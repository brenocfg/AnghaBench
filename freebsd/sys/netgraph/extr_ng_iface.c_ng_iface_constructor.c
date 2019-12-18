#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_8__ {int /*<<< orphan*/  ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_baudrate; int /*<<< orphan*/  if_xname; TYPE_5__ if_snd; scalar_t__ if_hdrlen; scalar_t__ if_addrlen; int /*<<< orphan*/  if_type; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_output; TYPE_1__* if_softc; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_7__ {int /*<<< orphan*/  unit; int /*<<< orphan*/  node; struct ifnet* ifp; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_NULL ; 
 int ENOMEM ; 
 int IFF_MULTICAST ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_5__*) ; 
 int /*<<< orphan*/  IFT_PROPVIRTUAL ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  M_NETGRAPH_IFACE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_IFACE_IFACE_NAME ; 
 int /*<<< orphan*/  NG_IFACE_MTU_DEFAULT ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  V_ng_iface_unit ; 
 int /*<<< orphan*/  alloc_unr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpfattach (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_attach (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ng_iface_ioctl ; 
 int /*<<< orphan*/  ng_iface_output ; 
 int /*<<< orphan*/  ng_iface_start ; 
 scalar_t__ ng_name_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
ng_iface_constructor(node_p node)
{
	struct ifnet *ifp;
	priv_p priv;

	/* Allocate node and interface private structures */
	priv = malloc(sizeof(*priv), M_NETGRAPH_IFACE, M_WAITOK | M_ZERO);
	ifp = if_alloc(IFT_PROPVIRTUAL);
	if (ifp == NULL) {
		free(priv, M_NETGRAPH_IFACE);
		return (ENOMEM);
	}

	rm_init(&priv->lock, "ng_iface private rmlock");

	/* Link them together */
	ifp->if_softc = priv;
	priv->ifp = ifp;

	/* Get an interface unit number */
	priv->unit = alloc_unr(V_ng_iface_unit);

	/* Link together node and private info */
	NG_NODE_SET_PRIVATE(node, priv);
	priv->node = node;

	/* Initialize interface structure */
	if_initname(ifp, NG_IFACE_IFACE_NAME, priv->unit);
	ifp->if_output = ng_iface_output;
	ifp->if_start = ng_iface_start;
	ifp->if_ioctl = ng_iface_ioctl;
	ifp->if_mtu = NG_IFACE_MTU_DEFAULT;
	ifp->if_flags = (IFF_SIMPLEX|IFF_POINTOPOINT|IFF_NOARP|IFF_MULTICAST);
	ifp->if_type = IFT_PROPVIRTUAL;		/* XXX */
	ifp->if_addrlen = 0;			/* XXX */
	ifp->if_hdrlen = 0;			/* XXX */
	ifp->if_baudrate = 64000;		/* XXX */
	IFQ_SET_MAXLEN(&ifp->if_snd, ifqmaxlen);
	ifp->if_snd.ifq_drv_maxlen = ifqmaxlen;
	IFQ_SET_READY(&ifp->if_snd);

	/* Give this node the same name as the interface (if possible) */
	if (ng_name_node(node, ifp->if_xname) != 0)
		log(LOG_WARNING, "%s: can't acquire netgraph name\n",
		    ifp->if_xname);

	/* Attach the interface */
	if_attach(ifp);
	bpfattach(ifp, DLT_NULL, sizeof(u_int32_t));

	/* Done */
	return (0);
}