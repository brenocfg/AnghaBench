#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nodeinfo {int /*<<< orphan*/  id; } ;
struct ng_mesg {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  ng_ID_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_NODEINFO ; 
 int /*<<< orphan*/  free (struct ng_mesg*) ; 
 struct ng_mesg* ng_dialog_node (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ng_ID_t
ng_node_id_node(const char *node)
{
	struct ng_mesg *resp;
	ng_ID_t id;

	if ((resp = ng_dialog_node(node, NGM_GENERIC_COOKIE, NGM_NODEINFO,
	    NULL, 0)) == NULL)
		return (0);
	id = ((struct nodeinfo *)(void *)resp->data)->id;
	free(resp);
	return (id);
}