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
struct global_reg_snapshot {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void __global_reg_poll(struct global_reg_snapshot *gp)
{
	int limit = 0;

	while (!gp->thread && ++limit < 100) {
		barrier();
		udelay(1);
	}
}