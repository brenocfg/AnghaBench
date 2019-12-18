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
struct TYPE_2__ {int /*<<< orphan*/  idi_vaddr; } ;
struct vmxnet3_softc {TYPE_1__ vmx_mcast_dma; int /*<<< orphan*/  vmx_mcast; int /*<<< orphan*/  vmx_dev; int /*<<< orphan*/  vmx_ctx; } ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int VMXNET3_MULTICAST_MAX ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int iflib_dma_alloc_align (int /*<<< orphan*/ ,int,int,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmxnet3_alloc_mcast_table(struct vmxnet3_softc *sc)
{
	int error;

	/* Multicast table state shared with the device */
	error = iflib_dma_alloc_align(sc->vmx_ctx,
	    VMXNET3_MULTICAST_MAX * ETHER_ADDR_LEN, 32, &sc->vmx_mcast_dma, 0);
	if (error)
		device_printf(sc->vmx_dev, "unable to alloc multicast table\n");
	else
		sc->vmx_mcast = sc->vmx_mcast_dma.idi_vaddr;

	return (error);
}