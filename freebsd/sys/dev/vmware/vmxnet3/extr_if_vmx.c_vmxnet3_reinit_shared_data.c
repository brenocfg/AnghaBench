#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int idi_paddr; } ;
struct vmxnet3_softc {int vmx_flags; TYPE_1__ vmx_ds_dma; TYPE_2__* vmx_scctx; struct vmxnet3_driver_shared* vmx_ds; struct ifnet* vmx_ifp; } ;
struct vmxnet3_driver_shared {int /*<<< orphan*/  upt_features; int /*<<< orphan*/  nrxqueue; int /*<<< orphan*/  ntxqueue; int /*<<< orphan*/  mtu; } ;
struct ifnet {int if_capenable; int /*<<< orphan*/  if_mtu; } ;
typedef  TYPE_2__* if_softc_ctx_t ;
struct TYPE_4__ {int /*<<< orphan*/  isc_nrxqsets; int /*<<< orphan*/  isc_ntxqsets; } ;

/* Variables and functions */
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int /*<<< orphan*/  UPT1_F_CSUM ; 
 int /*<<< orphan*/  UPT1_F_LRO ; 
 int /*<<< orphan*/  UPT1_F_RSS ; 
 int /*<<< orphan*/  UPT1_F_VLAN ; 
 int /*<<< orphan*/  VMXNET3_BAR1_DSH ; 
 int /*<<< orphan*/  VMXNET3_BAR1_DSL ; 
 int VMXNET3_FLAG_RSS ; 
 int /*<<< orphan*/  vmxnet3_reinit_rss_shared_data (struct vmxnet3_softc*) ; 
 int /*<<< orphan*/  vmxnet3_write_bar1 (struct vmxnet3_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmxnet3_reinit_shared_data(struct vmxnet3_softc *sc)
{
	struct ifnet *ifp;
	struct vmxnet3_driver_shared *ds;
	if_softc_ctx_t scctx;
	
	ifp = sc->vmx_ifp;
	ds = sc->vmx_ds;
	scctx = sc->vmx_scctx;
	
	ds->mtu = ifp->if_mtu;
	ds->ntxqueue = scctx->isc_ntxqsets;
	ds->nrxqueue = scctx->isc_nrxqsets;

	ds->upt_features = 0;
	if (ifp->if_capenable & (IFCAP_RXCSUM | IFCAP_RXCSUM_IPV6))
		ds->upt_features |= UPT1_F_CSUM;
	if (ifp->if_capenable & IFCAP_VLAN_HWTAGGING)
		ds->upt_features |= UPT1_F_VLAN;
	if (ifp->if_capenable & IFCAP_LRO)
		ds->upt_features |= UPT1_F_LRO;

	if (sc->vmx_flags & VMXNET3_FLAG_RSS) {
		ds->upt_features |= UPT1_F_RSS;
		vmxnet3_reinit_rss_shared_data(sc);
	}

	vmxnet3_write_bar1(sc, VMXNET3_BAR1_DSL, sc->vmx_ds_dma.idi_paddr);
	vmxnet3_write_bar1(sc, VMXNET3_BAR1_DSH,
	    (uint64_t) sc->vmx_ds_dma.idi_paddr >> 32);
}