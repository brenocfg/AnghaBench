#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct attr* last; struct attr* first; } ;
typedef  TYPE_1__ uiprivAttrList ;
struct attr {struct attr* prev; struct attr* next; } ;

/* Variables and functions */

__attribute__((used)) static struct attr *attrUnlink(uiprivAttrList *alist, struct attr *a)
{
	struct attr *p, *n;

	p = a->prev;
	n = a->next;
	a->prev = NULL;
	a->next = NULL;

	// only item in list?
	if (p == NULL && n == NULL) {
		alist->first = NULL;
		alist->last = NULL;
		return NULL;
	}
	// start of list?
	if (p == NULL) {
		n->prev = NULL;
		alist->first = n;
		return n;
	}
	// end of list?
	if (n == NULL) {
		p->next = NULL;
		alist->last = p;
		return NULL;
	}
	// middle of list
	p->next = n;
	n->prev = p;
	return n;
}