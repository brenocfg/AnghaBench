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
 int /*<<< orphan*/  env ; 
 int /*<<< orphan*/  pll_control ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 

void
pll_trap(
	int arg
	)
{
	pll_control--;
	siglongjmp(env, 1);
}