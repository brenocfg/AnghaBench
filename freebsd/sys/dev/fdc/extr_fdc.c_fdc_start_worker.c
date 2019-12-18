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
struct fdc_data {int /*<<< orphan*/  fdc_thread; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct fdc_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdc_thread ; 
 int /*<<< orphan*/  kproc_create (int /*<<< orphan*/ ,struct fdc_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
fdc_start_worker(device_t dev)
{
	struct	fdc_data *fdc;

	fdc = device_get_softc(dev);
	kproc_create(fdc_thread, fdc, &fdc->fdc_thread, 0, 0,
	    "fdc%d", device_get_unit(dev));
}