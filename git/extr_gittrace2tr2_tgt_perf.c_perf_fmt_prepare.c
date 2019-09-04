#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
struct tr2tls_thread_ctx {scalar_t__ nr_open_regions; TYPE_1__ thread_name; } ;
struct tr2_tbuf {char* buf; } ;
struct strbuf {int len; } ;
struct repository {int /*<<< orphan*/  trace2_repo_id; } ;
struct TYPE_5__ {int len; char const* buf; } ;

/* Variables and functions */
 int TR2FMT_PERF_CATEGORY_WIDTH ; 
 int TR2FMT_PERF_FL_WIDTH ; 
 int /*<<< orphan*/  TR2FMT_PERF_MAX_EVENT_NAME ; 
 int TR2FMT_PERF_REPO_WIDTH ; 
 int TR2_INDENT_LENGTH (struct tr2tls_thread_ctx*) ; 
 int /*<<< orphan*/  TR2_MAX_THREAD_NAME ; 
 TYPE_2__ dots ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,TYPE_2__*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr2_sid_depth () ; 
 int /*<<< orphan*/  tr2_tbuf_local_time (struct tr2_tbuf*) ; 
 int /*<<< orphan*/  tr2env_perf_brief ; 

__attribute__((used)) static void perf_fmt_prepare(const char *event_name,
			     struct tr2tls_thread_ctx *ctx, const char *file,
			     int line, const struct repository *repo,
			     uint64_t *p_us_elapsed_absolute,
			     uint64_t *p_us_elapsed_relative,
			     const char *category, struct strbuf *buf)
{
	int len;

	strbuf_setlen(buf, 0);

	if (!tr2env_perf_brief) {
		struct tr2_tbuf tb_now;

		tr2_tbuf_local_time(&tb_now);
		strbuf_addstr(buf, tb_now.buf);
		strbuf_addch(buf, ' ');

		if (file && *file)
			strbuf_addf(buf, "%s:%d ", file, line);
		while (buf->len < TR2FMT_PERF_FL_WIDTH)
			strbuf_addch(buf, ' ');

		strbuf_addstr(buf, "| ");
	}

	strbuf_addf(buf, "d%d | ", tr2_sid_depth());
	strbuf_addf(buf, "%-*s | %-*s | ", TR2_MAX_THREAD_NAME,
		    ctx->thread_name.buf, TR2FMT_PERF_MAX_EVENT_NAME,
		    event_name);

	len = buf->len + TR2FMT_PERF_REPO_WIDTH;
	if (repo)
		strbuf_addf(buf, "r%d ", repo->trace2_repo_id);
	while (buf->len < len)
		strbuf_addch(buf, ' ');
	strbuf_addstr(buf, "| ");

	if (p_us_elapsed_absolute)
		strbuf_addf(buf, "%9.6f | ",
			    ((double)(*p_us_elapsed_absolute)) / 1000000.0);
	else
		strbuf_addf(buf, "%9s | ", " ");

	if (p_us_elapsed_relative)
		strbuf_addf(buf, "%9.6f | ",
			    ((double)(*p_us_elapsed_relative)) / 1000000.0);
	else
		strbuf_addf(buf, "%9s | ", " ");

	strbuf_addf(buf, "%-*s | ", TR2FMT_PERF_CATEGORY_WIDTH,
		    (category ? category : ""));

	if (ctx->nr_open_regions > 0) {
		int len_indent = TR2_INDENT_LENGTH(ctx);
		while (len_indent > dots.len) {
			strbuf_addbuf(buf, &dots);
			len_indent -= dots.len;
		}
		strbuf_addf(buf, "%.*s", len_indent, dots.buf);
	}
}