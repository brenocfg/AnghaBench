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
 int ENXIO ; 
 int ISA_PNP_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int an_alloc_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  an_ids ; 
 int an_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  an_release_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
an_probe_isa(device_t dev)
{
	int			error = 0;

	error = ISA_PNP_PROBE(device_get_parent(dev), dev, an_ids);
	if (error == ENXIO)
		return(error);

	error = an_probe(dev);
	an_release_resources(dev);
	if (error == 0)
		return (ENXIO);

	error = an_alloc_irq(dev, 0, 0);
	an_release_resources(dev);
	if (!error)
		device_set_desc(dev, "Aironet ISA4500/ISA4800");
	return (error);
}