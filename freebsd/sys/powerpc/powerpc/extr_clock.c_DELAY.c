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
typedef  scalar_t__ volatile u_quad_t ;

/* Variables and functions */
 int /*<<< orphan*/  TSENTER () ; 
 int /*<<< orphan*/  TSEXIT () ; 
 scalar_t__ volatile howmany (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mftb () ; 
 int /*<<< orphan*/  nop_prio_medium () ; 
 int /*<<< orphan*/  nop_prio_vlow () ; 
 int /*<<< orphan*/  ps_per_tick ; 

void
DELAY(int n)
{
	volatile u_quad_t	tb;
	u_quad_t		ttb;

	TSENTER();
	tb = mftb();
	ttb = tb + howmany((uint64_t)n * 1000000, ps_per_tick);
	nop_prio_vlow();
	while (tb < ttb)
		tb = mftb();
	nop_prio_medium();
	TSEXIT();
}