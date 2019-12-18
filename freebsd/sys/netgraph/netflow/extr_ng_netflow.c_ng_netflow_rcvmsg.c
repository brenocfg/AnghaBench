#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct ngnf_show_header {int dummy; } ;
struct ng_netflow_v9info {int dummy; } ;
struct ng_netflow_settimeouts {int /*<<< orphan*/  active_timeout; int /*<<< orphan*/  inactive_timeout; } ;
struct ng_netflow_settemplate {int /*<<< orphan*/  time; int /*<<< orphan*/  packets; } ;
struct ng_netflow_setmtu {int /*<<< orphan*/  mtu; } ;
struct ng_netflow_setifindex {size_t const iface; int /*<<< orphan*/  index; } ;
struct ng_netflow_setdlt {size_t const iface; int /*<<< orphan*/  dlt; } ;
struct ng_netflow_setconfig {size_t const iface; int /*<<< orphan*/  conf; } ;
struct ng_netflow_info {int dummy; } ;
struct ng_netflow_ifinfo {int dummy; } ;
struct TYPE_8__ {int ifinfo_dlt; int /*<<< orphan*/  conf; int /*<<< orphan*/  ifinfo_index; } ;
struct ng_netflow_iface {TYPE_1__ info; int /*<<< orphan*/ * hook; } ;
struct TYPE_9__ {int typecookie; int arglen; int /*<<< orphan*/  cmd; } ;
struct ng_mesg {scalar_t__ data; TYPE_2__ header; } ;
typedef  TYPE_3__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_10__ {int /*<<< orphan*/  mtu; int /*<<< orphan*/  templ_time; int /*<<< orphan*/  templ_packets; struct ng_netflow_iface* ifaces; int /*<<< orphan*/  nfinfo_act_t; int /*<<< orphan*/  nfinfo_inact_t; } ;

/* Variables and functions */
#define  DLT_EN10MB 140 
#define  DLT_RAW 139 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERROUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_MTU ; 
 int /*<<< orphan*/  MIN_MTU ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_NETFLOW_COOKIE 138 
#define  NGM_NETFLOW_IFINFO 137 
#define  NGM_NETFLOW_INFO 136 
#define  NGM_NETFLOW_SETCONFIG 135 
#define  NGM_NETFLOW_SETDLT 134 
#define  NGM_NETFLOW_SETIFINDEX 133 
#define  NGM_NETFLOW_SETMTU 132 
#define  NGM_NETFLOW_SETTEMPLATE 131 
#define  NGM_NETFLOW_SETTIMEOUTS 130 
#define  NGM_NETFLOW_SHOW 129 
#define  NGM_NETFLOW_V9INFO 128 
 int NGRESP_SIZE ; 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 size_t const NG_NETFLOW_MAXIFACES ; 
 TYPE_3__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  ng_netflow_copyinfo (TYPE_3__* const,struct ng_netflow_info*) ; 
 int /*<<< orphan*/  ng_netflow_copyv9info (TYPE_3__* const,struct ng_netflow_v9info*) ; 
 int ng_netflow_flow_show (TYPE_3__* const,struct ngnf_show_header*,struct ngnf_show_header*) ; 

