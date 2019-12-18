#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int time_t ;
typedef  int /*<<< orphan*/  l_fp ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  L_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L_LINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  L_RSHIFT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  L_SUB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAXFREQ ; 
 int /*<<< orphan*/  NTP_LOCK () ; 
 int /*<<< orphan*/  NTP_UNLOCK () ; 
 scalar_t__ SHIFT_PLL ; 
 int STA_DEL ; 
 int STA_INS ; 
 int STA_PPSSIGNAL ; 
 int STA_PPSTIME ; 
#define  TIME_DEL 132 
#define  TIME_INS 131 
#define  TIME_OK 130 
#define  TIME_OOP 129 
#define  TIME_WAIT 128 
 scalar_t__ pps_shift ; 
 scalar_t__ pps_valid ; 
 int /*<<< orphan*/  time_adj ; 
 int time_adjtime ; 
 scalar_t__ time_constant ; 
 int /*<<< orphan*/  time_freq ; 
 int time_maxerror ; 
 int /*<<< orphan*/  time_offset ; 
 int time_state ; 
 int time_status ; 
 int /*<<< orphan*/  time_tai ; 

void
ntp_update_second(int64_t *adjustment, time_t *newsec)
{
	int tickrate;
	l_fp ftemp;		/* 32/64-bit temporary */

	NTP_LOCK();

	/*
	 * On rollover of the second both the nanosecond and microsecond
	 * clocks are updated and the state machine cranked as
	 * necessary. The phase adjustment to be used for the next
	 * second is calculated and the maximum error is increased by
	 * the tolerance.
	 */
	time_maxerror += MAXFREQ / 1000;

	/*
	 * Leap second processing. If in leap-insert state at
	 * the end of the day, the system clock is set back one
	 * second; if in leap-delete state, the system clock is
	 * set ahead one second. The nano_time() routine or
	 * external clock driver will insure that reported time
	 * is always monotonic.
	 */
	switch (time_state) {

		/*
		 * No warning.
		 */
		case TIME_OK:
		if (time_status & STA_INS)
			time_state = TIME_INS;
		else if (time_status & STA_DEL)
			time_state = TIME_DEL;
		break;

		/*
		 * Insert second 23:59:60 following second
		 * 23:59:59.
		 */
		case TIME_INS:
		if (!(time_status & STA_INS))
			time_state = TIME_OK;
		else if ((*newsec) % 86400 == 0) {
			(*newsec)--;
			time_state = TIME_OOP;
			time_tai++;
		}
		break;

		/*
		 * Delete second 23:59:59.
		 */
		case TIME_DEL:
		if (!(time_status & STA_DEL))
			time_state = TIME_OK;
		else if (((*newsec) + 1) % 86400 == 0) {
			(*newsec)++;
			time_tai--;
			time_state = TIME_WAIT;
		}
		break;

		/*
		 * Insert second in progress.
		 */
		case TIME_OOP:
			time_state = TIME_WAIT;
		break;

		/*
		 * Wait for status bits to clear.
		 */
		case TIME_WAIT:
		if (!(time_status & (STA_INS | STA_DEL)))
			time_state = TIME_OK;
	}

	/*
	 * Compute the total time adjustment for the next second
	 * in ns. The offset is reduced by a factor depending on
	 * whether the PPS signal is operating. Note that the
	 * value is in effect scaled by the clock frequency,
	 * since the adjustment is added at each tick interrupt.
	 */
	ftemp = time_offset;
#ifdef PPS_SYNC
	/* XXX even if PPS signal dies we should finish adjustment ? */
	if (time_status & STA_PPSTIME && time_status &
	    STA_PPSSIGNAL)
		L_RSHIFT(ftemp, pps_shift);
	else
		L_RSHIFT(ftemp, SHIFT_PLL + time_constant);
#else
		L_RSHIFT(ftemp, SHIFT_PLL + time_constant);
#endif /* PPS_SYNC */
	time_adj = ftemp;
	L_SUB(time_offset, ftemp);
	L_ADD(time_adj, time_freq);
	
	/*
	 * Apply any correction from adjtime(2).  If more than one second
	 * off we slew at a rate of 5ms/s (5000 PPM) else 500us/s (500PPM)
	 * until the last second is slewed the final < 500 usecs.
	 */
	if (time_adjtime != 0) {
		if (time_adjtime > 1000000)
			tickrate = 5000;
		else if (time_adjtime < -1000000)
			tickrate = -5000;
		else if (time_adjtime > 500)
			tickrate = 500;
		else if (time_adjtime < -500)
			tickrate = -500;
		else
			tickrate = time_adjtime;
		time_adjtime -= tickrate;
		L_LINT(ftemp, tickrate * 1000);
		L_ADD(time_adj, ftemp);
	}
	*adjustment = time_adj;
		
#ifdef PPS_SYNC
	if (pps_valid > 0)
		pps_valid--;
	else
		time_status &= ~STA_PPSSIGNAL;
#endif /* PPS_SYNC */

	NTP_UNLOCK();
}