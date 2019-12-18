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
struct valuelist {int port; int /*<<< orphan*/  name; struct valuelist* next; struct valuelist* prev; } ;
struct protoent {int p_proto; int /*<<< orphan*/  p_name; } ;

/* Variables and functions */
 struct valuelist* protolist ; 

__attribute__((used)) static struct protoent *
cgetprotobynumber(int proto) {				/*%< Host byte order. */
	struct valuelist **list = &protolist;
	struct valuelist *lp = *list;
	static struct protoent prot;

	for (; lp != NULL; lp = lp->next)
		if (lp->port == proto) {		/*%< Host byte order. */
			if (lp != *list) {
				lp->prev->next = lp->next;
				if (lp->next)
					lp->next->prev = lp->prev;
				(*list)->prev = lp;
				lp->next = *list;
				*list = lp;
			}
			prot.p_name = lp->name;
			prot.p_proto = lp->port;	/*%< Host byte order. */
			return (&prot);
		}
	return (0);
}