#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ndis_softc {int dummy; } ;
struct mtx {int dummy; } ;
typedef  int /*<<< orphan*/  ndis_status ;
struct TYPE_11__ {int /*<<< orphan*/  ni_introbj; int /*<<< orphan*/  ni_dpc; int /*<<< orphan*/  ni_dpcevt; int /*<<< orphan*/  ni_dpcfunc; int /*<<< orphan*/  ni_isrfunc; scalar_t__ ni_dpccnt; void* ni_shared; void* ni_isrreq; void* ni_block; int /*<<< orphan*/ * ni_rsvd; } ;
typedef  TYPE_3__ ndis_miniport_interrupt ;
struct TYPE_12__ {int /*<<< orphan*/  nmc_interrupt_func; int /*<<< orphan*/  nmc_isr_func; } ;
typedef  TYPE_4__ ndis_miniport_characteristics ;
struct TYPE_13__ {TYPE_3__* nmb_interrupt; TYPE_2__* nmb_deviceobj; TYPE_1__* nmb_physdeviceobj; } ;
typedef  TYPE_5__ ndis_miniport_block ;
typedef  int /*<<< orphan*/  ndis_interrupt_mode ;
typedef  void* ndis_handle ;
typedef  int /*<<< orphan*/  funcptr ;
struct TYPE_10__ {int /*<<< orphan*/  do_drvobj; } ;
struct TYPE_9__ {int /*<<< orphan*/  do_devext; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TYPE_NOTIFY ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int IoConnectInterrupt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ndis_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* IoGetDriverObjectExtension (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  KDPC_IMPORTANCE_LOW ; 
 int /*<<< orphan*/  KeInitializeDpc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeSetImportanceDpc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDIS_STATUS_FAILURE ; 
 int /*<<< orphan*/  NDIS_STATUS_RESOURCES ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 struct ndis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndis_findwrap (int /*<<< orphan*/ ) ; 
 scalar_t__ ndis_intr ; 
 scalar_t__ ndis_intrhand ; 

__attribute__((used)) static ndis_status
NdisMRegisterInterrupt(ndis_miniport_interrupt *intr, ndis_handle adapter,
    uint32_t ivec, uint32_t ilevel, uint8_t reqisr, uint8_t shared,
    ndis_interrupt_mode imode)
{
	ndis_miniport_block	*block;
	ndis_miniport_characteristics *ch;
	struct ndis_softc	*sc;
	int			error;

	block = adapter;
	sc = device_get_softc(block->nmb_physdeviceobj->do_devext);
	ch = IoGetDriverObjectExtension(block->nmb_deviceobj->do_drvobj,
	    (void *)1);

	intr->ni_rsvd = ExAllocatePoolWithTag(NonPagedPool,
	    sizeof(struct mtx), 0);
	if (intr->ni_rsvd == NULL)
		return (NDIS_STATUS_RESOURCES);

	intr->ni_block = adapter;
	intr->ni_isrreq = reqisr;
	intr->ni_shared = shared;
	intr->ni_dpccnt = 0;
	intr->ni_isrfunc = ch->nmc_isr_func;
	intr->ni_dpcfunc = ch->nmc_interrupt_func;

	KeInitializeEvent(&intr->ni_dpcevt, EVENT_TYPE_NOTIFY, TRUE);
	KeInitializeDpc(&intr->ni_dpc,
	    ndis_findwrap((funcptr)ndis_intrhand), intr);
	KeSetImportanceDpc(&intr->ni_dpc, KDPC_IMPORTANCE_LOW);

	error = IoConnectInterrupt(&intr->ni_introbj,
	    ndis_findwrap((funcptr)ndis_intr), sc, NULL,
	    ivec, ilevel, 0, imode, shared, 0, FALSE);

	if (error != STATUS_SUCCESS)
		return (NDIS_STATUS_FAILURE);

	block->nmb_interrupt = intr;

	return (NDIS_STATUS_SUCCESS);
}