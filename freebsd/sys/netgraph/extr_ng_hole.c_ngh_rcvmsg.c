#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int typecookie; int const cmd; int /*<<< orphan*/  arglen; } ;
struct ng_mesg {TYPE_1__ header; scalar_t__ data; } ;
struct ng_hole_hookstat {int dummy; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/ * hook_p ;
typedef  TYPE_2__* hinfo_p ;
struct TYPE_4__ {struct ng_hole_hookstat stats; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_HOLE_CLR_STATS 131 
#define  NGM_HOLE_COOKIE 130 
#define  NGM_HOLE_GETCLR_STATS 129 
#define  NGM_HOLE_GET_STATS 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_HOOKSIZ ; 
 int /*<<< orphan*/  NG_HOOK_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  bcopy (struct ng_hole_hookstat*,scalar_t__,int) ; 
 int /*<<< orphan*/  bzero (struct ng_hole_hookstat*,int) ; 
 int /*<<< orphan*/ * ng_findhook (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ngh_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	struct ng_mesg *msg;
	struct ng_mesg *resp = NULL;
	int error = 0;
	struct ng_hole_hookstat *stats;
	hook_p hook;

	NGI_GET_MSG(item, msg);
	switch (msg->header.typecookie) {
	case NGM_HOLE_COOKIE:
		switch (msg->header.cmd) {
		case NGM_HOLE_GET_STATS:
		case NGM_HOLE_CLR_STATS:
		case NGM_HOLE_GETCLR_STATS:
			/* Sanity check. */
			if (msg->header.arglen != NG_HOOKSIZ) {
				error = EINVAL;
				break;
			}
			/* Find hook. */
			hook = ng_findhook(node, (char *)msg->data);
			if (hook == NULL) {
				error = ENOENT;
				break;
			}
			stats = &((hinfo_p)NG_HOOK_PRIVATE(hook))->stats;
			/* Build response (if desired). */
			if (msg->header.cmd != NGM_HOLE_CLR_STATS) {
				NG_MKRESPONSE(resp, msg, sizeof(*stats),
				    M_NOWAIT);
				if (resp == NULL) {
					error = ENOMEM;
					break;
				}
				bcopy(stats, resp->data, sizeof(*stats));
			}
			/* Clear stats (if desired). */
			if (msg->header.cmd != NGM_HOLE_GET_STATS)
				bzero(stats, sizeof(*stats));
			break;
		default:		/* Unknown command. */
			error = EINVAL;
			break;
		}
		break;
	default:			/* Unknown type cookie. */
		error = EINVAL;
		break;
	}
	NG_RESPOND_MSG(error, node, item, resp);
	NG_FREE_MSG(msg);
	return (error);
}