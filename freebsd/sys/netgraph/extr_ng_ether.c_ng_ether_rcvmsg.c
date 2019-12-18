#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  int u_char ;
struct sockaddr_dl {int sdl_len; int sdl_alen; void* sdl_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_11__ {int typecookie; int arglen; int /*<<< orphan*/  cmd; } ;
struct ng_mesg {scalar_t__ data; TYPE_1__ header; } ;
struct ifmultiaddr {int dummy; } ;
struct epoch_tracker {int dummy; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_13__ {int if_index; int /*<<< orphan*/  if_xname; } ;
struct TYPE_12__ {int promisc; int autoSrcAddr; TYPE_3__* ifp; } ;

/* Variables and functions */
 void* AF_LINK ; 
 int EADDRINUSE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETHER_ADDR_LEN ; 
 int IFNAMSIZ ; 
 void* IF_LLADDR (TYPE_3__*) ; 
 scalar_t__ LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_ETHER_ADD_MULTI 139 
#define  NGM_ETHER_COOKIE 138 
#define  NGM_ETHER_DEL_MULTI 137 
#define  NGM_ETHER_DETACH 136 
#define  NGM_ETHER_GET_AUTOSRC 135 
#define  NGM_ETHER_GET_ENADDR 134 
#define  NGM_ETHER_GET_IFINDEX 133 
#define  NGM_ETHER_GET_IFNAME 132 
#define  NGM_ETHER_GET_PROMISC 131 
#define  NGM_ETHER_SET_AUTOSRC 130 
#define  NGM_ETHER_SET_ENADDR 129 
#define  NGM_ETHER_SET_PROMISC 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  bcopy (void*,scalar_t__,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_dl*,int) ; 
 int if_addmulti (TYPE_3__*,struct sockaddr*,struct ifmultiaddr**) ; 
 int if_delmulti (TYPE_3__*,struct sockaddr*) ; 
 struct ifmultiaddr* if_findmulti (TYPE_3__*,struct sockaddr*) ; 
 int if_setlladdr (TYPE_3__*,int*,int) ; 
 int ifpromisc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ng_ether_detach (TYPE_3__*) ; 
 int /*<<< orphan*/  strlcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ng_ether_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_mesg *resp = NULL;
	int error = 0;
	struct ng_mesg *msg;

	NGI_GET_MSG(item, msg);
	switch (msg->header.typecookie) {
	case NGM_ETHER_COOKIE:
		switch (msg->header.cmd) {
		case NGM_ETHER_GET_IFNAME:
			NG_MKRESPONSE(resp, msg, IFNAMSIZ, M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				break;
			}
			strlcpy(resp->data, priv->ifp->if_xname, IFNAMSIZ);
			break;
		case NGM_ETHER_GET_IFINDEX:
			NG_MKRESPONSE(resp, msg, sizeof(u_int32_t), M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				break;
			}
			*((u_int32_t *)resp->data) = priv->ifp->if_index;
			break;
		case NGM_ETHER_GET_ENADDR:
			NG_MKRESPONSE(resp, msg, ETHER_ADDR_LEN, M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				break;
			}
			bcopy(IF_LLADDR(priv->ifp),
			    resp->data, ETHER_ADDR_LEN);
			break;
		case NGM_ETHER_SET_ENADDR:
		    {
			if (msg->header.arglen != ETHER_ADDR_LEN) {
				error = EINVAL;
				break;
			}
			error = if_setlladdr(priv->ifp,
			    (u_char *)msg->data, ETHER_ADDR_LEN);
			break;
		    }
		case NGM_ETHER_GET_PROMISC:
			NG_MKRESPONSE(resp, msg, sizeof(u_int32_t), M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				break;
			}
			*((u_int32_t *)resp->data) = priv->promisc;
			break;
		case NGM_ETHER_SET_PROMISC:
		    {
			u_char want;

			if (msg->header.arglen != sizeof(u_int32_t)) {
				error = EINVAL;
				break;
			}
			want = !!*((u_int32_t *)msg->data);
			if (want ^ priv->promisc) {
				if ((error = ifpromisc(priv->ifp, want)) != 0)
					break;
				priv->promisc = want;
			}
			break;
		    }
		case NGM_ETHER_GET_AUTOSRC:
			NG_MKRESPONSE(resp, msg, sizeof(u_int32_t), M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				break;
			}
			*((u_int32_t *)resp->data) = priv->autoSrcAddr;
			break;
		case NGM_ETHER_SET_AUTOSRC:
			if (msg->header.arglen != sizeof(u_int32_t)) {
				error = EINVAL;
				break;
			}
			priv->autoSrcAddr = !!*((u_int32_t *)msg->data);
			break;
		case NGM_ETHER_ADD_MULTI:
		    {
			struct sockaddr_dl sa_dl;
			struct epoch_tracker et;
			struct ifmultiaddr *ifma;

			if (msg->header.arglen != ETHER_ADDR_LEN) {
				error = EINVAL;
				break;
			}
			bzero(&sa_dl, sizeof(struct sockaddr_dl));
			sa_dl.sdl_len = sizeof(struct sockaddr_dl);
			sa_dl.sdl_family = AF_LINK;
			sa_dl.sdl_alen = ETHER_ADDR_LEN;
			bcopy((void *)msg->data, LLADDR(&sa_dl),
			    ETHER_ADDR_LEN);
			/*
			 * Netgraph is only permitted to join groups once
			 * via the if_addmulti() KPI, because it cannot hold
			 * struct ifmultiaddr * between calls. It may also
			 * lose a race while we check if the membership
			 * already exists.
			 */
			NET_EPOCH_ENTER(et);
			ifma = if_findmulti(priv->ifp,
			    (struct sockaddr *)&sa_dl);
			NET_EPOCH_EXIT(et);
			if (ifma != NULL) {
				error = EADDRINUSE;
			} else {
				error = if_addmulti(priv->ifp,
				    (struct sockaddr *)&sa_dl, &ifma);
			}
			break;
		    }
		case NGM_ETHER_DEL_MULTI:
		    {
			struct sockaddr_dl sa_dl;

			if (msg->header.arglen != ETHER_ADDR_LEN) {
				error = EINVAL;
				break;
			}
			bzero(&sa_dl, sizeof(struct sockaddr_dl));
			sa_dl.sdl_len = sizeof(struct sockaddr_dl);
			sa_dl.sdl_family = AF_LINK;
			sa_dl.sdl_alen = ETHER_ADDR_LEN;
			bcopy((void *)msg->data, LLADDR(&sa_dl),
			    ETHER_ADDR_LEN);
			error = if_delmulti(priv->ifp,
			    (struct sockaddr *)&sa_dl);
			break;
		    }
		case NGM_ETHER_DETACH:
			ng_ether_detach(priv->ifp);
			break;
		default:
			error = EINVAL;
			break;
		}
		break;
	default:
		error = EINVAL;
		break;
	}
	NG_RESPOND_MSG(error, node, item, resp);
	NG_FREE_MSG(msg);
	return (error);
}