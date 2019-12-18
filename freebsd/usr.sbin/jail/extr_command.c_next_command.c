#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct cfjail {int flags; int* comparam; TYPE_1__* comstring; TYPE_2__** intparams; } ;
typedef  enum intparam { ____Placeholder_intparam } intparam ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  val; } ;
struct TYPE_9__ {scalar_t__ len; } ;

/* Variables and functions */
 int IP_COMMAND ; 
 int IP_EXEC_CREATED ; 
 int IP_EXEC_POSTSTART ; 
 int IP_EXEC_PRESTART ; 
 int IP_EXEC_START ; 
#define  IP_MOUNT_DEVFS 133 
#define  IP_MOUNT_FDESCFS 132 
#define  IP_MOUNT_PROCFS 131 
#define  IP_STOP_TIMEOUT 130 
#define  IP__NULL 129 
#define  IP__OP 128 
 int JF_FAILED ; 
 int JF_FROM_RUNQ ; 
 int JF_STOP ; 
 int PF_REV ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_PREV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bool_param (TYPE_2__*) ; 
 int /*<<< orphan*/  cfstrings ; 
 TYPE_1__ dummystring ; 
 int /*<<< orphan*/  failed (struct cfjail*) ; 
 scalar_t__ paralimit ; 
 int /*<<< orphan*/  requeue (struct cfjail*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  requeue_head (struct cfjail*,int /*<<< orphan*/ *) ; 
 int run_command (struct cfjail*) ; 
 int /*<<< orphan*/  runnable ; 
 int /*<<< orphan*/  tq ; 

int
next_command(struct cfjail *j)
{
	enum intparam comparam;
	int create_failed, stopping;

	if (paralimit == 0) {
		if (j->flags & JF_FROM_RUNQ)
			requeue_head(j, &runnable);
		else
			requeue(j, &runnable);
		return 1;
	}
	j->flags &= ~JF_FROM_RUNQ;
	create_failed = (j->flags & (JF_STOP | JF_FAILED)) == JF_FAILED;
	stopping = (j->flags & JF_STOP) != 0;
	comparam = *j->comparam;
	for (;;) {
		if (j->comstring == NULL) {
			j->comparam += create_failed ? -1 : 1;
			switch ((comparam = *j->comparam)) {
			case IP__NULL:
				return 0;
			case IP_MOUNT_DEVFS:
				if (!bool_param(j->intparams[IP_MOUNT_DEVFS]))
					continue;
				j->comstring = &dummystring;
				break;
			case IP_MOUNT_FDESCFS:
				if (!bool_param(j->intparams[IP_MOUNT_FDESCFS]))
					continue;
				j->comstring = &dummystring;
				break;
			case IP_MOUNT_PROCFS:
				if (!bool_param(j->intparams[IP_MOUNT_PROCFS]))
					continue;
				j->comstring = &dummystring;
				break;
			case IP__OP:
			case IP_STOP_TIMEOUT:
				j->comstring = &dummystring;
				break;
			default:
				if (j->intparams[comparam] == NULL)
					continue;
				j->comstring = create_failed || (stopping &&
				    (j->intparams[comparam]->flags & PF_REV))
				    ? TAILQ_LAST(&j->intparams[comparam]->val,
					cfstrings)
				    : TAILQ_FIRST(&j->intparams[comparam]->val);
			}
		} else {
			j->comstring = j->comstring == &dummystring ? NULL :
			    create_failed || (stopping &&
			    (j->intparams[comparam]->flags & PF_REV))
			    ? TAILQ_PREV(j->comstring, cfstrings, tq)
			    : TAILQ_NEXT(j->comstring, tq);
		}
		if (j->comstring == NULL || j->comstring->len == 0 ||
		    (create_failed && (comparam == IP_EXEC_PRESTART ||
		    comparam == IP_EXEC_CREATED || comparam == IP_EXEC_START ||
		    comparam == IP_COMMAND || comparam == IP_EXEC_POSTSTART)))
			continue;
		switch (run_command(j)) {
		case -1:
			failed(j);
			/* FALLTHROUGH */
		case 1:
			return 1;
		}
	}
}