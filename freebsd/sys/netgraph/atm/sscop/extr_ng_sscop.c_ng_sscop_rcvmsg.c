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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sscop_param {int dummy; } ;
struct priv {int enabled; int flow; int /*<<< orphan*/  sscop; int /*<<< orphan*/  stats; int /*<<< orphan*/ * lower; int /*<<< orphan*/ * upper; } ;
struct ng_sscop_setparam_resp {int /*<<< orphan*/  mask; int /*<<< orphan*/  error; } ;
struct ng_sscop_setparam {int /*<<< orphan*/  param; int /*<<< orphan*/  mask; } ;
struct TYPE_2__ {int typecookie; int arglen; int /*<<< orphan*/  cmd; } ;
struct ng_mesg {scalar_t__ data; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EISCONN ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_FLOW_COOKIE 138 
#define  NGM_GENERIC_COOKIE 137 
#define  NGM_SSCOP_COOKIE 136 
#define  NGM_SSCOP_DISABLE 135 
#define  NGM_SSCOP_ENABLE 134 
#define  NGM_SSCOP_GETDEBUG 133 
#define  NGM_SSCOP_GETPARAM 132 
#define  NGM_SSCOP_GETSTATE 131 
#define  NGM_SSCOP_SETDEBUG 130 
#define  NGM_SSCOP_SETPARAM 129 
#define  NGM_TEXT_STATUS 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 struct priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int NG_TEXTRESPONSE ; 
 int flow_lower (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int flow_upper (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sscop_getdebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscop_getparam (int /*<<< orphan*/ ,struct sscop_param*) ; 
 int /*<<< orphan*/  sscop_getstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscop_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscop_setdebug (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscop_setparam (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_status (int /*<<< orphan*/ ,struct priv*,char*,int) ; 

__attribute__((used)) static int
ng_sscop_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	struct priv *priv = NG_NODE_PRIVATE(node);
	struct ng_mesg *resp = NULL;
	struct ng_mesg *msg;
	int error = 0;

	NGI_GET_MSG(item, msg);

	switch (msg->header.typecookie) {

	  case NGM_GENERIC_COOKIE:
		switch (msg->header.cmd) {

		  case NGM_TEXT_STATUS:
			NG_MKRESPONSE(resp, msg, NG_TEXTRESPONSE, M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				break;
			}

			resp->header.arglen = text_status(node, priv,
			    (char *)resp->data, resp->header.arglen) + 1;
			break;

		  default:
			error = EINVAL;
			break;
		}
		break;

	  case NGM_FLOW_COOKIE:
		if (priv->enabled && lasthook != NULL) {
			if (lasthook == priv->upper)
				error = flow_upper(node, msg);
			else if (lasthook == priv->lower)
				error = flow_lower(node, msg);
		}
		break;

	  case NGM_SSCOP_COOKIE:
		switch (msg->header.cmd) {

		  case NGM_SSCOP_GETPARAM:
		    {
			struct sscop_param *p;

			NG_MKRESPONSE(resp, msg, sizeof(*p), M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				break;
			}
			p = (struct sscop_param *)resp->data;
			sscop_getparam(priv->sscop, p);
			break;
		    }

		  case NGM_SSCOP_SETPARAM:
		    {
			struct ng_sscop_setparam *arg;
			struct ng_sscop_setparam_resp *p;

			if (msg->header.arglen != sizeof(*arg)) {
				error = EINVAL;
				break;
			}
			if (priv->enabled) {
				error = EISCONN;
				break;
			}
			arg = (struct ng_sscop_setparam *)msg->data;
			NG_MKRESPONSE(resp, msg, sizeof(*p), M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				break;
			}
			p = (struct ng_sscop_setparam_resp *)resp->data;
			p->mask = arg->mask;
			p->error = sscop_setparam(priv->sscop,
			    &arg->param, &p->mask);
			break;
		    }

		  case NGM_SSCOP_ENABLE:
			if (msg->header.arglen != 0) {
				error = EINVAL;
				break;
			}
			if (priv->enabled) {
				error = EBUSY;
				break;
			}
			priv->enabled = 1;
			priv->flow = 1;
			memset(&priv->stats, 0, sizeof(priv->stats));
			break;

		  case NGM_SSCOP_DISABLE:
			if (msg->header.arglen != 0) {
				error = EINVAL;
				break;
			}
			if (!priv->enabled) {
				error = ENOTCONN;
				break;
			}
			priv->enabled = 0;
			sscop_reset(priv->sscop);
			break;

		  case NGM_SSCOP_GETDEBUG:
			if (msg->header.arglen != 0) {
				error = EINVAL;
				break;
			}
			NG_MKRESPONSE(resp, msg, sizeof(u_int32_t), M_NOWAIT);
			if(resp == NULL) {
				error = ENOMEM;
				break;
			}
			*(u_int32_t *)resp->data = sscop_getdebug(priv->sscop);
			break;

		  case NGM_SSCOP_SETDEBUG:
			if (msg->header.arglen != sizeof(u_int32_t)) {
				error = EINVAL;
				break;
			}
			sscop_setdebug(priv->sscop, *(u_int32_t *)msg->data);
			break;

		  case NGM_SSCOP_GETSTATE:
			if (msg->header.arglen != 0) {
				error = EINVAL;
				break;
			}
			NG_MKRESPONSE(resp, msg, sizeof(u_int32_t), M_NOWAIT);
			if(resp == NULL) {
				error = ENOMEM;
				break;
			}
			*(u_int32_t *)resp->data =
			    priv->enabled ? (sscop_getstate(priv->sscop) + 1)
			                  : 0;
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