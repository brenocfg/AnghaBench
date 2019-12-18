#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  op; int /*<<< orphan*/  name; int /*<<< orphan*/  len; int /*<<< orphan*/ * next; } ;
struct event_cmd_exec {int /*<<< orphan*/ * line; TYPE_1__ evcmd; } ;
struct event_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ event_cmd_default_clone (void*) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 

struct event_cmd *
event_cmd_exec_clone(void *this)
{
	struct event_cmd_exec * newone = (struct event_cmd_exec *) event_cmd_default_clone(this);
	struct event_cmd_exec * oldone = this;

	newone->evcmd.next = NULL;
	newone->evcmd.len = oldone->evcmd.len;
	newone->evcmd.name = oldone->evcmd.name;
	newone->evcmd.op = oldone->evcmd.op;
	if ((newone->line = strdup(oldone->line)) == NULL)
		err(1, "out of memory");
	return (struct event_cmd *) newone;
}