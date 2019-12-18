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
struct mpt_softc {int verbose; int cfg_role; int do_cfg_role; int msi_enable; int /*<<< orphan*/  dev; scalar_t__ is_sas; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static void
mpt_set_options(struct mpt_softc *mpt)
{
	int tval;

	tval = 0;
	if (resource_int_value(device_get_name(mpt->dev),
	    device_get_unit(mpt->dev), "debug", &tval) == 0 && tval != 0) {
		mpt->verbose = tval;
	}
	tval = -1;
	if (resource_int_value(device_get_name(mpt->dev),
	    device_get_unit(mpt->dev), "role", &tval) == 0 && tval >= 0 &&
	    tval <= 3) {
		mpt->cfg_role = tval;
		mpt->do_cfg_role = 1;
	}
	tval = 0;
	mpt->msi_enable = 0;
	if (mpt->is_sas)
		mpt->msi_enable = 1;
	if (resource_int_value(device_get_name(mpt->dev),
	    device_get_unit(mpt->dev), "msi_enable", &tval) == 0) {
		mpt->msi_enable = tval;
	}
}