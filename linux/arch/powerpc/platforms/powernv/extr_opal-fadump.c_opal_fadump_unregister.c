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
struct fw_dump {scalar_t__ dump_registered; } ;
typedef  scalar_t__ s64 ;
struct TYPE_2__ {scalar_t__ registered_regions; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  OPAL_MPIPL_REMOVE_ALL ; 
 TYPE_1__* opal_fdm ; 
 scalar_t__ opal_mpipl_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 

__attribute__((used)) static int opal_fadump_unregister(struct fw_dump *fadump_conf)
{
	s64 rc;

	rc = opal_mpipl_update(OPAL_MPIPL_REMOVE_ALL, 0, 0, 0);
	if (rc) {
		pr_err("Failed to un-register - unexpected Error(%lld).\n", rc);
		return -EIO;
	}

	opal_fdm->registered_regions = 0;
	fadump_conf->dump_registered = 0;
	return 0;
}