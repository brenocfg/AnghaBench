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
 struct fdc_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int fdc_attach (int /*<<< orphan*/ ) ; 
 int fdc_hints_probe (int /*<<< orphan*/ ) ; 
 int fdc_isa_alloc_resources (int /*<<< orphan*/ ,struct fdc_data*) ; 
 int /*<<< orphan*/  fdc_release_resources (struct fdc_data*) ; 
 int /*<<< orphan*/  fdc_start_worker (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fdc_isa_attach(device_t dev)
{
	struct	fdc_data *fdc;
	int error;

	fdc = device_get_softc(dev);
	fdc->fdc_dev = dev;
	error = fdc_isa_alloc_resources(dev, fdc);
	if (error == 0)
		error = fdc_attach(dev);
	if (error == 0)
		error = fdc_hints_probe(dev);
	if (error == 0)
		fdc_start_worker(dev);
	else
		fdc_release_resources(fdc);
	return (error);
}