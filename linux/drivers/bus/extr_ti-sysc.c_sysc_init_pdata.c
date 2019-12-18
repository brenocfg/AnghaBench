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
struct ti_sysc_platform_data {int dummy; } ;
struct ti_sysc_module_data {int /*<<< orphan*/ * cfg; int /*<<< orphan*/  cap; int /*<<< orphan*/  nr_offsets; int /*<<< orphan*/  offsets; int /*<<< orphan*/  module_size; int /*<<< orphan*/  module_pa; scalar_t__ name; } ;
struct sysc {struct ti_sysc_module_data* mdata; int /*<<< orphan*/  cfg; int /*<<< orphan*/  cap; int /*<<< orphan*/  offsets; int /*<<< orphan*/  module_size; int /*<<< orphan*/  module_pa; scalar_t__ legacy_mode; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SYSC_MAX_REGS ; 
 struct ti_sysc_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 struct ti_sysc_module_data* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysc_init_pdata(struct sysc *ddata)
{
	struct ti_sysc_platform_data *pdata = dev_get_platdata(ddata->dev);
	struct ti_sysc_module_data *mdata;

	if (!pdata)
		return 0;

	mdata = devm_kzalloc(ddata->dev, sizeof(*mdata), GFP_KERNEL);
	if (!mdata)
		return -ENOMEM;

	if (ddata->legacy_mode) {
		mdata->name = ddata->legacy_mode;
		mdata->module_pa = ddata->module_pa;
		mdata->module_size = ddata->module_size;
		mdata->offsets = ddata->offsets;
		mdata->nr_offsets = SYSC_MAX_REGS;
		mdata->cap = ddata->cap;
		mdata->cfg = &ddata->cfg;
	}

	ddata->mdata = mdata;

	return 0;
}