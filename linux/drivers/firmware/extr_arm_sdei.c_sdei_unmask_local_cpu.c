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
 int EIO ; 
 int /*<<< orphan*/  SDEI_1_0_FN_SDEI_PE_UNMASK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int invoke_sdei_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn_once (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preemptible () ; 
 int /*<<< orphan*/  smp_processor_id () ; 

int sdei_unmask_local_cpu(void)
{
	int err;

	WARN_ON_ONCE(preemptible());

	err = invoke_sdei_fn(SDEI_1_0_FN_SDEI_PE_UNMASK, 0, 0, 0, 0, 0, NULL);
	if (err && err != -EIO) {
		pr_warn_once("failed to unmask CPU[%u]: %d\n",
			     smp_processor_id(), err);
		return err;
	}

	return 0;
}