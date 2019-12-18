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
struct vmxnet3_softc {TYPE_1__* vmx_ds; int /*<<< orphan*/  vmx_vlan_filter; struct ifnet* vmx_ifp; } ;
struct ifnet {int if_capenable; } ;
struct TYPE_2__ {int /*<<< orphan*/  vlan_filter; } ;

/* Variables and functions */
 int IFCAP_VLAN_HWFILTER ; 
 int /*<<< orphan*/  VMXNET3_CMD_VLAN_FILTER ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_getflags (struct ifnet*) ; 
 int /*<<< orphan*/  vmxnet3_set_rxfilter (struct vmxnet3_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_write_cmd (struct vmxnet3_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_reinit_rxfilters(struct vmxnet3_softc *sc)
{
	struct ifnet *ifp;

	ifp = sc->vmx_ifp;

	vmxnet3_set_rxfilter(sc, if_getflags(ifp));

	if (ifp->if_capenable & IFCAP_VLAN_HWFILTER)
		bcopy(sc->vmx_vlan_filter, sc->vmx_ds->vlan_filter,
		    sizeof(sc->vmx_ds->vlan_filter));
	else
		bzero(sc->vmx_ds->vlan_filter,
		    sizeof(sc->vmx_ds->vlan_filter));
	vmxnet3_write_cmd(sc, VMXNET3_CMD_VLAN_FILTER);
}