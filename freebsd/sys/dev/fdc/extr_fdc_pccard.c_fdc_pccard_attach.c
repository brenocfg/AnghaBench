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
struct fdc_data {int flags; int /*<<< orphan*/  fdct; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FDC_NE765 ; 
 int FDC_NODMA ; 
 int FDC_NOFAST ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 struct fdc_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_flags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fdc_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int fdc_attach (int /*<<< orphan*/ ) ; 
 int fdc_pccard_alloc_resources (int /*<<< orphan*/ ,struct fdc_data*) ; 
 int /*<<< orphan*/  fdc_release_resources (struct fdc_data*) ; 
 int /*<<< orphan*/  fdc_start_worker (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fdc_pccard_attach(device_t dev)
{
	int error;
	struct	fdc_data *fdc;
	device_t child;

	fdc = device_get_softc(dev);
	fdc->flags = FDC_NODMA | FDC_NOFAST;
	fdc->fdct = FDC_NE765;
	error = fdc_pccard_alloc_resources(dev, fdc);
	if (error == 0)
		error = fdc_attach(dev);
	if (error == 0) {
		child = fdc_add_child(dev, "fd", -1);
		device_set_flags(child, 0x24);
		error = bus_generic_attach(dev);
	}
	if (error == 0)
		fdc_start_worker(dev);
	else
		fdc_release_resources(fdc);
	return (error);
}