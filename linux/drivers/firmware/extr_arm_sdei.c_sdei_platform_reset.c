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
 int /*<<< orphan*/  _ipi_private_reset ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int sdei_api_shared_reset () ; 
 int /*<<< orphan*/  sdei_mark_interface_broken () ; 

__attribute__((used)) static int sdei_platform_reset(void)
{
	int err;

	on_each_cpu(&_ipi_private_reset, NULL, true);
	err = sdei_api_shared_reset();
	if (err) {
		pr_err("Failed to reset platform: %d\n", err);
		sdei_mark_interface_broken();
	}

	return err;
}