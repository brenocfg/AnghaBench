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
struct testsuite {int /*<<< orphan*/  failed; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*,char const*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int test_finished(int result, struct strbuf *err, void *cb,
			 void *task_cb)
{
	struct testsuite *suite = cb;
	const char *name = (const char *)task_cb;

	if (result)
		string_list_append(&suite->failed, name);

	strbuf_addf(err, "%s: '%s'\n", result ? "FAIL" : "SUCCESS", name);

	return 0;
}