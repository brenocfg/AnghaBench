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
struct valuelist {struct valuelist* prev; struct valuelist* next; int /*<<< orphan*/  port; int /*<<< orphan*/ * name; } ;
struct protoent {int /*<<< orphan*/  p_proto; int /*<<< orphan*/  p_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  endprotoent () ; 
 int /*<<< orphan*/  free (struct valuelist*) ; 
 struct protoent* getprotoent () ; 
 scalar_t__ malloc (int) ; 
 struct valuelist* protolist ; 
 int /*<<< orphan*/  setprotoent (int) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 

void
res_buildprotolist(void) {
	struct protoent *pp;
	struct valuelist *slp;

#ifdef MAYBE_HESIOD
	setprotoent(0);
#else
	setprotoent(1);
#endif
	while ((pp = getprotoent()) != NULL) {
		slp = (struct valuelist *)malloc(sizeof(struct valuelist));
		if (!slp)
			break;
		slp->name = strdup(pp->p_name);
		if (slp->name == NULL) {
			free(slp);
			break;
		}
		slp->port = pp->p_proto;	/*%< host byte order */
		slp->next = protolist;
		slp->prev = NULL;
		if (protolist)
			protolist->prev = slp;
		protolist = slp;
	}
	endprotoent();
}