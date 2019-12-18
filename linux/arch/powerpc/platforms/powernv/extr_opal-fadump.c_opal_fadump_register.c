#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fw_dump {int dump_registered; int /*<<< orphan*/  fadump_enabled; int /*<<< orphan*/  fadump_supported; } ;
typedef  int s64 ;
struct TYPE_4__ {int region_cnt; scalar_t__ registered_regions; TYPE_1__* rgn; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  dest; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int EIO ; 
#define  OPAL_HARDWARE 131 
 int /*<<< orphan*/  OPAL_MPIPL_ADD_RANGE ; 
#define  OPAL_PARAMETER 130 
#define  OPAL_RESOURCE 129 
#define  OPAL_SUCCESS 128 
 int /*<<< orphan*/  opal_fadump_unregister (struct fw_dump*) ; 
 TYPE_2__* opal_fdm ; 
 int opal_mpipl_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 

__attribute__((used)) static int opal_fadump_register(struct fw_dump *fadump_conf)
{
	s64 rc = OPAL_PARAMETER;
	int i, err = -EIO;

	for (i = 0; i < opal_fdm->region_cnt; i++) {
		rc = opal_mpipl_update(OPAL_MPIPL_ADD_RANGE,
				       opal_fdm->rgn[i].src,
				       opal_fdm->rgn[i].dest,
				       opal_fdm->rgn[i].size);
		if (rc != OPAL_SUCCESS)
			break;

		opal_fdm->registered_regions++;
	}

	switch (rc) {
	case OPAL_SUCCESS:
		pr_info("Registration is successful!\n");
		fadump_conf->dump_registered = 1;
		err = 0;
		break;
	case OPAL_RESOURCE:
		/* If MAX regions limit in f/w is hit, warn and proceed. */
		pr_warn("%d regions could not be registered for MPIPL as MAX limit is reached!\n",
			(opal_fdm->region_cnt - opal_fdm->registered_regions));
		fadump_conf->dump_registered = 1;
		err = 0;
		break;
	case OPAL_PARAMETER:
		pr_err("Failed to register. Parameter Error(%lld).\n", rc);
		break;
	case OPAL_HARDWARE:
		pr_err("Support not available.\n");
		fadump_conf->fadump_supported = 0;
		fadump_conf->fadump_enabled = 0;
		break;
	default:
		pr_err("Failed to register. Unknown Error(%lld).\n", rc);
		break;
	}

	/*
	 * If some regions were registered before OPAL_MPIPL_ADD_RANGE
	 * OPAL call failed, unregister all regions.
	 */
	if ((err < 0) && (opal_fdm->registered_regions > 0))
		opal_fadump_unregister(fadump_conf);

	return err;
}