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
struct nfit_table_prev {int /*<<< orphan*/  flushes; int /*<<< orphan*/  idts; int /*<<< orphan*/  bdws; int /*<<< orphan*/  dcrs; int /*<<< orphan*/  memdevs; int /*<<< orphan*/  spas; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  prev; } ;
struct acpi_nfit_desc {int /*<<< orphan*/  init_mutex; TYPE_1__ flushes; TYPE_1__ idts; TYPE_1__ bdws; TYPE_1__ dcrs; TYPE_1__ memdevs; TYPE_1__ spas; int /*<<< orphan*/  list; int /*<<< orphan*/  nvdimm_bus; int /*<<< orphan*/  nd_desc; struct device* dev; } ;
typedef  int acpi_size ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  acpi_desc_lock ; 
 int /*<<< orphan*/  acpi_descs ; 
 int acpi_nfit_check_deletions (struct acpi_nfit_desc*,struct nfit_table_prev*) ; 
 int acpi_nfit_desc_init_scrub_attr (struct acpi_nfit_desc*) ; 
 int /*<<< orphan*/  acpi_nfit_init_dsms (struct acpi_nfit_desc*) ; 
 int acpi_nfit_register_dimms (struct acpi_nfit_desc*) ; 
 int acpi_nfit_register_regions (struct acpi_nfit_desc*) ; 
 int /*<<< orphan*/  acpi_nfit_unregister ; 
 void* add_table (struct acpi_nfit_desc*,struct nfit_table_prev*,void*,void const*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct acpi_nfit_desc*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_cut_position (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nfit_mem_init (struct acpi_nfit_desc*) ; 
 int /*<<< orphan*/  nvdimm_bus_register (struct device*,int /*<<< orphan*/ *) ; 

int acpi_nfit_init(struct acpi_nfit_desc *acpi_desc, void *data, acpi_size sz)
{
	struct device *dev = acpi_desc->dev;
	struct nfit_table_prev prev;
	const void *end;
	int rc;

	if (!acpi_desc->nvdimm_bus) {
		acpi_nfit_init_dsms(acpi_desc);

		acpi_desc->nvdimm_bus = nvdimm_bus_register(dev,
				&acpi_desc->nd_desc);
		if (!acpi_desc->nvdimm_bus)
			return -ENOMEM;

		rc = devm_add_action_or_reset(dev, acpi_nfit_unregister,
				acpi_desc);
		if (rc)
			return rc;

		rc = acpi_nfit_desc_init_scrub_attr(acpi_desc);
		if (rc)
			return rc;

		/* register this acpi_desc for mce notifications */
		mutex_lock(&acpi_desc_lock);
		list_add_tail(&acpi_desc->list, &acpi_descs);
		mutex_unlock(&acpi_desc_lock);
	}

	mutex_lock(&acpi_desc->init_mutex);

	INIT_LIST_HEAD(&prev.spas);
	INIT_LIST_HEAD(&prev.memdevs);
	INIT_LIST_HEAD(&prev.dcrs);
	INIT_LIST_HEAD(&prev.bdws);
	INIT_LIST_HEAD(&prev.idts);
	INIT_LIST_HEAD(&prev.flushes);

	list_cut_position(&prev.spas, &acpi_desc->spas,
				acpi_desc->spas.prev);
	list_cut_position(&prev.memdevs, &acpi_desc->memdevs,
				acpi_desc->memdevs.prev);
	list_cut_position(&prev.dcrs, &acpi_desc->dcrs,
				acpi_desc->dcrs.prev);
	list_cut_position(&prev.bdws, &acpi_desc->bdws,
				acpi_desc->bdws.prev);
	list_cut_position(&prev.idts, &acpi_desc->idts,
				acpi_desc->idts.prev);
	list_cut_position(&prev.flushes, &acpi_desc->flushes,
				acpi_desc->flushes.prev);

	end = data + sz;
	while (!IS_ERR_OR_NULL(data))
		data = add_table(acpi_desc, &prev, data, end);

	if (IS_ERR(data)) {
		dev_dbg(dev, "nfit table parsing error: %ld\n",	PTR_ERR(data));
		rc = PTR_ERR(data);
		goto out_unlock;
	}

	rc = acpi_nfit_check_deletions(acpi_desc, &prev);
	if (rc)
		goto out_unlock;

	rc = nfit_mem_init(acpi_desc);
	if (rc)
		goto out_unlock;

	rc = acpi_nfit_register_dimms(acpi_desc);
	if (rc)
		goto out_unlock;

	rc = acpi_nfit_register_regions(acpi_desc);

 out_unlock:
	mutex_unlock(&acpi_desc->init_mutex);
	return rc;
}