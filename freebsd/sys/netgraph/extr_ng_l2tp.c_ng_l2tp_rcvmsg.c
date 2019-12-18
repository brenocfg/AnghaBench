#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_9__ {int typecookie; int const cmd; int arglen; } ;
struct ng_mesg {TYPE_1__ header; int /*<<< orphan*/ * data; } ;
struct ng_l2tp_sess_config {int /*<<< orphan*/  session_id; } ;
struct ng_l2tp_seq_config {void* xack; void* rack; void* nr; void* ns; } ;
struct ng_l2tp_config {int enabled; int match_id; int /*<<< orphan*/  peer_id; int /*<<< orphan*/  tunnel_id; } ;
typedef  int /*<<< orphan*/  session_id ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  TYPE_3__* hookpriv_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_11__ {int /*<<< orphan*/  stats; struct ng_l2tp_sess_config conf; } ;
struct TYPE_10__ {int /*<<< orphan*/  stats; struct ng_l2tp_config conf; int /*<<< orphan*/  ftarget; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  NGI_RETADDR (int /*<<< orphan*/ ) ; 
#define  NGM_L2TP_CLR_SESSION_STATS 139 
#define  NGM_L2TP_CLR_STATS 138 
#define  NGM_L2TP_COOKIE 137 
#define  NGM_L2TP_GETCLR_SESSION_STATS 136 
#define  NGM_L2TP_GETCLR_STATS 135 
#define  NGM_L2TP_GET_CONFIG 134 
#define  NGM_L2TP_GET_SESSION_STATS 133 
#define  NGM_L2TP_GET_SESS_CONFIG 132 
#define  NGM_L2TP_GET_STATS 131 
#define  NGM_L2TP_SET_CONFIG 130 
#define  NGM_L2TP_SET_SEQ 129 
#define  NGM_L2TP_SET_SESS_CONFIG 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 void* htons (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ng_l2tp_find_session (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int ng_l2tp_seq_adjust (TYPE_2__* const,struct ng_l2tp_config* const) ; 
 int ng_l2tp_seq_set (TYPE_2__* const,struct ng_l2tp_seq_config* const) ; 

__attribute__((used)) static int
ng_l2tp_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_mesg *resp = NULL;
	struct ng_mesg *msg;
	int error = 0;

