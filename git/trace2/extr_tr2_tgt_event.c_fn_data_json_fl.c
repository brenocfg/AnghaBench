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
typedef  scalar_t__ uint64_t ;
struct tr2tls_thread_ctx {scalar_t__ nr_open_regions; } ;
struct repository {int dummy; } ;
struct json_writer {int /*<<< orphan*/  json; } ;

/* Variables and functions */
 struct json_writer JSON_WRITER_INIT ; 
 int /*<<< orphan*/  event_fmt_prepare (char const*,char const*,int,struct repository const*,struct json_writer*) ; 
 int /*<<< orphan*/  jw_end (struct json_writer*) ; 
 int /*<<< orphan*/  jw_object_begin (struct json_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_object_double (struct json_writer*,char*,int,double) ; 
 int /*<<< orphan*/  jw_object_intmax (struct json_writer*,char*,scalar_t__) ; 
 int /*<<< orphan*/  jw_object_string (struct json_writer*,char*,char const*) ; 
 int /*<<< orphan*/  jw_object_sub_jw (struct json_writer*,char*,struct json_writer const*) ; 
 int /*<<< orphan*/  jw_release (struct json_writer*) ; 
 int /*<<< orphan*/  tr2_dst_write_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr2dst_event ; 
 scalar_t__ tr2env_event_max_nesting_levels ; 
 struct tr2tls_thread_ctx* tr2tls_get_self () ; 

__attribute__((used)) static void fn_data_json_fl(const char *file, int line,
			    uint64_t us_elapsed_absolute,
			    uint64_t us_elapsed_region, const char *category,
			    const struct repository *repo, const char *key,
			    const struct json_writer *value)
{
	const char *event_name = "data_json";
	struct tr2tls_thread_ctx *ctx = tr2tls_get_self();
	if (ctx->nr_open_regions <= tr2env_event_max_nesting_levels) {
		struct json_writer jw = JSON_WRITER_INIT;
		double t_abs = (double)us_elapsed_absolute / 1000000.0;
		double t_rel = (double)us_elapsed_region / 1000000.0;

		jw_object_begin(&jw, 0);
		event_fmt_prepare(event_name, file, line, repo, &jw);
		jw_object_double(&jw, "t_abs", 6, t_abs);
		jw_object_double(&jw, "t_rel", 6, t_rel);
		jw_object_intmax(&jw, "nesting", ctx->nr_open_regions);
		jw_object_string(&jw, "category", category);
		jw_object_string(&jw, "key", key);
		jw_object_sub_jw(&jw, "value", value);
		jw_end(&jw);

		tr2_dst_write_line(&tr2dst_event, &jw.json);
		jw_release(&jw);
	}
}