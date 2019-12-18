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
typedef  size_t u_int ;
struct typelist {size_t numtypes; TYPE_1__* typeinfo; } ;
struct TYPE_4__ {size_t* subs; size_t len; } ;
struct ngtype {size_t* name; TYPE_2__ index; scalar_t__ data; } ;
struct ng_mesg {size_t* name; TYPE_2__ index; scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  type_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT_OBJECT_OID (struct ngtype*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_LISTTYPES ; 
 int SNMP_ERR_GENERR ; 
 struct ngtype* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ngtype*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ngtype*) ; 
 int /*<<< orphan*/  link ; 
 struct ngtype* malloc (int) ; 
 struct ngtype* ng_dialog_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngtype_list ; 
 scalar_t__ ngtype_tick ; 
 int /*<<< orphan*/  snmp_node ; 
 int /*<<< orphan*/  strcpy (size_t*,int /*<<< orphan*/ ) ; 
 size_t strlen (size_t*) ; 
 scalar_t__ this_tick ; 

__attribute__((used)) static int
fetch_types(void)
{
	struct ngtype *t;
	struct typelist *typelist;
	struct ng_mesg *resp;
	u_int u, i;

	if (this_tick <= ngtype_tick)
		return (0);

	while ((t = TAILQ_FIRST(&ngtype_list)) != NULL) {
		TAILQ_REMOVE(&ngtype_list, t, link);
		free(t);
	}

	if ((resp = ng_dialog_id(snmp_node, NGM_GENERIC_COOKIE,
	    NGM_LISTTYPES, NULL, 0)) == NULL)
		return (SNMP_ERR_GENERR);
	typelist = (struct typelist *)(void *)resp->data;

	for (u = 0; u < typelist->numtypes; u++) {
		if ((t = malloc(sizeof(*t))) == NULL) {
			free(resp);
			return (SNMP_ERR_GENERR);
		}
		strcpy(t->name, typelist->typeinfo[u].type_name);
		t->index.subs[0] = strlen(t->name);
		t->index.len = t->index.subs[0] + 1;
		for (i = 0; i < t->index.subs[0]; i++)
			t->index.subs[i + 1] = t->name[i];

		INSERT_OBJECT_OID(t, &ngtype_list);
	}

	ngtype_tick = this_tick;

	free(resp);
	return (0);
}