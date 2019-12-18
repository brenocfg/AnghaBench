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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  uint64_t ;
struct tr2tls_thread_ctx {scalar_t__ nr_open_regions; } ;
struct repository {int dummy; } ;
struct json_writer {int /*<<< orphan*/  json; } ;

/* Variables and functions */
 struct json_writer JSON_WRITER_INIT ; 
 int /*<<< orphan*/  event_fmt_prepare (char const*,char const*,int,struct repository const*,struct json_writer*) ; 
 int /*<<< orphan*/  jw_end (struct json_writer*) ; 
 int /*<<< orphan*/  jw_object_begin (struct json_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_object_intmax (struct json_writer*,char*,scalar_t__) ; 
 int /*<<< orphan*/  jw_object_string (struct json_writer*,char*,char const*) ; 
 int /*<<< orphan*/  jw_release (struct json_writer*) ; 
 int /*<<< orphan*/  maybe_add_string_va (struct json_writer*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr2_dst_write_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr2dst_event ; 
 scalar_t__ tr2env_event_max_nesting_levels ; 
 struct tr2tls_thread_ctx* tr2tls_get_self () ; 

__attribute__((used)) static void fn_region_enter_printf_va_fl(const char *file, int line,
					 uint64_t us_elapsed_absolute,
					 const char *category,
					 const char *label,
					 const struct repository *repo,
					 const char *fmt, va_list ap)
{
	const char *event_name = "region_enter";
	struct tr2tls_thread_ctx *ctx = tr2tls_get_self();
	if (ctx->nr_open_regions <= tr2env_event_max_nesting_levels) {
		struct json_writer jw = JSON_WRITER_INIT;

		jw_object_begin(&jw, 0);
		event_fmt_prepare(event_name, file, line, repo, &jw);
		jw_object_intmax(&jw, "nesting", ctx->nr_open_regions);
		if (category)
			jw_object_string(&jw, "category", category);
		if (label)
			jw_object_string(&jw, "label", label);
		maybe_add_string_va(&jw, "msg", fmt, ap);
		jw_end(&jw);

		tr2_dst_write_line(&tr2dst_event, &jw.json);
		jw_release(&jw);
	}
}