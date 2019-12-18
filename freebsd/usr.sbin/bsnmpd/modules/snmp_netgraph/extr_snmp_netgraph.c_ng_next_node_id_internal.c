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
typedef  int /*<<< orphan*/  ng_ID_t ;
struct TYPE_5__ {int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_2__ nodeinfo; int /*<<< orphan*/  peerhook; int /*<<< orphan*/  ourhook; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_LISTHOOKS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (struct ng_mesg*) ; 
 struct ng_mesg* ng_dialog_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_next_node_id (int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ng_ID_t
ng_next_node_id_internal(ng_ID_t node, const char *type, const char *hook,
    int skip_tee)
{
	struct ng_mesg *resp;
	struct hooklist *hooklist;
	u_int i;

	if ((resp = ng_dialog_id(node, NGM_GENERIC_COOKIE, NGM_LISTHOOKS,
	    NULL, 0)) == NULL) {
		syslog(LOG_ERR, "get hook list: %m");
		exit(1);
	}
	hooklist = (struct hooklist *)(void *)resp->data;

	for (i = 0; i < hooklist->nodeinfo.hooks; i++)
		if (strcmp(hooklist->link[i].ourhook, hook) == 0)
			break;

	if (i == hooklist->nodeinfo.hooks) {
		free(resp);
		return (0);
	}

	node = hooklist->link[i].nodeinfo.id;

	if (skip_tee && strcmp(hooklist->link[i].nodeinfo.type, "tee") == 0) {
		if (strcmp(hooklist->link[i].peerhook, "left") == 0)
			node = ng_next_node_id(node, type, "right");
		else if (strcmp(hooklist->link[i].peerhook, "right") == 0)
			node = ng_next_node_id(node, type, "left");
		else if (type != NULL &&
		    strcmp(hooklist->link[i].nodeinfo.type, type) != 0)
			node = 0;

	} else if (type != NULL &&
	    strcmp(hooklist->link[i].nodeinfo.type, type) != 0)
		node = 0;

	free(resp);

	return (node);
}