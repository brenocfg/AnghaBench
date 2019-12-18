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
 int /*<<< orphan*/  SPR_TTMR ; 
 int /*<<< orphan*/  SPR_TTMR_CR ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void timer_ack(void)
{
	/* Clear the IP bit and disable further interrupts */
	/* This can be done very simply... we just need to keep the timer
	   running, so just maintain the CR bits while clearing the rest
	   of the register
	 */
	mtspr(SPR_TTMR, SPR_TTMR_CR);
}