	NGI_GET_MSG(item, msg);
	switch (msg->header.typecookie) {
	case NGM_L2TP_COOKIE:
		switch (msg->header.cmd) {
		case NGM_L2TP_SET_CONFIG:
		    {
			struct ng_l2tp_config *const conf =
				(struct ng_l2tp_config *)msg->data;

			/* Check for invalid or illegal config */
			if (msg->header.arglen != sizeof(*conf)) {
				error = EINVAL;
				break;
			}
			conf->enabled = !!conf->enabled;
			conf->match_id = !!conf->match_id;
			if (priv->conf.enabled
			    && ((priv->conf.tunnel_id != 0
			       && conf->tunnel_id != priv->conf.tunnel_id)
			      || ((priv->conf.peer_id != 0
			       && conf->peer_id != priv->conf.peer_id)))) {
				error = EBUSY;
				break;
			}

			/* Save calling node as failure target */
			priv->ftarget = NGI_RETADDR(item);

			/* Adjust sequence number state */
			if ((error = ng_l2tp_seq_adjust(priv, conf)) != 0)
				break;

			/* Update node's config */
			priv->conf = *conf;
			break;
		    }
		case NGM_L2TP_GET_CONFIG:
		    {
			struct ng_l2tp_config *conf;

			NG_MKRESPONSE(resp, msg, sizeof(*conf), M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				break;
			}
			conf = (struct ng_l2tp_config *)resp->data;
			*conf = priv->conf;
			break;
		    }
		case NGM_L2TP_SET_SESS_CONFIG:
		    {
			struct ng_l2tp_sess_config *const conf =
			    (struct ng_l2tp_sess_config *)msg->data;
			hookpriv_p hpriv;

			/* Check for invalid or illegal config. */
			if (msg->header.arglen != sizeof(*conf)) {
				error = EINVAL;
				break;
			}

			/* Find matching hook */
			hpriv = ng_l2tp_find_session(priv, conf->session_id);
			if (hpriv == NULL) {
				error = ENOENT;
				break;
			}

			/* Update hook's config */
			hpriv->conf = *conf;
			break;
		    }
		case NGM_L2TP_GET_SESS_CONFIG:
		    {
			struct ng_l2tp_sess_config *conf;
			u_int16_t session_id;
			hookpriv_p hpriv;

			/* Get session ID */
			if (msg->header.arglen != sizeof(session_id)) {
				error = EINVAL;
				break;
			}
			memcpy(&session_id, msg->data, 2);

			/* Find matching hook */
			hpriv = ng_l2tp_find_session(priv, session_id);
			if (hpriv == NULL) {
				error = ENOENT;
				break;
			}

			/* Send response */
			NG_MKRESPONSE(resp, msg, sizeof(hpriv->conf), M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				break;
			}
			conf = (struct ng_l2tp_sess_config *)resp->data;
			*conf = hpriv->conf;
			break;
		    }
		case NGM_L2TP_GET_STATS:
		case NGM_L2TP_CLR_STATS:
		case NGM_L2TP_GETCLR_STATS:
		    {
			if (msg->header.cmd != NGM_L2TP_CLR_STATS) {
				NG_MKRESPONSE(resp, msg,
				    sizeof(priv->stats), M_NOWAIT);
				if (resp == NULL) {
					error = ENOMEM;
					break;
				}
				memcpy(resp->data,
				    &priv->stats, sizeof(priv->stats));
			}
			if (msg->header.cmd != NGM_L2TP_GET_STATS)
				memset(&priv->stats, 0, sizeof(priv->stats));
			break;
		    }
		case NGM_L2TP_GET_SESSION_STATS:
		case NGM_L2TP_CLR_SESSION_STATS:
		case NGM_L2TP_GETCLR_SESSION_STATS:
		    {
			uint16_t session_id;
			hookpriv_p hpriv;

			/* Get session ID. */
			if (msg->header.arglen != sizeof(session_id)) {
				error = EINVAL;
				break;
			}
			bcopy(msg->data, &session_id, sizeof(uint16_t));

			/* Find matching hook. */
			hpriv = ng_l2tp_find_session(priv, session_id);
			if (hpriv == NULL) {
				error = ENOENT;
				break;
			}

			if (msg->header.cmd != NGM_L2TP_CLR_SESSION_STATS) {
				NG_MKRESPONSE(resp, msg,
				    sizeof(hpriv->stats), M_NOWAIT);
				if (resp == NULL) {
					error = ENOMEM;
					break;
				}
				bcopy(&hpriv->stats, resp->data,
					sizeof(hpriv->stats));
			}
			if (msg->header.cmd != NGM_L2TP_GET_SESSION_STATS)
				bzero(&hpriv->stats, sizeof(hpriv->stats));
			break;
		    }
		case NGM_L2TP_SET_SEQ:
		    {
			struct ng_l2tp_seq_config *const conf =
				(struct ng_l2tp_seq_config *)msg->data;

			/* Check for invalid or illegal seq config. */
			if (msg->header.arglen != sizeof(*conf)) {
				error = EINVAL;
				break;
			}
			conf->ns = htons(conf->ns);
			conf->nr = htons(conf->nr);
			conf->rack = htons(conf->rack);
			conf->xack = htons(conf->xack);

			/* Set sequence numbers. */
			error = ng_l2tp_seq_set(priv, conf);
			break;
		    }
		default:
			error = EINVAL;
			break;
		}
		break;
	default:
		error = EINVAL;
		break;
	}

	/* Done */
	NG_RESPOND_MSG(error, node, item, resp);
	NG_FREE_MSG(msg);
	return (error);
}