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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  PUC_IVAR_TYPE ; 
 uintptr_t PUC_TYPE_PARALLEL ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int ppc_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ppc_puc_probe(device_t dev)
{
	device_t parent;
	uintptr_t type;

	parent = device_get_parent(dev);
	if (BUS_READ_IVAR(parent, dev, PUC_IVAR_TYPE, &type))
		return (ENXIO);
	if (type != PUC_TYPE_PARALLEL)
		return (ENXIO);

	device_set_desc(dev, "Parallel port");
	return (ppc_probe(dev, 0));
}