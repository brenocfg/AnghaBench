#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct ng_pptpgre_conf {size_t cid; } ;
struct TYPE_10__ {int typecookie; int const cmd; int arglen; } ;
struct ng_mesg {TYPE_1__ header; scalar_t__ data; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  TYPE_3__* hpriv_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_12__ {struct ng_pptpgre_conf conf; } ;
struct TYPE_11__ {struct ng_pptpgre_conf stats; TYPE_3__ uppersess; int /*<<< orphan*/ * sesshash; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROUT (int) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_PPTPGRE_CLR_STATS 133 
#define  NGM_PPTPGRE_COOKIE 132 
#define  NGM_PPTPGRE_GETCLR_STATS 131 
#define  NGM_PPTPGRE_GET_CONFIG 130 
#define  NGM_PPTPGRE_GET_STATS 129 
#define  NGM_PPTPGRE_SET_CONFIG 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 size_t SESSHASH (size_t) ; 
 int /*<<< orphan*/  bcopy (struct ng_pptpgre_conf*,scalar_t__,int) ; 
 int /*<<< orphan*/  bzero (struct ng_pptpgre_conf*,int) ; 
 TYPE_3__* ng_pptpgre_find_session (TYPE_2__* const,size_t) ; 
 int /*<<< orphan*/  ng_pptpgre_reset (TYPE_3__*) ; 
 int /*<<< orphan*/  sessions ; 

__attribute__((used)) static int
ng_pptpgre_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_mesg *resp = NULL;
	int error = 0;
	struct ng_mesg *msg;

	NGI_GET_MSG(item, msg);
	switch (msg->header.typecookie) {
	case NGM_PPTPGRE_COOKIE:
		switch (msg->header.cmd) {
		case NGM_PPTPGRE_SET_CONFIG:
		    {
			struct ng_pptpgre_conf *const newConf =
				(struct ng_pptpgre_conf *) msg->data;
			hpriv_p hpriv;
			uint16_t hash;

			/* Check for invalid or illegal config */
			if (msg->header.arglen != sizeof(*newConf))
				ERROUT(EINVAL);
			/* Try to find session by cid. */
			hpriv = ng_pptpgre_find_session(priv, newConf->cid);
			/* If not present - use upper. */
			if (hpriv == NULL) {
				hpriv = &priv->uppersess;
				LIST_REMOVE(hpriv, sessions);
				hash = SESSHASH(newConf->cid);
				LIST_INSERT_HEAD(&priv->sesshash[hash], hpriv,
				    sessions);
			}
			ng_pptpgre_reset(hpriv);	/* reset on configure */
			hpriv->conf = *newConf;
			break;
		    }
		case NGM_PPTPGRE_GET_CONFIG:
		    {
			hpriv_p hpriv;

			if (msg->header.arglen == 2) {
				/* Try to find session by cid. */
	    			hpriv = ng_pptpgre_find_session(priv,
				    *((uint16_t *)msg->data));
				if (hpriv == NULL)
					ERROUT(EINVAL);
			} else if (msg->header.arglen == 0) {
				/* Use upper. */
				hpriv = &priv->uppersess;
			} else
				ERROUT(EINVAL);
			NG_MKRESPONSE(resp, msg, sizeof(hpriv->conf), M_NOWAIT);
			if (resp == NULL)
				ERROUT(ENOMEM);
			bcopy(&hpriv->conf, resp->data, sizeof(hpriv->conf));
			break;
		    }
		case NGM_PPTPGRE_GET_STATS:
		case NGM_PPTPGRE_CLR_STATS:
		case NGM_PPTPGRE_GETCLR_STATS:
		    {
			if (msg->header.cmd != NGM_PPTPGRE_CLR_STATS) {
				NG_MKRESPONSE(resp, msg,
				    sizeof(priv->stats), M_NOWAIT);
				if (resp == NULL)
					ERROUT(ENOMEM);
				bcopy(&priv->stats,
				    resp->data, sizeof(priv->stats));
			}
			if (msg->header.cmd != NGM_PPTPGRE_GET_STATS)
				bzero(&priv->stats, sizeof(priv->stats));
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
done:
	NG_RESPOND_MSG(error, node, item, resp);
	NG_FREE_MSG(msg);
	return (error);
}