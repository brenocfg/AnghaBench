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
struct nfit_table_prev {int /*<<< orphan*/  flushes; int /*<<< orphan*/  idts; int /*<<< orphan*/  bdws; int /*<<< orphan*/  dcrs; int /*<<< orphan*/  memdevs; int /*<<< orphan*/  spas; } ;
struct device {int dummy; } ;
struct acpi_nfit_desc {struct device* dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_nfit_check_deletions(struct acpi_nfit_desc *acpi_desc,
		struct nfit_table_prev *prev)
{
	struct device *dev = acpi_desc->dev;

	if (!list_empty(&prev->spas) ||
			!list_empty(&prev->memdevs) ||
			!list_empty(&prev->dcrs) ||
			!list_empty(&prev->bdws) ||
			!list_empty(&prev->idts) ||
			!list_empty(&prev->flushes)) {
		dev_err(dev, "new nfit deletes entries (unsupported)\n");
		return -ENXIO;
	}
	return 0;
}