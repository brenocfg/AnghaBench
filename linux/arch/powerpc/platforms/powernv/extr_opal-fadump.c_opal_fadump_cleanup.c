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
struct fw_dump {int dummy; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_MPIPL_TAG_KERNEL ; 
 scalar_t__ OPAL_SUCCESS ; 
 scalar_t__ opal_mpipl_register_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 

__attribute__((used)) static void opal_fadump_cleanup(struct fw_dump *fadump_conf)
{
	s64 ret;

	ret = opal_mpipl_register_tag(OPAL_MPIPL_TAG_KERNEL, 0);
	if (ret != OPAL_SUCCESS)
		pr_warn("Could not reset (%llu) kernel metadata tag!\n", ret);
}