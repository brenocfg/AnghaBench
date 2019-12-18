#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct ng_tee_stats {int /*<<< orphan*/  left2right; int /*<<< orphan*/  right2left; int /*<<< orphan*/  left; int /*<<< orphan*/  right; } ;
struct TYPE_11__ {int typecookie; int const cmd; } ;
struct ng_mesg {TYPE_1__ header; scalar_t__ data; } ;
typedef  TYPE_7__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
typedef  TYPE_8__* hi_p ;
struct TYPE_18__ {TYPE_6__* dest; } ;
struct TYPE_15__ {int /*<<< orphan*/  hook; int /*<<< orphan*/  stats; } ;
struct TYPE_14__ {int /*<<< orphan*/  hook; int /*<<< orphan*/  stats; } ;
struct TYPE_13__ {int /*<<< orphan*/  stats; } ;
struct TYPE_12__ {int /*<<< orphan*/  stats; } ;
struct TYPE_17__ {TYPE_5__ right; TYPE_4__ left; TYPE_3__ left2right; TYPE_2__ right2left; } ;
struct TYPE_16__ {int /*<<< orphan*/  hook; } ;
typedef  struct ng_mesg* NGI_MSG ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_FLOW_COOKIE 132 
#define  NGM_TEE_CLR_STATS 131 
#define  NGM_TEE_COOKIE 130 
#define  NGM_TEE_GETCLR_STATS 129 
#define  NGM_TEE_GET_STATS 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_FWD_ITEM_HOOK (int,struct ng_mesg*,int /*<<< orphan*/ ) ; 
 TYPE_8__* NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 TYPE_7__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ng_tee_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	const sc_p sc = NG_NODE_PRIVATE(node);
	struct ng_mesg *resp = NULL;
	int error = 0;
	struct ng_mesg *msg;

	NGI_GET_MSG(item, msg);
	switch (msg->header.typecookie) {
	case NGM_TEE_COOKIE:
		switch (msg->header.cmd) {
		case NGM_TEE_GET_STATS:
		case NGM_TEE_CLR_STATS:
		case NGM_TEE_GETCLR_STATS:
                    {
			struct ng_tee_stats *stats;

                        if (msg->header.cmd != NGM_TEE_CLR_STATS) {
                                NG_MKRESPONSE(resp, msg,
                                    sizeof(*stats), M_NOWAIT);
				if (resp == NULL) {
					error = ENOMEM;
					goto done;
				}
				stats = (struct ng_tee_stats *)resp->data;
				bcopy(&sc->right.stats, &stats->right,
				    sizeof(stats->right));
				bcopy(&sc->left.stats, &stats->left,
				    sizeof(stats->left));
				bcopy(&sc->right2left.stats, &stats->right2left,
				    sizeof(stats->right2left));
				bcopy(&sc->left2right.stats, &stats->left2right,
				    sizeof(stats->left2right));
                        }
                        if (msg->header.cmd != NGM_TEE_GET_STATS) {
				bzero(&sc->right.stats,
				    sizeof(sc->right.stats));
				bzero(&sc->left.stats,
				    sizeof(sc->left.stats));
				bzero(&sc->right2left.stats,
				    sizeof(sc->right2left.stats));
				bzero(&sc->left2right.stats,
				    sizeof(sc->left2right.stats));
			}
                        break;
		    }
		default:
			error = EINVAL;
			break;
		}
		break;
	case NGM_FLOW_COOKIE:
		if (lasthook == sc->left.hook || lasthook == sc->right.hook)  {
			hi_p const hinfo = NG_HOOK_PRIVATE(lasthook);
			if (hinfo && hinfo->dest) {
				NGI_MSG(item) = msg;
				NG_FWD_ITEM_HOOK(error, item, hinfo->dest->hook);
				return (error);
			}
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