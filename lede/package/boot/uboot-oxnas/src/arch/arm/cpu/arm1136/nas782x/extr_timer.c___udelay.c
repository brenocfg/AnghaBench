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
typedef  int ulong ;

/* Variables and functions */
 int CONFIG_SYS_HZ ; 
 int READ_TIMER_HW ; 
 int TIMER_CLOCK ; 
 int TIMER_LOAD_VAL ; 
 int get_timer (int) ; 

void __udelay (unsigned long usec)
{
	ulong tmo, tmp;

	if (usec > 100000) {		/* if "big" number, spread normalization to seconds */
		tmo = usec / 1000;	/* start to normalize for usec to ticks per sec */
		tmo *= CONFIG_SYS_HZ;	/* find number of "ticks" to wait to achieve target */
		tmo /= 1000;		/* finish normalize. */

		tmp = get_timer (0);		/* get current timestamp */
		while (get_timer (tmp) < tmo)/* loop till event */
			/*NOP*/;
	} else {			/* else small number, convert to hw ticks */
		tmo = usec * (TIMER_CLOCK / 1000) / 1000;
		/* timeout is no more than 0.1s, and the hw timer will roll over at most once */
		tmp = READ_TIMER_HW;
		while (((READ_TIMER_HW -tmp) & TIMER_LOAD_VAL) < tmo)/* loop till event */
			/*NOP*/;
	}
}