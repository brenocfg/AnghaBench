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
struct firewire_comm {int dummy; } ;

/* Variables and functions */
 int CYCLE_DELAY ; 
 int CYCLE_MOD ; 
 int roundup2 (int,int) ; 

__attribute__((used)) static int
fwohci_next_cycle(struct firewire_comm *fc, int cycle_now)
{
	int sec, cycle, cycle_match;

	cycle = cycle_now & 0x1fff;
	sec = cycle_now >> 13;
#define CYCLE_MOD	0x10
#if 1
#define CYCLE_DELAY	8	/* min delay to start DMA */
#else
#define CYCLE_DELAY	7000	/* min delay to start DMA */
#endif
	cycle = cycle + CYCLE_DELAY;
	if (cycle >= 8000) {
		sec++;
		cycle -= 8000;
	}
	cycle = roundup2(cycle, CYCLE_MOD);
	if (cycle >= 8000) {
		sec++;
		if (cycle == 8000)
			cycle = 0;
		else
			cycle = CYCLE_MOD;
	}
	cycle_match = ((sec << 13) | cycle) & 0x7ffff;

	return (cycle_match);
}