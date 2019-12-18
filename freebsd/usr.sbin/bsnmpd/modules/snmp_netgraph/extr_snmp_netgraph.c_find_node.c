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
typedef  size_t u_int ;
struct nodeinfo {int dummy; } ;
struct ng_mesg {scalar_t__ data; } ;
struct asn_oid {int /*<<< orphan*/ * subs; } ;
typedef  int /*<<< orphan*/  ng_ID_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_NODEINFO ; 
 int /*<<< orphan*/  free (struct ng_mesg*) ; 
 struct ng_mesg* ng_dialog_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_node(const struct asn_oid *oid, u_int sub, struct nodeinfo *info)
{
	ng_ID_t id = oid->subs[sub];
	struct ng_mesg *resp;

	if ((resp = ng_dialog_id(id, NGM_GENERIC_COOKIE, NGM_NODEINFO,
	    NULL, 0)) == NULL)
		return (-1);

	*info = *(struct nodeinfo *)(void *)resp->data;
	free(resp);
	return (0);
}