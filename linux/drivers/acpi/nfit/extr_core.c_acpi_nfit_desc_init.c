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
struct nvdimm_bus_descriptor {char* provider_name; int /*<<< orphan*/  attr_groups; int /*<<< orphan*/  clear_to_send; int /*<<< orphan*/  flush_probe; int /*<<< orphan*/  ndctl; int /*<<< orphan*/  module; } ;
struct device {int dummy; } ;
struct acpi_nfit_desc {int scrub_tmo; int /*<<< orphan*/  dwork; int /*<<< orphan*/  init_mutex; int /*<<< orphan*/  list; int /*<<< orphan*/  dimms; int /*<<< orphan*/  memdevs; int /*<<< orphan*/  flushes; int /*<<< orphan*/  idts; int /*<<< orphan*/  bdws; int /*<<< orphan*/  dcrs; int /*<<< orphan*/  spas; struct nvdimm_bus_descriptor nd_desc; int /*<<< orphan*/  blk_do_io; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  acpi_nfit_attribute_groups ; 
 int /*<<< orphan*/  acpi_nfit_blk_region_do_io ; 
 int /*<<< orphan*/  acpi_nfit_clear_to_send ; 
 int /*<<< orphan*/  acpi_nfit_ctl ; 
 int /*<<< orphan*/  acpi_nfit_flush_probe ; 
 int /*<<< orphan*/  acpi_nfit_scrub ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct acpi_nfit_desc*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void acpi_nfit_desc_init(struct acpi_nfit_desc *acpi_desc, struct device *dev)
{
	struct nvdimm_bus_descriptor *nd_desc;

	dev_set_drvdata(dev, acpi_desc);
	acpi_desc->dev = dev;
	acpi_desc->blk_do_io = acpi_nfit_blk_region_do_io;
	nd_desc = &acpi_desc->nd_desc;
	nd_desc->provider_name = "ACPI.NFIT";
	nd_desc->module = THIS_MODULE;
	nd_desc->ndctl = acpi_nfit_ctl;
	nd_desc->flush_probe = acpi_nfit_flush_probe;
	nd_desc->clear_to_send = acpi_nfit_clear_to_send;
	nd_desc->attr_groups = acpi_nfit_attribute_groups;

	INIT_LIST_HEAD(&acpi_desc->spas);
	INIT_LIST_HEAD(&acpi_desc->dcrs);
	INIT_LIST_HEAD(&acpi_desc->bdws);
	INIT_LIST_HEAD(&acpi_desc->idts);
	INIT_LIST_HEAD(&acpi_desc->flushes);
	INIT_LIST_HEAD(&acpi_desc->memdevs);
	INIT_LIST_HEAD(&acpi_desc->dimms);
	INIT_LIST_HEAD(&acpi_desc->list);
	mutex_init(&acpi_desc->init_mutex);
	acpi_desc->scrub_tmo = 1;
	INIT_DELAYED_WORK(&acpi_desc->dwork, acpi_nfit_scrub);
}