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

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  perf_io_write_fl (char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  sq_append_quote_argv_pretty (struct strbuf*,char const**) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void fn_alias_fl(const char *file, int line, const char *alias,
			const char **argv)
{
	const char *event_name = "alias";
	struct strbuf buf_payload = STRBUF_INIT;

	strbuf_addf(&buf_payload, "alias:%s argv:[", alias);
	sq_append_quote_argv_pretty(&buf_payload, argv);
	strbuf_addch(&buf_payload, ']');

	perf_io_write_fl(file, line, event_name, NULL, NULL, NULL, NULL,
			 &buf_payload);
	strbuf_release(&buf_payload);
}