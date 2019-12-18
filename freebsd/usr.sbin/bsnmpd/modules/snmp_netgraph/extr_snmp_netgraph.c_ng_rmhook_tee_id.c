#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct ng_mesg {scalar_t__ data; } ;
struct TYPE_4__ {size_t hooks; } ;
struct hooklist {TYPE_3__* link; TYPE_1__ nodeinfo; } ;
typedef  scalar_t__ ng_ID_t ;
struct TYPE_5__ {scalar_t__ id; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_2__ nodeinfo; int /*<<< orphan*/  peerhook; int /*<<< orphan*/  ourhook; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_LISTHOOKS ; 
 int /*<<< orphan*/  free (struct ng_mesg*) ; 
 struct ng_mesg* ng_dialog_id (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_rmhook_id (scalar_t__,char const*) ; 
 int /*<<< orphan*/  ng_shutdown_id (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
ng_rmhook_tee_id(ng_ID_t node, const char *hook)
{
	struct ng_mesg *resp;
	struct hooklist *hooklist;
	u_int i;
	int first = 1;
	ng_ID_t next_node;
	const char *next_hook;

  again:
	/* if we have just shutdown a tee node, which had no other hooks
	 * connected, the node id may already be wrong here. */
	if ((resp = ng_dialog_id(node, NGM_GENERIC_COOKIE, NGM_LISTHOOKS,
	    NULL, 0)) == NULL)
		return (0);

	hooklist = (struct hooklist *)(void *)resp->data;

	for (i = 0; i < hooklist->nodeinfo.hooks; i++)
		if (strcmp(hooklist->link[i].ourhook, hook) == 0)
			break;

	if (i == hooklist->nodeinfo.hooks) {
		free(resp);
		return (0);
	}

	next_node = 0;
	next_hook = NULL;
	if (strcmp(hooklist->link[i].nodeinfo.type, "tee") == 0) {
		if (strcmp(hooklist->link[i].peerhook, "left") == 0) {
			next_node = hooklist->link[i].nodeinfo.id;
			next_hook = "right";
		} else if (strcmp(hooklist->link[i].peerhook, "right") == 0) {
			next_node = hooklist->link[i].nodeinfo.id;
			next_hook = "left";
		}
	}
	free(resp);

	if (first) {
		ng_rmhook_id(node, hook);
		first = 0;
	} else {
		ng_shutdown_id(node);
	}
	if ((node = next_node) == 0)
		return (0);
	hook = next_hook;

	goto again;
}