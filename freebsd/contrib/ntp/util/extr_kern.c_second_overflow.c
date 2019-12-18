#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tv_sec; } ;

/* Variables and functions */
 int SHIFT_HZ ; 
 int SHIFT_KF ; 
 int SHIFT_KG ; 
 int SHIFT_SCALE ; 
 int SHIFT_UPDATE ; 
#define  TIME_DEL 130 
#define  TIME_INS 129 
 int TIME_OK ; 
#define  TIME_OOP 128 
 int fixtick ; 
 int time_adj ; 
 int time_constant ; 
 int time_freq ; 
 int /*<<< orphan*/  time_maxerror ; 
 int time_offset ; 
 int time_status ; 
 scalar_t__ time_tolerance ; 
 TYPE_1__ timex ; 

void
second_overflow(void)
{
	int ltemp;

	time_maxerror += time_tolerance;
	if (time_offset < 0) {
		ltemp = -time_offset >>
			(SHIFT_KG + time_constant);
		time_offset += ltemp;
		time_adj = -(ltemp <<
			     (SHIFT_SCALE - SHIFT_HZ - SHIFT_UPDATE));
	} else {
		ltemp = time_offset >>
			(SHIFT_KG + time_constant);
		time_offset -= ltemp;
		time_adj = ltemp <<
			(SHIFT_SCALE - SHIFT_HZ - SHIFT_UPDATE);
	}
	if (time_freq < 0)
	    time_adj -= -time_freq >> (SHIFT_KF + SHIFT_HZ - SHIFT_SCALE);
	else
	    time_adj += time_freq >> (SHIFT_KF + SHIFT_HZ - SHIFT_SCALE);
	time_adj += fixtick << (SHIFT_SCALE - SHIFT_HZ);

	/* ugly divide should be replaced */
	if (timex.tv_sec % 86400 == 0) {
		switch (time_status) {

		    case TIME_INS:
			timex.tv_sec--; /* !! */
			time_status = TIME_OOP;
			break;

		    case TIME_DEL:
			timex.tv_sec++;
			time_status = TIME_OK;
			break;

		    case TIME_OOP:
			time_status = TIME_OK;
			break;
		}
	}
}