#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nr; TYPE_1__* items; } ;
struct testsuite {scalar_t__ next; scalar_t__ write_junit_xml; scalar_t__ trace; scalar_t__ verbose_log; scalar_t__ verbose; scalar_t__ immediate; scalar_t__ quiet; TYPE_2__ tests; } ;
struct strbuf {int dummy; } ;
struct child_process {int /*<<< orphan*/  args; } ;
struct TYPE_3__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 

__attribute__((used)) static int next_test(struct child_process *cp, struct strbuf *err, void *cb,
		     void **task_cb)
{
	struct testsuite *suite = cb;
	const char *test;
	if (suite->next >= suite->tests.nr)
		return 0;

	test = suite->tests.items[suite->next++].string;
	argv_array_pushl(&cp->args, "sh", test, NULL);
	if (suite->quiet)
		argv_array_push(&cp->args, "--quiet");
	if (suite->immediate)
		argv_array_push(&cp->args, "-i");
	if (suite->verbose)
		argv_array_push(&cp->args, "-v");
	if (suite->verbose_log)
		argv_array_push(&cp->args, "-V");
	if (suite->trace)
		argv_array_push(&cp->args, "-x");
	if (suite->write_junit_xml)
		argv_array_push(&cp->args, "--write-junit-xml");

	strbuf_addf(err, "Output of '%s':\n", test);
	*task_cb = (void *)test;

	return 1;
}