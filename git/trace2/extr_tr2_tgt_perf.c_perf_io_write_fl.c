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
struct tr2tls_thread_ctx {int dummy; } ;
struct strbuf {int dummy; } ;
struct repository {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  perf_fmt_prepare (char const*,struct tr2tls_thread_ctx*,char const*,int,struct repository const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  tr2_dst_write_line (int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  tr2dst_perf ; 
 struct tr2tls_thread_ctx* tr2tls_get_self () ; 

__attribute__((used)) static void perf_io_write_fl(const char *file, int line, const char *event_name,
			     const struct repository *repo,
			     uint64_t *p_us_elapsed_absolute,
			     uint64_t *p_us_elapsed_relative,
			     const char *category,
			     const struct strbuf *buf_payload)
{
	struct tr2tls_thread_ctx *ctx = tr2tls_get_self();
	struct strbuf buf_line = STRBUF_INIT;

	perf_fmt_prepare(event_name, ctx, file, line, repo,
			 p_us_elapsed_absolute, p_us_elapsed_relative, category,
			 &buf_line);
	strbuf_addbuf(&buf_line, buf_payload);
	tr2_dst_write_line(&tr2dst_perf, &buf_line);
	strbuf_release(&buf_line);
}