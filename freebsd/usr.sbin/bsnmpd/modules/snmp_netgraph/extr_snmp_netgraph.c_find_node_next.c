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
typedef  scalar_t__ u_int ;
struct nodeinfo {scalar_t__ id; } ;
struct ng_mesg {scalar_t__ data; } ;
struct namelist {scalar_t__ numnames; struct nodeinfo* nodeinfo; } ;
struct asn_oid {scalar_t__ len; scalar_t__* subs; } ;
typedef  scalar_t__ ng_ID_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_LISTNODES ; 
 int /*<<< orphan*/  free (struct ng_mesg*) ; 
 int /*<<< orphan*/  ncmp ; 
 struct ng_mesg* ng_dialog_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (struct nodeinfo*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_node ; 

__attribute__((used)) static int
find_node_next(const struct asn_oid *oid, u_int sub, struct nodeinfo *info)
{
	u_int idxlen = oid->len - sub;
	struct ng_mesg *resp;
	struct namelist *list;
	ng_ID_t id;
	u_int i;

	if ((resp = ng_dialog_id(snmp_node, NGM_GENERIC_COOKIE, NGM_LISTNODES,
	    NULL, 0)) == NULL)
		return (-1);
	list = (struct namelist *)(void *)resp->data;

	qsort(list->nodeinfo, list->numnames, sizeof(list->nodeinfo[0]), ncmp);

	if (idxlen == 0) {
		if (list->numnames == 0) {
			free(resp);
			return (-1);
		}
		*info = list->nodeinfo[0];
		free(resp);
		return (0);
	}
	id = oid->subs[sub];

	for (i = 0; i < list->numnames; i++)
		if (list->nodeinfo[i].id > id) {
			*info = list->nodeinfo[i];
			free(resp);
			return (0);
		}

	free(resp);
	return (-1);
}