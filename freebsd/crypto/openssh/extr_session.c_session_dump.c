#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pid; int /*<<< orphan*/  chanid; int /*<<< orphan*/  self; int /*<<< orphan*/  next_unused; int /*<<< orphan*/  used; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,long) ; 
 TYPE_1__* sessions ; 
 int sessions_nalloc ; 

__attribute__((used)) static void
session_dump(void)
{
	int i;
	for (i = 0; i < sessions_nalloc; i++) {
		Session *s = &sessions[i];

		debug("dump: used %d next_unused %d session %d %p "
		    "channel %d pid %ld",
		    s->used,
		    s->next_unused,
		    s->self,
		    s,
		    s->chanid,
		    (long)s->pid);
	}
}