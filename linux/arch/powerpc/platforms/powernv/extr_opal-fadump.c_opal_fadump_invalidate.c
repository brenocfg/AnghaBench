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
struct fw_dump {scalar_t__ dump_active; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  OPAL_MPIPL_FREE_PRESERVED_MEMORY ; 
 int /*<<< orphan*/ * opal_fdm_active ; 
 scalar_t__ opal_mpipl_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 

__attribute__((used)) static int opal_fadump_invalidate(struct fw_dump *fadump_conf)
{
	s64 rc;

	rc = opal_mpipl_update(OPAL_MPIPL_FREE_PRESERVED_MEMORY, 0, 0, 0);
	if (rc) {
		pr_err("Failed to invalidate - unexpected Error(%lld).\n", rc);
		return -EIO;
	}

	fadump_conf->dump_active = 0;
	opal_fdm_active = NULL;
	return 0;
}