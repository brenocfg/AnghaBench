#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ idi_vaddr; } ;
struct vmxnet3_softc {int vmx_flags; TYPE_1__ vmx_rss_dma; struct vmxnet3_rss_shared* vmx_rss; int /*<<< orphan*/  vmx_ctx; TYPE_1__ vmx_ds_dma; struct vmxnet3_driver_shared* vmx_ds; int /*<<< orphan*/  vmx_dev; } ;
struct vmxnet3_rss_shared {int dummy; } ;
struct vmxnet3_driver_shared {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int VMXNET3_FLAG_RSS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int iflib_dma_alloc_align (int /*<<< orphan*/ ,size_t,int,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmxnet3_alloc_shared_data(struct vmxnet3_softc *sc)
{
	device_t dev;
	size_t size;
	int error;

	dev = sc->vmx_dev;

	/* Top level state structure shared with the device */
	size = sizeof(struct vmxnet3_driver_shared);
	error = iflib_dma_alloc_align(sc->vmx_ctx, size, 1, &sc->vmx_ds_dma, 0);
	if (error) {
		device_printf(dev, "cannot alloc shared memory\n");
		return (error);
	}
	sc->vmx_ds = (struct vmxnet3_driver_shared *) sc->vmx_ds_dma.idi_vaddr;

	/* RSS table state shared with the device */
	if (sc->vmx_flags & VMXNET3_FLAG_RSS) {
		size = sizeof(struct vmxnet3_rss_shared);
		error = iflib_dma_alloc_align(sc->vmx_ctx, size, 128,
		    &sc->vmx_rss_dma, 0);
		if (error) {
			device_printf(dev, "cannot alloc rss shared memory\n");
			return (error);
		}
		sc->vmx_rss =
		    (struct vmxnet3_rss_shared *) sc->vmx_rss_dma.idi_vaddr;
	}

	return (0);
}