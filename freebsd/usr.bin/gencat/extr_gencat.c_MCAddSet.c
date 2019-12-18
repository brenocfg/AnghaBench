#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct _setT* le_next; } ;
struct _setT {int setId; int /*<<< orphan*/  msghead; TYPE_1__ entries; } ;
struct TYPE_5__ {struct _setT* lh_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_AFTER (struct _setT*,struct _setT*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (TYPE_2__*,struct _setT*,int /*<<< orphan*/ ) ; 
 int NL_SETMAX ; 
 struct _setT* curSet ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  memset (struct _setT*,char,int) ; 
 TYPE_2__ sethead ; 
 struct _setT* xmalloc (int) ; 

void
MCAddSet(int setId)
{
	struct _setT *p, *q;

	if (setId <= 0) {
		error("setId's must be greater than zero");
		/* NOTREACHED */
	}
	if (setId > NL_SETMAX) {
		error("setId exceeds limit");
		/* NOTREACHED */
	}

	p = sethead.lh_first;
	q = NULL;
	for (; p != NULL && p->setId < setId; q = p, p = p->entries.le_next);

	if (p && p->setId == setId) {
		;
	} else {
		p = xmalloc(sizeof(struct _setT));
		memset(p, '\0', sizeof(struct _setT));
		LIST_INIT(&p->msghead);

		p->setId = setId;

		if (q == NULL) {
			LIST_INSERT_HEAD(&sethead, p, entries);
		} else {
			LIST_INSERT_AFTER(q, p, entries);
		}
	}

	curSet = p;
}