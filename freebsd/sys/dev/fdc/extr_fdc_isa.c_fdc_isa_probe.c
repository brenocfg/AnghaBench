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
struct fdc_data {int /*<<< orphan*/  fdc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int ISA_PNP_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct fdc_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdc_ids ; 
 int fdc_initial_reset (int /*<<< orphan*/ ,struct fdc_data*) ; 
 int fdc_isa_alloc_resources (int /*<<< orphan*/ ,struct fdc_data*) ; 
 int /*<<< orphan*/  fdc_release_resources (struct fdc_data*) ; 

__attribute__((used)) static int
fdc_isa_probe(device_t dev)
{
	int	error;
	struct	fdc_data *fdc;

	fdc = device_get_softc(dev);
	fdc->fdc_dev = dev;

	/* Check pnp ids */
	error = ISA_PNP_PROBE(device_get_parent(dev), dev, fdc_ids);
	if (error == ENXIO)
		return (ENXIO);

	/* Attempt to allocate our resources for the duration of the probe */
	error = fdc_isa_alloc_resources(dev, fdc);
	if (error == 0)
		error = fdc_initial_reset(dev, fdc);

	fdc_release_resources(fdc);
	return (error);
}