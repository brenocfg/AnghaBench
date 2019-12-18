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
struct TYPE_5__ {struct _msgT* le_next; } ;
struct _msgT {int msgId; int /*<<< orphan*/  str; TYPE_2__ entries; } ;
struct TYPE_4__ {struct _msgT* lh_first; } ;
struct TYPE_6__ {TYPE_1__ msghead; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct _msgT*,int /*<<< orphan*/ ) ; 
 TYPE_3__* curSet ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ *,char*) ; 

void
MCDelMsg(int msgId)
{
	struct _msgT *msg;

	if (!curSet)
		error("you can't delete a message before defining the set");

	msg = curSet->msghead.lh_first;
	for (; msg != NULL && msg->msgId < msgId; msg = msg->entries.le_next);

	if (msg && msg->msgId == msgId) {
		free(msg->str);
		LIST_REMOVE(msg, entries);
		return;
	}
	warning(NULL, "specified msg doesn't exist");
}