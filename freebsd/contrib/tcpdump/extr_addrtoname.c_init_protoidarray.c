#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  scalar_t__ u_char ;
struct protoidmem {int /*<<< orphan*/ * p_name; } ;
struct protoidlist {int /*<<< orphan*/ * name; scalar_t__* protoid; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ndo_error ) (TYPE_1__*,char*) ;} ;
typedef  TYPE_1__ netdissect_options ;
struct TYPE_7__ {scalar_t__ s; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 TYPE_5__* eproto_db ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct protoidmem* lookup_protoid (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 struct protoidlist* protoidlist ; 
 int /*<<< orphan*/ * strdup (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 

__attribute__((used)) static void
init_protoidarray(netdissect_options *ndo)
{
	register int i;
	register struct protoidmem *tp;
	const struct protoidlist *pl;
	u_char protoid[5];

	protoid[0] = 0;
	protoid[1] = 0;
	protoid[2] = 0;
	for (i = 0; eproto_db[i].s; i++) {
		u_short etype = htons(eproto_db[i].p);

		memcpy((char *)&protoid[3], (char *)&etype, 2);
		tp = lookup_protoid(ndo, protoid);
		tp->p_name = strdup(eproto_db[i].s);
		if (tp->p_name == NULL)
			(*ndo->ndo_error)(ndo,
					  "init_protoidarray: strdup(eproto_db[i].s)");
	}
	/* Hardwire some SNAP proto ID names */
	for (pl = protoidlist; pl->name != NULL; ++pl) {
		tp = lookup_protoid(ndo, pl->protoid);
		/* Don't override existing name */
		if (tp->p_name != NULL)
			continue;

		tp->p_name = pl->name;
	}
}