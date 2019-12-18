#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct thread {int dummy; } ;
struct socket {int dummy; } ;
struct nodeinfo {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {scalar_t__ token; int /*<<< orphan*/  cmd; } ;
struct ng_mesg {scalar_t__ data; TYPE_2__ header; } ;
struct ng_btsocket_hci_raw_node_state {int /*<<< orphan*/  state; } ;
struct ng_btsocket_hci_raw_node_stat {int /*<<< orphan*/  stat; } ;
struct ng_btsocket_hci_raw_node_role_switch {int /*<<< orphan*/  role_switch; } ;
struct ng_btsocket_hci_raw_node_packet_mask {int /*<<< orphan*/  packet_mask; } ;
struct ng_btsocket_hci_raw_node_neighbor_cache {int num_entries; int /*<<< orphan*/ * entries; } ;
struct ng_btsocket_hci_raw_node_list_names {struct nodeinfo* names; struct nodeinfo* num_names; } ;
struct ng_btsocket_hci_raw_node_link_policy_mask {int /*<<< orphan*/  policy_mask; } ;
struct ng_btsocket_hci_raw_node_features {int /*<<< orphan*/  features; } ;
struct ng_btsocket_hci_raw_node_debug {int /*<<< orphan*/  debug; } ;
struct ng_btsocket_hci_raw_node_buffer {int /*<<< orphan*/  buffer; } ;
struct ng_btsocket_hci_raw_node_bdaddr {int /*<<< orphan*/  bdaddr; } ;
struct ng_btsocket_hci_raw_con_list {int num_connections; int /*<<< orphan*/ * connections; } ;
struct namelist {int /*<<< orphan*/  numnames; struct nodeinfo* nodeinfo; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  ng_hci_node_neighbor_cache_entry_ep ;
struct TYPE_10__ {int /*<<< orphan*/  num_entries; } ;
typedef  TYPE_3__ ng_hci_node_get_neighbor_cache_ep ;
struct TYPE_11__ {int /*<<< orphan*/  num_connections; } ;
typedef  TYPE_4__ ng_hci_node_con_list_ep ;
typedef  int /*<<< orphan*/  ng_hci_node_con_ep ;
typedef  TYPE_5__* ng_btsocket_hci_raw_pcb_p ;
typedef  scalar_t__ caddr_t ;
struct TYPE_8__ {scalar_t__* hci_node; } ;
struct TYPE_12__ {scalar_t__ token; int flags; int /*<<< orphan*/  pcb_mtx; struct ng_mesg* msg; TYPE_1__ addr; } ;

/* Variables and functions */
 int EBUSY ; 
 int EHOSTUNREACH ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_HCI_COOKIE ; 
 int /*<<< orphan*/  NGM_HCI_NODE_FLUSH_NEIGHBOR_CACHE ; 
 int /*<<< orphan*/  NGM_HCI_NODE_GET_BDADDR ; 
 int /*<<< orphan*/  NGM_HCI_NODE_GET_BUFFER ; 
 int /*<<< orphan*/  NGM_HCI_NODE_GET_CON_LIST ; 
 int /*<<< orphan*/  NGM_HCI_NODE_GET_DEBUG ; 
 int /*<<< orphan*/  NGM_HCI_NODE_GET_FEATURES ; 
 int /*<<< orphan*/  NGM_HCI_NODE_GET_LINK_POLICY_SETTINGS_MASK ; 
 int /*<<< orphan*/  NGM_HCI_NODE_GET_NEIGHBOR_CACHE ; 
 int /*<<< orphan*/  NGM_HCI_NODE_GET_PACKET_MASK ; 
 int /*<<< orphan*/  NGM_HCI_NODE_GET_ROLE_SWITCH ; 
 int /*<<< orphan*/  NGM_HCI_NODE_GET_STAT ; 
 int /*<<< orphan*/  NGM_HCI_NODE_GET_STATE ; 
 int /*<<< orphan*/  NGM_HCI_NODE_INIT ; 
 int /*<<< orphan*/  NGM_HCI_NODE_RESET_STAT ; 
 int /*<<< orphan*/  NGM_HCI_NODE_SET_DEBUG ; 
 int /*<<< orphan*/  NGM_HCI_NODE_SET_LINK_POLICY_SETTINGS_MASK ; 
 int /*<<< orphan*/  NGM_HCI_NODE_SET_PACKET_MASK ; 
 int /*<<< orphan*/  NGM_HCI_NODE_SET_ROLE_SWITCH ; 
 int /*<<< orphan*/  NGM_LISTNAMES ; 
 int NG_BTSOCKET_HCI_RAW_PRIVILEGED ; 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int NG_HCI_MAX_CON_NUM ; 
 int NG_HCI_MAX_NEIGHBOR_NUM ; 
 int /*<<< orphan*/  NG_HCI_NODE_TYPE ; 
 int /*<<< orphan*/  NG_MKMESSAGE (struct ng_mesg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODESIZ ; 
 int /*<<< orphan*/  NG_SEND_MSG_PATH (int,int /*<<< orphan*/ *,struct ng_mesg*,char*,int /*<<< orphan*/ ) ; 
 int PCATCH ; 
 int PZERO ; 
#define  SIOC_HCI_RAW_NODE_FLUSH_NEIGHBOR_CACHE 146 
#define  SIOC_HCI_RAW_NODE_GET_BDADDR 145 
#define  SIOC_HCI_RAW_NODE_GET_BUFFER 144 
#define  SIOC_HCI_RAW_NODE_GET_CON_LIST 143 
#define  SIOC_HCI_RAW_NODE_GET_DEBUG 142 
#define  SIOC_HCI_RAW_NODE_GET_FEATURES 141 
#define  SIOC_HCI_RAW_NODE_GET_LINK_POLICY_MASK 140 
#define  SIOC_HCI_RAW_NODE_GET_NEIGHBOR_CACHE 139 
#define  SIOC_HCI_RAW_NODE_GET_PACKET_MASK 138 
#define  SIOC_HCI_RAW_NODE_GET_ROLE_SWITCH 137 
#define  SIOC_HCI_RAW_NODE_GET_STAT 136 
#define  SIOC_HCI_RAW_NODE_GET_STATE 135 
#define  SIOC_HCI_RAW_NODE_INIT 134 
#define  SIOC_HCI_RAW_NODE_LIST_NAMES 133 
#define  SIOC_HCI_RAW_NODE_RESET_STAT 132 
#define  SIOC_HCI_RAW_NODE_SET_DEBUG 131 
#define  SIOC_HCI_RAW_NODE_SET_LINK_POLICY_MASK 130 
#define  SIOC_HCI_RAW_NODE_SET_PACKET_MASK 129 
#define  SIOC_HCI_RAW_NODE_SET_ROLE_SWITCH 128 
 int copyout (scalar_t__,scalar_t__,int) ; 
 int hz ; 
 void* min (int,int /*<<< orphan*/ ) ; 
 int msleep (struct ng_mesg**,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_btsocket_hci_raw_get_token (scalar_t__*) ; 
 int ng_btsocket_hci_raw_ioctl_timeout ; 
 int /*<<< orphan*/ * ng_btsocket_hci_raw_node ; 
 int ng_btsocket_hci_raw_send_ngmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ng_btsocket_hci_raw_send_sync_ngmsg (TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__*) ; 
 TYPE_5__* so2hci_raw_pcb (struct socket*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ng_btsocket_hci_raw_control(struct socket *so, u_long cmd, caddr_t data,
		struct ifnet *ifp, struct thread *td)
{
	ng_btsocket_hci_raw_pcb_p	 pcb = so2hci_raw_pcb(so);
	char				 path[NG_NODESIZ + 1];
	struct ng_mesg			*msg = NULL;
	int				 error = 0;

	if (pcb == NULL)
		return (EINVAL);
	if (ng_btsocket_hci_raw_node == NULL)
		return (EINVAL);

	mtx_lock(&pcb->pcb_mtx);

	/* Check if we have device name */
	if (pcb->addr.hci_node[0] == 0) {
		mtx_unlock(&pcb->pcb_mtx);
		return (EHOSTUNREACH);
	}

	/* Check if we have pending ioctl() */
	if (pcb->token != 0) {
		mtx_unlock(&pcb->pcb_mtx);
		return (EBUSY);
	}

	snprintf(path, sizeof(path), "%s:", pcb->addr.hci_node);

	switch (cmd) {
	case SIOC_HCI_RAW_NODE_GET_STATE: {
		struct ng_btsocket_hci_raw_node_state	*p =
			(struct ng_btsocket_hci_raw_node_state *) data;

		error = ng_btsocket_hci_raw_send_sync_ngmsg(pcb, path, 
				NGM_HCI_NODE_GET_STATE,
				&p->state, sizeof(p->state));
		} break;

	case SIOC_HCI_RAW_NODE_INIT:
		if (pcb->flags & NG_BTSOCKET_HCI_RAW_PRIVILEGED)
			error = ng_btsocket_hci_raw_send_ngmsg(path,
					NGM_HCI_NODE_INIT, NULL, 0);
		else
			error = EPERM;
		break;

	case SIOC_HCI_RAW_NODE_GET_DEBUG: {
		struct ng_btsocket_hci_raw_node_debug	*p = 
			(struct ng_btsocket_hci_raw_node_debug *) data;

		error = ng_btsocket_hci_raw_send_sync_ngmsg(pcb, path,
				NGM_HCI_NODE_GET_DEBUG,
				&p->debug, sizeof(p->debug));
		} break;

	case SIOC_HCI_RAW_NODE_SET_DEBUG: {
		struct ng_btsocket_hci_raw_node_debug	*p = 
			(struct ng_btsocket_hci_raw_node_debug *) data;

		if (pcb->flags & NG_BTSOCKET_HCI_RAW_PRIVILEGED)
			error = ng_btsocket_hci_raw_send_ngmsg(path,
					NGM_HCI_NODE_SET_DEBUG, &p->debug,
					sizeof(p->debug));
		else
			error = EPERM;
		} break;

	case SIOC_HCI_RAW_NODE_GET_BUFFER: {
		struct ng_btsocket_hci_raw_node_buffer	*p = 
			(struct ng_btsocket_hci_raw_node_buffer *) data;

		error = ng_btsocket_hci_raw_send_sync_ngmsg(pcb, path,
				NGM_HCI_NODE_GET_BUFFER,
				&p->buffer, sizeof(p->buffer));
		} break;

	case SIOC_HCI_RAW_NODE_GET_BDADDR: {
		struct ng_btsocket_hci_raw_node_bdaddr	*p = 
			(struct ng_btsocket_hci_raw_node_bdaddr *) data;

		error = ng_btsocket_hci_raw_send_sync_ngmsg(pcb, path,
				NGM_HCI_NODE_GET_BDADDR,
				&p->bdaddr, sizeof(p->bdaddr));
		} break;

	case SIOC_HCI_RAW_NODE_GET_FEATURES: {
		struct ng_btsocket_hci_raw_node_features	*p = 
			(struct ng_btsocket_hci_raw_node_features *) data;

		error = ng_btsocket_hci_raw_send_sync_ngmsg(pcb, path,
				NGM_HCI_NODE_GET_FEATURES,
				&p->features, sizeof(p->features));
		} break;

	case SIOC_HCI_RAW_NODE_GET_STAT: {
		struct ng_btsocket_hci_raw_node_stat	*p = 
			(struct ng_btsocket_hci_raw_node_stat *) data;

		error = ng_btsocket_hci_raw_send_sync_ngmsg(pcb, path,
				NGM_HCI_NODE_GET_STAT,
				&p->stat, sizeof(p->stat));
		} break;

	case SIOC_HCI_RAW_NODE_RESET_STAT:
		if (pcb->flags & NG_BTSOCKET_HCI_RAW_PRIVILEGED)
			error = ng_btsocket_hci_raw_send_ngmsg(path,
					NGM_HCI_NODE_RESET_STAT, NULL, 0);
		else
			error = EPERM;
		break;

	case SIOC_HCI_RAW_NODE_FLUSH_NEIGHBOR_CACHE:
		if (pcb->flags & NG_BTSOCKET_HCI_RAW_PRIVILEGED)
			error = ng_btsocket_hci_raw_send_ngmsg(path,
					NGM_HCI_NODE_FLUSH_NEIGHBOR_CACHE,
					NULL, 0);
		else
			error = EPERM;
		break;

	case SIOC_HCI_RAW_NODE_GET_NEIGHBOR_CACHE:  {
		struct ng_btsocket_hci_raw_node_neighbor_cache	*p = 
			(struct ng_btsocket_hci_raw_node_neighbor_cache *) data;
		ng_hci_node_get_neighbor_cache_ep		*p1 = NULL;
		ng_hci_node_neighbor_cache_entry_ep		*p2 = NULL;

		if (p->num_entries <= 0 || 
		    p->num_entries > NG_HCI_MAX_NEIGHBOR_NUM ||
		    p->entries == NULL) {
			mtx_unlock(&pcb->pcb_mtx);
			return (EINVAL);
		}

		NG_MKMESSAGE(msg, NGM_HCI_COOKIE,
			NGM_HCI_NODE_GET_NEIGHBOR_CACHE, 0, M_NOWAIT);
		if (msg == NULL) {
			mtx_unlock(&pcb->pcb_mtx);
			return (ENOMEM);
		}
		ng_btsocket_hci_raw_get_token(&msg->header.token);
		pcb->token = msg->header.token;
		pcb->msg = NULL;

		NG_SEND_MSG_PATH(error, ng_btsocket_hci_raw_node, msg, path, 0);
		if (error != 0) {
			pcb->token = 0;
			mtx_unlock(&pcb->pcb_mtx);
			return (error);
		}

		error = msleep(&pcb->msg, &pcb->pcb_mtx,
				PZERO|PCATCH, "hcictl", 
				ng_btsocket_hci_raw_ioctl_timeout * hz);
		pcb->token = 0;

		if (error != 0) {
			mtx_unlock(&pcb->pcb_mtx);
			return (error);
		}

		msg = pcb->msg;
		pcb->msg = NULL;

		mtx_unlock(&pcb->pcb_mtx);
		
		if (msg != NULL &&
		    msg->header.cmd == NGM_HCI_NODE_GET_NEIGHBOR_CACHE) {
			/* Return data back to user space */
			p1 = (ng_hci_node_get_neighbor_cache_ep *)(msg->data);
			p2 = (ng_hci_node_neighbor_cache_entry_ep *)(p1 + 1);

			p->num_entries = min(p->num_entries, p1->num_entries);
			if (p->num_entries > 0)
				error = copyout((caddr_t) p2, 
						(caddr_t) p->entries,
						p->num_entries * sizeof(*p2));
		} else
			error = EINVAL;

		NG_FREE_MSG(msg); /* checks for != NULL */
		return (error);
		} /* NOTREACHED */

	case SIOC_HCI_RAW_NODE_GET_CON_LIST: {
		struct ng_btsocket_hci_raw_con_list	*p = 
			(struct ng_btsocket_hci_raw_con_list *) data;
		ng_hci_node_con_list_ep			*p1 = NULL;
		ng_hci_node_con_ep			*p2 = NULL;

		if (p->num_connections == 0 ||
		    p->num_connections > NG_HCI_MAX_CON_NUM ||
		    p->connections == NULL) {
			mtx_unlock(&pcb->pcb_mtx);
			return (EINVAL);
		}

		NG_MKMESSAGE(msg, NGM_HCI_COOKIE, NGM_HCI_NODE_GET_CON_LIST,
			0, M_NOWAIT);
		if (msg == NULL) {
			mtx_unlock(&pcb->pcb_mtx);
			return (ENOMEM);
		}
		ng_btsocket_hci_raw_get_token(&msg->header.token);
		pcb->token = msg->header.token;
		pcb->msg = NULL;

		NG_SEND_MSG_PATH(error, ng_btsocket_hci_raw_node, msg, path, 0);
		if (error != 0) {
			pcb->token = 0;
			mtx_unlock(&pcb->pcb_mtx);
			return (error);
		}

		error = msleep(&pcb->msg, &pcb->pcb_mtx,
				PZERO|PCATCH, "hcictl", 
				ng_btsocket_hci_raw_ioctl_timeout * hz);
		pcb->token = 0;

		if (error != 0) {
			mtx_unlock(&pcb->pcb_mtx);
			return (error);
		}

		msg = pcb->msg;
		pcb->msg = NULL;

		mtx_unlock(&pcb->pcb_mtx);

		if (msg != NULL &&
		    msg->header.cmd == NGM_HCI_NODE_GET_CON_LIST) {
			/* Return data back to user space */
			p1 = (ng_hci_node_con_list_ep *)(msg->data);
			p2 = (ng_hci_node_con_ep *)(p1 + 1);

			p->num_connections = min(p->num_connections,
						p1->num_connections);
			if (p->num_connections > 0)
				error = copyout((caddr_t) p2, 
					(caddr_t) p->connections,
					p->num_connections * sizeof(*p2));
		} else
			error = EINVAL;

		NG_FREE_MSG(msg); /* checks for != NULL */
		return (error);
		} /* NOTREACHED */

	case SIOC_HCI_RAW_NODE_GET_LINK_POLICY_MASK: {
		struct ng_btsocket_hci_raw_node_link_policy_mask	*p = 
			(struct ng_btsocket_hci_raw_node_link_policy_mask *) 
				data;

		error = ng_btsocket_hci_raw_send_sync_ngmsg(pcb, path,
				NGM_HCI_NODE_GET_LINK_POLICY_SETTINGS_MASK,
				&p->policy_mask, sizeof(p->policy_mask));
		} break;

	case SIOC_HCI_RAW_NODE_SET_LINK_POLICY_MASK: {
		struct ng_btsocket_hci_raw_node_link_policy_mask	*p = 
			(struct ng_btsocket_hci_raw_node_link_policy_mask *) 
				data;

		if (pcb->flags & NG_BTSOCKET_HCI_RAW_PRIVILEGED)
			error = ng_btsocket_hci_raw_send_ngmsg(path,
					NGM_HCI_NODE_SET_LINK_POLICY_SETTINGS_MASK,
					&p->policy_mask,
					sizeof(p->policy_mask));
		else
			error = EPERM;
		} break;

	case SIOC_HCI_RAW_NODE_GET_PACKET_MASK: {
		struct ng_btsocket_hci_raw_node_packet_mask	*p = 
			(struct ng_btsocket_hci_raw_node_packet_mask *) data;

		error = ng_btsocket_hci_raw_send_sync_ngmsg(pcb, path,
				NGM_HCI_NODE_GET_PACKET_MASK,
				&p->packet_mask, sizeof(p->packet_mask));
		} break;

	case SIOC_HCI_RAW_NODE_SET_PACKET_MASK: {
		struct ng_btsocket_hci_raw_node_packet_mask	*p = 
			(struct ng_btsocket_hci_raw_node_packet_mask *) data;

		if (pcb->flags & NG_BTSOCKET_HCI_RAW_PRIVILEGED)
			error = ng_btsocket_hci_raw_send_ngmsg(path,
					NGM_HCI_NODE_SET_PACKET_MASK,
					&p->packet_mask,
					sizeof(p->packet_mask));
		else
			error = EPERM;
		} break;

	case SIOC_HCI_RAW_NODE_GET_ROLE_SWITCH: {
		struct ng_btsocket_hci_raw_node_role_switch	*p = 
			(struct ng_btsocket_hci_raw_node_role_switch *) data;

		error = ng_btsocket_hci_raw_send_sync_ngmsg(pcb, path,
				NGM_HCI_NODE_GET_ROLE_SWITCH,
				&p->role_switch, sizeof(p->role_switch));
		} break;

	case SIOC_HCI_RAW_NODE_SET_ROLE_SWITCH: {
		struct ng_btsocket_hci_raw_node_role_switch	*p = 
			(struct ng_btsocket_hci_raw_node_role_switch *) data;

		if (pcb->flags & NG_BTSOCKET_HCI_RAW_PRIVILEGED)
			error = ng_btsocket_hci_raw_send_ngmsg(path,
					NGM_HCI_NODE_SET_ROLE_SWITCH,
					&p->role_switch,
					sizeof(p->role_switch));
		else
			error = EPERM;
		} break;

	case SIOC_HCI_RAW_NODE_LIST_NAMES: {
		struct ng_btsocket_hci_raw_node_list_names	*nl =
			(struct ng_btsocket_hci_raw_node_list_names *) data;
		struct nodeinfo					*ni = nl->names;

		if (nl->num_names == 0) {
			mtx_unlock(&pcb->pcb_mtx);
			return (EINVAL);
		}

		NG_MKMESSAGE(msg, NGM_GENERIC_COOKIE, NGM_LISTNAMES,
			0, M_NOWAIT);
		if (msg == NULL) {
			mtx_unlock(&pcb->pcb_mtx);
			return (ENOMEM);
		}
		ng_btsocket_hci_raw_get_token(&msg->header.token);
		pcb->token = msg->header.token;
		pcb->msg = NULL;

		NG_SEND_MSG_PATH(error, ng_btsocket_hci_raw_node, msg, ".:", 0);
		if (error != 0) {
			pcb->token = 0;
			mtx_unlock(&pcb->pcb_mtx);
			return (error);
		}

		error = msleep(&pcb->msg, &pcb->pcb_mtx,
				PZERO|PCATCH, "hcictl",
				ng_btsocket_hci_raw_ioctl_timeout * hz);
		pcb->token = 0;

		if (error != 0) {
			mtx_unlock(&pcb->pcb_mtx);
			return (error);
		}

		msg = pcb->msg;
		pcb->msg = NULL;

		mtx_unlock(&pcb->pcb_mtx);

		if (msg != NULL && msg->header.cmd == NGM_LISTNAMES) {
			/* Return data back to user space */
			struct namelist	*nl1 = (struct namelist *) msg->data;
			struct nodeinfo	*ni1 = &nl1->nodeinfo[0];

			while (nl->num_names > 0 && nl1->numnames > 0) {
				if (strcmp(ni1->type, NG_HCI_NODE_TYPE) == 0) {
					error = copyout((caddr_t) ni1,
							(caddr_t) ni,
							sizeof(*ni));
					if (error != 0)
						break;

					nl->num_names --;
					ni ++;
				}

				nl1->numnames --;
				ni1 ++;
			}

			nl->num_names = ni - nl->names;
		} else
			error = EINVAL;

		NG_FREE_MSG(msg); /* checks for != NULL */
		return (error);
		} /* NOTREACHED */

	default:
		error = EINVAL;
		break;
	}

	mtx_unlock(&pcb->pcb_mtx);

	return (error);
}