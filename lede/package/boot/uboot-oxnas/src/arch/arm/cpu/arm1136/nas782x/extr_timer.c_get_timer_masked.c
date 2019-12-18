#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
struct TYPE_3__ {int lastinc; int tbl; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int CONFIG_SYS_HZ ; 
 int READ_TIMER ; 
 int TIMER_CLOCK ; 
 int TIMER_LOAD_VAL ; 
 TYPE_2__* gd ; 

ulong get_timer_masked (void)
{
	ulong now = READ_TIMER;		/* current tick value */

	if (now >= gd->arch.lastinc) {		/* normal mode (non roll) */
		/* move stamp fordward with absoulte diff ticks */
		gd->arch.tbl += (now - gd->arch.lastinc);
	} else {
		/* we have rollover of incrementer */
		gd->arch.tbl += ((TIMER_LOAD_VAL / (TIMER_CLOCK / CONFIG_SYS_HZ))
				 - gd->arch.lastinc) + now;
	}
	gd->arch.lastinc = now;
	return gd->arch.tbl;
}