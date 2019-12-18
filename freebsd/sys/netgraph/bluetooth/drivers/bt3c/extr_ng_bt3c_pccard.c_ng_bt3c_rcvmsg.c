#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int typecookie; int arglen; int /*<<< orphan*/  cmd; } ;
struct ng_mesg {TYPE_1__ header; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int ng_bt3c_node_state_ep ;
typedef  int /*<<< orphan*/  ng_bt3c_node_stat_ep ;
struct TYPE_7__ {int queue; int qlen; } ;
typedef  TYPE_2__ ng_bt3c_node_qlen_ep ;
typedef  int ng_bt3c_node_debug_ep ;
typedef  int /*<<< orphan*/  ng_bt3c_firmware_block_ep ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
typedef  TYPE_3__* bt3c_softc_p ;
struct TYPE_9__ {int ifq_maxlen; } ;
struct TYPE_8__ {int flags; int debug; int state; int /*<<< orphan*/  stat; TYPE_5__ outq; TYPE_5__ inq; int /*<<< orphan*/ * hook; } ;

/* Variables and functions */
 int EHOSTDOWN ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_BT3C_COOKIE 140 
#define  NGM_BT3C_NODE_DOWNLOAD_FIRMWARE 139 
#define  NGM_BT3C_NODE_GET_DEBUG 138 
#define  NGM_BT3C_NODE_GET_QLEN 137 
#define  NGM_BT3C_NODE_GET_STAT 136 
#define  NGM_BT3C_NODE_GET_STATE 135 
#define  NGM_BT3C_NODE_IN_QUEUE 134 
#define  NGM_BT3C_NODE_OUT_QUEUE 133 
#define  NGM_BT3C_NODE_RESET_STAT 132 
#define  NGM_BT3C_NODE_SET_DEBUG 131 
#define  NGM_BT3C_NODE_SET_QLEN 130 
#define  NGM_GENERIC_COOKIE 129 
#define  NGM_TEXT_STATUS 128 
 char* NG_BT3C_HOOK ; 
 int /*<<< orphan*/  NG_BT3C_STAT_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int NG_TEXTRESPONSE ; 
 int _IF_QLEN (TYPE_5__*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  bt3c_download_firmware (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  snprintf (scalar_t__,int,char*,char*,int,int,int,int,int,int,int) ; 

__attribute__((used)) static int
ng_bt3c_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	bt3c_softc_p	 sc = (bt3c_softc_p) NG_NODE_PRIVATE(node);
	struct ng_mesg	*msg = NULL, *rsp = NULL;
	int		 error = 0;

	if (sc == NULL) {
		NG_FREE_ITEM(item);
		return (EHOSTDOWN);
	}

	NGI_GET_MSG(item, msg);

	switch (msg->header.typecookie) {
	case NGM_GENERIC_COOKIE:
		switch (msg->header.cmd) {
		case NGM_TEXT_STATUS:
			NG_MKRESPONSE(rsp, msg, NG_TEXTRESPONSE, M_NOWAIT);
			if (rsp == NULL)
				error = ENOMEM;
			else
				snprintf(rsp->data, NG_TEXTRESPONSE,
					"Hook: %s\n" \
					"Flags: %#x\n" \
					"Debug: %d\n"  \
					"State: %d\n"  \
					"IncmQ: [len:%d,max:%d]\n" \
					"OutgQ: [len:%d,max:%d]\n",
					(sc->hook != NULL)? NG_BT3C_HOOK : "",
					sc->flags,
					sc->debug,
					sc->state,
					_IF_QLEN(&sc->inq), /* XXX */
					sc->inq.ifq_maxlen, /* XXX */
					_IF_QLEN(&sc->outq), /* XXX */
					sc->outq.ifq_maxlen /* XXX */
					);
			break;

		default:
			error = EINVAL;
			break;
		}
		break;

	case NGM_BT3C_COOKIE:
		switch (msg->header.cmd) {
		case NGM_BT3C_NODE_GET_STATE:
			NG_MKRESPONSE(rsp, msg, sizeof(ng_bt3c_node_state_ep),
				M_NOWAIT);
			if (rsp == NULL)
				error = ENOMEM;
			else
				*((ng_bt3c_node_state_ep *)(rsp->data)) = 
					sc->state;
			break;

		case NGM_BT3C_NODE_SET_DEBUG:
			if (msg->header.arglen != sizeof(ng_bt3c_node_debug_ep))
				error = EMSGSIZE;
			else
				sc->debug =
					*((ng_bt3c_node_debug_ep *)(msg->data));
			break;

		case NGM_BT3C_NODE_GET_DEBUG:
			NG_MKRESPONSE(rsp, msg, sizeof(ng_bt3c_node_debug_ep),
				M_NOWAIT);
			if (rsp == NULL)
				error = ENOMEM;
			else
				*((ng_bt3c_node_debug_ep *)(rsp->data)) = 
					sc->debug;
			break;

		case NGM_BT3C_NODE_GET_QLEN:
			NG_MKRESPONSE(rsp, msg, sizeof(ng_bt3c_node_qlen_ep),
				M_NOWAIT);
			if (rsp == NULL) {
				error = ENOMEM;
				break;
			}

			switch (((ng_bt3c_node_qlen_ep *)(msg->data))->queue) {
			case NGM_BT3C_NODE_IN_QUEUE:
				((ng_bt3c_node_qlen_ep *)(rsp->data))->queue =
					NGM_BT3C_NODE_IN_QUEUE;
				((ng_bt3c_node_qlen_ep *)(rsp->data))->qlen =
					sc->inq.ifq_maxlen;
				break;

			case NGM_BT3C_NODE_OUT_QUEUE:
				((ng_bt3c_node_qlen_ep *)(rsp->data))->queue =
					NGM_BT3C_NODE_OUT_QUEUE;
				((ng_bt3c_node_qlen_ep *)(rsp->data))->qlen =
					sc->outq.ifq_maxlen;
				break;

			default:
				NG_FREE_MSG(rsp);
				error = EINVAL;
				break;
			}
			break;

		case NGM_BT3C_NODE_SET_QLEN:
			if (msg->header.arglen != sizeof(ng_bt3c_node_qlen_ep)){
				error = EMSGSIZE;
				break;
			}

			if (((ng_bt3c_node_qlen_ep *)(msg->data))->qlen <= 0) {
				error = EINVAL;
				break;
			}

			switch (((ng_bt3c_node_qlen_ep *)(msg->data))->queue) {
			case NGM_BT3C_NODE_IN_QUEUE:
				sc->inq.ifq_maxlen = ((ng_bt3c_node_qlen_ep *)
					(msg->data))->qlen; /* XXX */
				break;

			case NGM_BT3C_NODE_OUT_QUEUE:
				sc->outq.ifq_maxlen = ((ng_bt3c_node_qlen_ep *)
					(msg->data))->qlen; /* XXX */
				break;

			default:
				error = EINVAL;
				break;
			}
			break;

		case NGM_BT3C_NODE_GET_STAT:
			NG_MKRESPONSE(rsp, msg, sizeof(ng_bt3c_node_stat_ep),
				M_NOWAIT);
			if (rsp == NULL)
				error = ENOMEM;
			else
				bcopy(&sc->stat, rsp->data,
					sizeof(ng_bt3c_node_stat_ep));
			break;

		case NGM_BT3C_NODE_RESET_STAT:
			NG_BT3C_STAT_RESET(sc->stat);
			break;

		case NGM_BT3C_NODE_DOWNLOAD_FIRMWARE:
			if (msg->header.arglen < 
					sizeof(ng_bt3c_firmware_block_ep))
				error = EMSGSIZE;
			else	
				bt3c_download_firmware(sc, msg->data,
							msg->header.arglen);
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

	NG_RESPOND_MSG(error, node, item, rsp);
	NG_FREE_MSG(msg);

	return (error);
}