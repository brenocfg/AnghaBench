#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct sppp {int dummy; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; TYPE_1__* if_softc; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_8__ {int /*<<< orphan*/  if_xname; } ;
struct TYPE_7__ {int /*<<< orphan*/  unit; int /*<<< orphan*/  node; struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_NULL ; 
 int ENOSPC ; 
 int IFF_MULTICAST ; 
 int IFF_POINTOPOINT ; 
 struct sppp* IFP2SP (struct ifnet*) ; 
 int /*<<< orphan*/  IFT_PPP ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  M_NETGRAPH_SPPP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  NG_SPPP_IFACE_NAME ; 
 TYPE_3__* SP2IFP (struct sppp*) ; 
 int /*<<< orphan*/  bpfattach (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_attach (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ng_name_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_sppp_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_sppp_ioctl ; 
 int /*<<< orphan*/  ng_sppp_start ; 
 int /*<<< orphan*/  sppp_attach (struct ifnet*) ; 

__attribute__((used)) static int
ng_sppp_constructor (node_p node)
{
	struct sppp *pp;
	struct ifnet *ifp;
	priv_p priv;

	/* Allocate node and interface private structures */
	priv = malloc(sizeof(*priv), M_NETGRAPH_SPPP, M_WAITOK | M_ZERO);

	ifp = if_alloc(IFT_PPP);
	if (ifp == NULL) {
		free (priv, M_NETGRAPH_SPPP);
		return (ENOSPC);
	}
	pp = IFP2SP(ifp);

	/* Link them together */
	ifp->if_softc = priv;
	priv->ifp = ifp;

	/* Get an interface unit number */
	ng_sppp_get_unit(&priv->unit);

	/* Link together node and private info */
	NG_NODE_SET_PRIVATE (node, priv);
	priv->node = node;

	/* Initialize interface structure */
	if_initname (SP2IFP(pp), NG_SPPP_IFACE_NAME, priv->unit);
	ifp->if_start = ng_sppp_start;
	ifp->if_ioctl = ng_sppp_ioctl;
	ifp->if_flags = (IFF_POINTOPOINT|IFF_MULTICAST);

	/* Give this node the same name as the interface (if possible) */
	if (ng_name_node(node, SP2IFP(pp)->if_xname) != 0)
		log (LOG_WARNING, "%s: can't acquire netgraph name\n",
		    SP2IFP(pp)->if_xname);

	/* Attach the interface */
	sppp_attach (ifp);
	if_attach (ifp);
	bpfattach (ifp, DLT_NULL, sizeof(u_int32_t));

	/* Done */
	return (0);
}