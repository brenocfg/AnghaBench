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
struct nvdimm_bus_descriptor {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_nfit_desc {int scrub_count; int scrub_tmo; int /*<<< orphan*/  init_mutex; int /*<<< orphan*/  dwork; int /*<<< orphan*/  scrub_flags; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARS_BUSY ; 
 int /*<<< orphan*/  ARS_CANCEL ; 
 int /*<<< orphan*/  ARS_POLL ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 struct nvdimm_bus_descriptor* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfit_device_lock (struct device*) ; 
 int /*<<< orphan*/  nfit_device_unlock (struct device*) ; 
 int /*<<< orphan*/  nfit_wq ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct acpi_nfit_desc* to_acpi_desc (struct nvdimm_bus_descriptor*) ; 

__attribute__((used)) static ssize_t scrub_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nvdimm_bus_descriptor *nd_desc;
	struct acpi_nfit_desc *acpi_desc;
	ssize_t rc = -ENXIO;
	bool busy;

	nfit_device_lock(dev);
	nd_desc = dev_get_drvdata(dev);
	if (!nd_desc) {
		nfit_device_unlock(dev);
		return rc;
	}
	acpi_desc = to_acpi_desc(nd_desc);

	mutex_lock(&acpi_desc->init_mutex);
	busy = test_bit(ARS_BUSY, &acpi_desc->scrub_flags)
		&& !test_bit(ARS_CANCEL, &acpi_desc->scrub_flags);
	rc = sprintf(buf, "%d%s", acpi_desc->scrub_count, busy ? "+\n" : "\n");
	/* Allow an admin to poll the busy state at a higher rate */
	if (busy && capable(CAP_SYS_RAWIO) && !test_and_set_bit(ARS_POLL,
				&acpi_desc->scrub_flags)) {
		acpi_desc->scrub_tmo = 1;
		mod_delayed_work(nfit_wq, &acpi_desc->dwork, HZ);
	}

	mutex_unlock(&acpi_desc->init_mutex);
	nfit_device_unlock(dev);
	return rc;
}