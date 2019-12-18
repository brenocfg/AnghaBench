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
typedef  int /*<<< orphan*/  uint64_t ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  perf_io_write_fl (char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  sq_append_quote_argv_pretty (struct strbuf*,char const**) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void fn_exec_fl(const char *file, int line, uint64_t us_elapsed_absolute,
		       int exec_id, const char *exe, const char **argv)
{
	const char *event_name = "exec";
	struct strbuf buf_payload = STRBUF_INIT;

	strbuf_addf(&buf_payload, "id:%d ", exec_id);
	strbuf_addstr(&buf_payload, "argv:[");
	if (exe) {
		strbuf_addstr(&buf_payload, exe);
		if (argv[0])
			strbuf_addch(&buf_payload, ' ');
	}
	sq_append_quote_argv_pretty(&buf_payload, argv);
	strbuf_addch(&buf_payload, ']');

	perf_io_write_fl(file, line, event_name, NULL, &us_elapsed_absolute,
			 NULL, NULL, &buf_payload);
	strbuf_release(&buf_payload);
}