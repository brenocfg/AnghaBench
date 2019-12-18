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
struct asmc_model {int /*<<< orphan*/  smc_desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ACPI_ID_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 int /*<<< orphan*/  asmc_ids ; 
 struct asmc_model* asmc_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
asmc_probe(device_t dev)
{
	struct asmc_model *model;
	int rv;

	if (resource_disabled("asmc", 0))
		return (ENXIO);
	rv = ACPI_ID_PROBE(device_get_parent(dev), dev, asmc_ids, NULL);
	if (rv > 0)
		return (rv);

	model = asmc_match(dev);
	if (!model) {
		device_printf(dev, "model not recognized\n");
		return (ENXIO);
	}
	device_set_desc(dev, model->smc_desc);

	return (rv);
}