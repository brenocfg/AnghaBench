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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NUM_OF_HPTSI_SLOTS ; 

__attribute__((used)) static inline int
hpts_tick(uint32_t wheel_tick, uint32_t plus)
{
	/*
	 * Given a slot on the wheel, what slot
	 * is that plus ticks out?
	 */
	KASSERT(wheel_tick < NUM_OF_HPTSI_SLOTS, ("Invalid tick %u not on wheel", wheel_tick));
	return ((wheel_tick + plus) % NUM_OF_HPTSI_SLOTS);
}