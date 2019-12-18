#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_6__ {int typecookie; int arglen; int /*<<< orphan*/  cmd; } ;
struct ng_mesg {scalar_t__ data; TYPE_1__ header; } ;
struct ng_etfstat {int /*<<< orphan*/  packets_out; int /*<<< orphan*/  packets_in; } ;
struct ng_etffilter {int /*<<< orphan*/  ethertype; int /*<<< orphan*/  matchhook; } ;
struct filter {int /*<<< orphan*/  ethertype; int /*<<< orphan*/ * match_hook; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/ * hook_p ;
typedef  TYPE_3__* etf_p ;
struct TYPE_7__ {int /*<<< orphan*/ * hook; } ;
struct TYPE_8__ {scalar_t__ hashtable; TYPE_2__ downstream_hook; int /*<<< orphan*/  flags; int /*<<< orphan*/  packets_out; int /*<<< orphan*/  packets_in; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (scalar_t__,struct filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH_ETF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_ETF_COOKIE 131 
#define  NGM_ETF_GET_STATUS 130 
#define  NGM_ETF_SET_FILTER 129 
#define  NGM_ETF_SET_FLAG 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int) ; 
 TYPE_3__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct filter* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ng_etf_findentry (TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ng_findhook (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_etf_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	const etf_p etfp = NG_NODE_PRIVATE(node);
	struct ng_mesg *resp = NULL;
	int error = 0;
	struct ng_mesg *msg;

	NGI_GET_MSG(item, msg);
	/* Deal with message according to cookie and command */
	switch (msg->header.typecookie) {
	case NGM_ETF_COOKIE: 
		switch (msg->header.cmd) {
		case NGM_ETF_GET_STATUS:
		    {
			struct ng_etfstat *stats;

			NG_MKRESPONSE(resp, msg, sizeof(*stats), M_NOWAIT);
			if (!resp) {
				error = ENOMEM;
				break;
			}
			stats = (struct ng_etfstat *) resp->data;
			stats->packets_in = etfp->packets_in;
			stats->packets_out = etfp->packets_out;
			break;
		    }
		case NGM_ETF_SET_FLAG:
			if (msg->header.arglen != sizeof(u_int32_t)) {
				error = EINVAL;
				break;
			}
			etfp->flags = *((u_int32_t *) msg->data);
			break;
		case NGM_ETF_SET_FILTER:
			{
				struct ng_etffilter *f;
				struct filter *fil;
				hook_p  hook;

				/* Check message long enough for this command */
				if (msg->header.arglen != sizeof(*f)) {
					error = EINVAL;
					break;
				}

				/* Make sure hook referenced exists */
				f = (struct ng_etffilter *)msg->data;
				hook = ng_findhook(node, f->matchhook);
				if (hook == NULL) {
					error = ENOENT;
					break;
				}

				/* and is not the downstream hook */
				if (hook == etfp->downstream_hook.hook) {
					error = EINVAL;
					break;
				}

				/* Check we don't already trap this ethertype */
				if (ng_etf_findentry(etfp,
						htons(f->ethertype))) {
					error = EEXIST;
					break;
				}

				/*
				 * Ok, make the filter and put it in the 
				 * hashtable ready for matching.
				 */
				fil = malloc(sizeof(*fil),
					M_NETGRAPH_ETF, M_NOWAIT | M_ZERO);
				if (fil == NULL) {
					error = ENOMEM;
					break;
				}

				fil->match_hook = hook;
				fil->ethertype = htons(f->ethertype);
				LIST_INSERT_HEAD( etfp->hashtable
					+ HASH(fil->ethertype),
						fil, next);
			}
			break;
		default:
			error = EINVAL;		/* unknown command */
			break;
		}
		break;
	default:
		error = EINVAL;			/* unknown cookie type */
		break;
	}

	/* Take care of synchronous response, if any */
	NG_RESPOND_MSG(error, node, item, resp);
	/* Free the message and return */
	NG_FREE_MSG(msg);
	return(error);
}