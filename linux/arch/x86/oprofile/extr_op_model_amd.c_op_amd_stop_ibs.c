#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ op_enabled; scalar_t__ fetch_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_AMD64_IBSFETCHCTL ; 
 int /*<<< orphan*/  MSR_AMD64_IBSOPCTL ; 
 int /*<<< orphan*/  ibs_caps ; 
 TYPE_1__ ibs_config ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void op_amd_stop_ibs(void)
{
	if (!ibs_caps)
		return;

	if (ibs_config.fetch_enabled)
		/* clear max count and enable */
		wrmsrl(MSR_AMD64_IBSFETCHCTL, 0);

	if (ibs_config.op_enabled)
		/* clear max count and enable */
		wrmsrl(MSR_AMD64_IBSOPCTL, 0);
}