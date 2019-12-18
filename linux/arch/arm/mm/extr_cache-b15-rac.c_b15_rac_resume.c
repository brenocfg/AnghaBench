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
 int /*<<< orphan*/  RAC_SUSPENDED ; 
 int /*<<< orphan*/  __b15_rac_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b15_rac_flags ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rac_config0_reg ; 

__attribute__((used)) static void b15_rac_resume(void)
{
	/* Coming out of a S3 suspend/resume cycle, the read-ahead cache
	 * register RAC_CONFIG0_REG will be restored to its default value, make
	 * sure we re-enable it and set the enable flag, we are also guaranteed
	 * to run on the boot CPU, so not racy again.
	 */
	__b15_rac_enable(rac_config0_reg);
	clear_bit(RAC_SUSPENDED, &b15_rac_flags);
}