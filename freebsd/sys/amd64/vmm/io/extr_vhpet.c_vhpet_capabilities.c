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
typedef  int uint64_t ;

/* Variables and functions */
 int FS_PER_S ; 
 int HPET_CAP_COUNT_SIZE ; 
 int HPET_FREQ ; 
 int VHPET_NUM_TIMERS ; 

__attribute__((used)) static uint64_t
vhpet_capabilities(void)
{
	uint64_t cap = 0;

	cap |= 0x8086 << 16;			/* vendor id */
	cap |= (VHPET_NUM_TIMERS - 1) << 8;	/* number of timers */
	cap |= 1;				/* revision */
	cap &= ~HPET_CAP_COUNT_SIZE;		/* 32-bit timer */

	cap &= 0xffffffff;
	cap |= (FS_PER_S / HPET_FREQ) << 32;	/* tick period in fs */

	return (cap);
}