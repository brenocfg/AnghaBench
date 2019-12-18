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
typedef  int /*<<< orphan*/  uint32_t ;
struct ipsec_softc {struct ifnet* ifp; int /*<<< orphan*/  fibnum; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_output; int /*<<< orphan*/  if_qflush; int /*<<< orphan*/  if_transmit; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_mtu; scalar_t__ if_addrlen; struct ipsec_softc* if_softc; } ;
struct if_clone {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {TYPE_1__* td_proc; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_fibnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_NULL ; 
 int IFF_MULTICAST ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IFT_TUNNEL ; 
 int /*<<< orphan*/  IPSEC_MTU ; 
 int /*<<< orphan*/  M_IPSEC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bpfattach (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* curthread ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_attach (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipsec_ioctl ; 
 int /*<<< orphan*/  ipsec_output ; 
 int /*<<< orphan*/  ipsec_qflush ; 
 int /*<<< orphan*/  ipsec_transmit ; 
 int /*<<< orphan*/  ipsecname ; 
 struct ipsec_softc* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ipsec_clone_create(struct if_clone *ifc, int unit, caddr_t params)
{
	struct ipsec_softc *sc;
	struct ifnet *ifp;

	sc = malloc(sizeof(*sc), M_IPSEC, M_WAITOK | M_ZERO);
	sc->fibnum = curthread->td_proc->p_fibnum;
	sc->ifp = ifp = if_alloc(IFT_TUNNEL);
	ifp->if_softc = sc;
	if_initname(ifp, ipsecname, unit);

	ifp->if_addrlen = 0;
	ifp->if_mtu = IPSEC_MTU;
	ifp->if_flags  = IFF_POINTOPOINT | IFF_MULTICAST;
	ifp->if_ioctl  = ipsec_ioctl;
	ifp->if_transmit  = ipsec_transmit;
	ifp->if_qflush  = ipsec_qflush;
	ifp->if_output = ipsec_output;
	if_attach(ifp);
	bpfattach(ifp, DLT_NULL, sizeof(uint32_t));

	return (0);
}