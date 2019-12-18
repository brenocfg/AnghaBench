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

/* Variables and functions */
 double CLOCK_PLL ; 
 int /*<<< orphan*/  DEBUG_INSIST (int) ; 
 scalar_t__ EVNT_SYNC ; 
 scalar_t__ FALSE ; 
 double NTP_MAXFREQ ; 
 scalar_t__ TRUE ; 
 double ULOGTOD (int) ; 
 int /*<<< orphan*/  adj_systime (double) ; 
 double clock_offset ; 
 scalar_t__ clock_phi ; 
 double drift_comp ; 
 scalar_t__ enable_panic_check ; 
 scalar_t__ freq_cnt ; 
 scalar_t__ kern_enable ; 
 scalar_t__ mode_ntpdate ; 
 int /*<<< orphan*/  ntp_enable ; 
 scalar_t__ pll_control ; 
 scalar_t__ state ; 
 int sys_poll ; 
 int /*<<< orphan*/  sys_rootdisp ; 

void
adj_host_clock(
	void
	)
{
	double	offset_adj;
	double	freq_adj;

	/*
	 * Update the dispersion since the last update. In contrast to
	 * NTPv3, NTPv4 does not declare unsynchronized after one day,
	 * since the dispersion check serves this function. Also,
	 * since the poll interval can exceed one day, the old test
	 * would be counterproductive. During the startup clamp period, the
	 * time constant is clamped at 2.
	 */
	sys_rootdisp += clock_phi;
#ifndef LOCKCLOCK
	if (!ntp_enable || mode_ntpdate)
		return;
	/*
	 * Determine the phase adjustment. The gain factor (denominator)
	 * increases with poll interval, so is dominated by the FLL
	 * above the Allan intercept. Note the reduced time constant at
	 * startup.
	 */
	if (state != EVNT_SYNC) {
		offset_adj = 0.;
	} else if (freq_cnt > 0) {
		offset_adj = clock_offset / (CLOCK_PLL * ULOGTOD(1));
		freq_cnt--;
#ifdef KERNEL_PLL
	} else if (pll_control && kern_enable) {
		offset_adj = 0.;
#endif /* KERNEL_PLL */
	} else {
		offset_adj = clock_offset / (CLOCK_PLL * ULOGTOD(sys_poll));
	}

	/*
	 * If the kernel discipline is enabled the frequency correction
	 * drift_comp has already been engaged via ntp_adjtime() in
	 * set_freq().  Otherwise it is a component of the adj_systime()
	 * offset.
	 */
#ifdef KERNEL_PLL
	if (pll_control && kern_enable)
		freq_adj = 0.;
	else
#endif /* KERNEL_PLL */
		freq_adj = drift_comp;

	/* Bound absolute value of total adjustment to NTP_MAXFREQ. */
	if (offset_adj + freq_adj > NTP_MAXFREQ)
		offset_adj = NTP_MAXFREQ - freq_adj;
	else if (offset_adj + freq_adj < -NTP_MAXFREQ)
		offset_adj = -NTP_MAXFREQ - freq_adj;

	clock_offset -= offset_adj;
	/*
	 * Windows port adj_systime() must be called each second,
	 * even if the argument is zero, to ease emulation of
	 * adjtime() using Windows' slew API which controls the rate
	 * but does not automatically stop slewing when an offset
	 * has decayed to zero.
	 */
	DEBUG_INSIST(enable_panic_check == TRUE);
	enable_panic_check = FALSE;
	adj_systime(offset_adj + freq_adj);
	enable_panic_check = TRUE;
#endif /* LOCKCLOCK */
}