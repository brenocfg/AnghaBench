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
typedef  size_t uint64_t ;

/* Variables and functions */
 size_t H2O_TIMERWHEEL_BITS_PER_WHEEL ; 
 size_t H2O_TIMERWHEEL_SLOTS_MASK ; 

__attribute__((used)) static size_t timer_slot(size_t wheel, uint64_t expire)
{
    return H2O_TIMERWHEEL_SLOTS_MASK & (expire >> (wheel * H2O_TIMERWHEEL_BITS_PER_WHEEL));
}