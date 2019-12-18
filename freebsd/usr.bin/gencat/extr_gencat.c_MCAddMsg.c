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
struct TYPE_4__ {struct _msgT* le_next; } ;
struct _msgT {int msgId; int /*<<< orphan*/  str; TYPE_1__ entries; } ;
struct TYPE_6__ {struct _msgT* lh_first; } ;
struct TYPE_5__ {TYPE_3__ msghead; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_AFTER (struct _msgT*,struct _msgT*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (TYPE_3__*,struct _msgT*,int /*<<< orphan*/ ) ; 
 int NL_MSGMAX ; 
 TYPE_2__* curSet ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct _msgT*,char,int) ; 
 struct _msgT* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void
MCAddMsg(int msgId, const char *str)
{
	struct _msgT *p, *q;

	if (!curSet)
		error("can't specify a message when no set exists");

	if (msgId <= 0) {
		error("msgId's must be greater than zero");
		/* NOTREACHED */
	}
	if (msgId > NL_MSGMAX) {
		error("msgID exceeds limit");
		/* NOTREACHED */
	}

	p = curSet->msghead.lh_first;
	q = NULL;
	for (; p != NULL && p->msgId < msgId; q = p, p = p->entries.le_next);

	if (p && p->msgId == msgId) {
		free(p->str);
	} else {
		p = xmalloc(sizeof(struct _msgT));
		memset(p, '\0', sizeof(struct _msgT));

		if (q == NULL) {
			LIST_INSERT_HEAD(&curSet->msghead, p, entries);
		} else {
			LIST_INSERT_AFTER(q, p, entries);
		}
	}

	p->msgId = msgId;
	p->str = xstrdup(str);
}