__attribute__((used)) static int
ng_netflow_rcvmsg (node_p node, item_p item, hook_p lasthook)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_mesg *resp = NULL;
	int error = 0;
	struct ng_mesg *msg;

	NGI_GET_MSG(item, msg);

	/* Deal with message according to cookie and command */
	switch (msg->header.typecookie) {
	case NGM_NETFLOW_COOKIE:
		switch (msg->header.cmd) {
		case NGM_NETFLOW_INFO:
		    {
			struct ng_netflow_info *i;

			NG_MKRESPONSE(resp, msg, sizeof(struct ng_netflow_info),
			    M_NOWAIT);
			i = (struct ng_netflow_info *)resp->data;
			ng_netflow_copyinfo(priv, i);

			break;
		    }
		case NGM_NETFLOW_IFINFO:
		    {
			struct ng_netflow_ifinfo *i;
			const uint16_t *index;

			if (msg->header.arglen != sizeof(uint16_t))
				 ERROUT(EINVAL);

			index  = (uint16_t *)msg->data;
			if (*index >= NG_NETFLOW_MAXIFACES)
				ERROUT(EINVAL);

			/* connected iface? */
			if (priv->ifaces[*index].hook == NULL)
				 ERROUT(EINVAL);

			NG_MKRESPONSE(resp, msg,
			     sizeof(struct ng_netflow_ifinfo), M_NOWAIT);
			i = (struct ng_netflow_ifinfo *)resp->data;
			memcpy((void *)i, (void *)&priv->ifaces[*index].info,
			    sizeof(priv->ifaces[*index].info));

			break;
		    }
		case NGM_NETFLOW_SETDLT:
		    {
			struct ng_netflow_setdlt *set;
			struct ng_netflow_iface *iface;

			if (msg->header.arglen !=
			    sizeof(struct ng_netflow_setdlt))
				ERROUT(EINVAL);

			set = (struct ng_netflow_setdlt *)msg->data;
			if (set->iface >= NG_NETFLOW_MAXIFACES)
				ERROUT(EINVAL);
			iface = &priv->ifaces[set->iface];

			/* connected iface? */
			if (iface->hook == NULL)
				ERROUT(EINVAL);

			switch (set->dlt) {
			case	DLT_EN10MB:
				iface->info.ifinfo_dlt = DLT_EN10MB;
				break;
			case	DLT_RAW:
				iface->info.ifinfo_dlt = DLT_RAW;
				break;
			default:
				ERROUT(EINVAL);
			}
			break;
		    }
		case NGM_NETFLOW_SETIFINDEX:
		    {
			struct ng_netflow_setifindex *set;
			struct ng_netflow_iface *iface;

			if (msg->header.arglen !=
			    sizeof(struct ng_netflow_setifindex))
				ERROUT(EINVAL);

			set = (struct ng_netflow_setifindex *)msg->data;
			if (set->iface >= NG_NETFLOW_MAXIFACES)
				ERROUT(EINVAL);
			iface = &priv->ifaces[set->iface];

			/* connected iface? */
			if (iface->hook == NULL)
				ERROUT(EINVAL);

			iface->info.ifinfo_index = set->index;

			break;
		    }
		case NGM_NETFLOW_SETTIMEOUTS:
		    {
			struct ng_netflow_settimeouts *set;

			if (msg->header.arglen !=
			    sizeof(struct ng_netflow_settimeouts))
				ERROUT(EINVAL);

			set = (struct ng_netflow_settimeouts *)msg->data;

			priv->nfinfo_inact_t = set->inactive_timeout;
			priv->nfinfo_act_t = set->active_timeout;

			break;
		    }
		case NGM_NETFLOW_SETCONFIG:
		    {
			struct ng_netflow_setconfig *set;

			if (msg->header.arglen !=
			    sizeof(struct ng_netflow_setconfig))
				ERROUT(EINVAL);

			set = (struct ng_netflow_setconfig *)msg->data;

			if (set->iface >= NG_NETFLOW_MAXIFACES)
				ERROUT(EINVAL);
			
			priv->ifaces[set->iface].info.conf = set->conf;
	
			break;
		    }
		case NGM_NETFLOW_SETTEMPLATE:
		    {
			struct ng_netflow_settemplate *set;

			if (msg->header.arglen !=
			    sizeof(struct ng_netflow_settemplate))
				ERROUT(EINVAL);

			set = (struct ng_netflow_settemplate *)msg->data;

			priv->templ_packets = set->packets;
			priv->templ_time = set->time;

			break;
		    }
		case NGM_NETFLOW_SETMTU:
		    {
			struct ng_netflow_setmtu *set;

			if (msg->header.arglen !=
			    sizeof(struct ng_netflow_setmtu))
				ERROUT(EINVAL);

			set = (struct ng_netflow_setmtu *)msg->data;
			if ((set->mtu < MIN_MTU) || (set->mtu > MAX_MTU))
				ERROUT(EINVAL);

			priv->mtu = set->mtu;

			break;
		    }
		case NGM_NETFLOW_SHOW:
			if (msg->header.arglen !=
			    sizeof(struct ngnf_show_header))
				ERROUT(EINVAL);

			NG_MKRESPONSE(resp, msg, NGRESP_SIZE, M_NOWAIT);

			if (!resp)
				ERROUT(ENOMEM);

			error = ng_netflow_flow_show(priv,
			    (struct ngnf_show_header *)msg->data,
			    (struct ngnf_show_header *)resp->data);

			if (error)
				NG_FREE_MSG(resp);

			break;
		case NGM_NETFLOW_V9INFO:
		    {
			struct ng_netflow_v9info *i;

			NG_MKRESPONSE(resp, msg,
			    sizeof(struct ng_netflow_v9info), M_NOWAIT);
			i = (struct ng_netflow_v9info *)resp->data;
			ng_netflow_copyv9info(priv, i);

			break;
		    }
		default:
			ERROUT(EINVAL);		/* unknown command */
			break;
		}
		break;
	default:
		ERROUT(EINVAL);		/* incorrect cookie */
		break;
	}

	/*
	 * Take care of synchronous response, if any.
	 * Free memory and return.
	 */
done:
	NG_RESPOND_MSG(error, node, item, resp);
	NG_FREE_MSG(msg);

	return (error);
}