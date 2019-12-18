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
struct kernel_param {scalar_t__ arg; } ;
typedef  int /*<<< orphan*/  local64_t ;

/* Variables and functions */
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int param_set_local64(const char *val, const struct kernel_param *kp)
{
	/* Clear on any write */
	local64_set((local64_t *)kp->arg, 0);
	return 0;
}