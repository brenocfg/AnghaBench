#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ng_pred1_stats {int dummy; } ;
struct ng_pred1_config {int dummy; } ;
struct TYPE_4__ {scalar_t__ typecookie; int cmd; int arglen; } ;
struct ng_mesg {TYPE_1__ header; scalar_t__ data; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_5__ {int /*<<< orphan*/  stats; int /*<<< orphan*/  ctrlnode; struct ng_pred1_config cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROUT (int) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  NGI_RETADDR (int /*<<< orphan*/ ) ; 
#define  NGM_PRED1_CLR_STATS 132 
#define  NGM_PRED1_CONFIG 131 
 scalar_t__ NGM_PRED1_COOKIE ; 
#define  NGM_PRED1_GETCLR_STATS 130 
#define  NGM_PRED1_GET_STATS 129 
#define  NGM_PRED1_RESETREQ 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  Pred1Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ng_pred1_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_mesg *resp = NULL;
	int error = 0;
	struct ng_mesg *msg;

	NGI_GET_MSG(item, msg);

	if (msg->header.typecookie != NGM_PRED1_COOKIE)
		ERROUT(EINVAL);

	switch (msg->header.cmd) {
	case NGM_PRED1_CONFIG:
	    {
		struct ng_pred1_config *const cfg =
		    (struct ng_pred1_config *)msg->data;

		/* Check configuration. */
		if (msg->header.arglen != sizeof(*cfg))
			ERROUT(EINVAL);

		/* Configuration is OK, reset to it. */
		priv->cfg = *cfg;

		/* Save return address so we can send reset-req's. */
		priv->ctrlnode = NGI_RETADDR(item);

		/* Clear our state. */
		Pred1Init(node);

		break;
	    }
	case NGM_PRED1_RESETREQ:
		Pred1Init(node);
		break;

	case NGM_PRED1_GET_STATS:
	case NGM_PRED1_CLR_STATS:
	case NGM_PRED1_GETCLR_STATS:
	    {
		/* Create response. */
		if (msg->header.cmd != NGM_PRED1_CLR_STATS) {
			NG_MKRESPONSE(resp, msg,
			    sizeof(struct ng_pred1_stats), M_NOWAIT);
			if (resp == NULL)
				ERROUT(ENOMEM);
			bcopy(&priv->stats, resp->data,
			    sizeof(struct ng_pred1_stats));
		}

		if (msg->header.cmd != NGM_PRED1_GET_STATS)
			bzero(&priv->stats, sizeof(struct ng_pred1_stats));
		break;
	    }

	default:
		error = EINVAL;
		break;
	}
done:
	NG_RESPOND_MSG(error, node, item, resp);
	NG_FREE_MSG(msg);
	return (error);
}