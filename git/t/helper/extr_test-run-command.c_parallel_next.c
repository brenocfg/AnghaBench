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
struct strbuf {int dummy; } ;
struct child_process {int /*<<< orphan*/  argv; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_pushv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int number_callbacks ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 

__attribute__((used)) static int parallel_next(struct child_process *cp,
			 struct strbuf *err,
			 void *cb,
			 void **task_cb)
{
	struct child_process *d = cb;
	if (number_callbacks >= 4)
		return 0;

	argv_array_pushv(&cp->args, d->argv);
	strbuf_addstr(err, "preloaded output of a child\n");
	number_callbacks++;
	return 1;
}