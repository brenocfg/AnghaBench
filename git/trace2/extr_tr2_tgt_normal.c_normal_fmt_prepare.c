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
struct tr2_tbuf {int /*<<< orphan*/  buf; } ;
struct strbuf {scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ TR2FMT_NORMAL_FL_WIDTH ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr2_tbuf_local_time (struct tr2_tbuf*) ; 
 int /*<<< orphan*/  tr2env_normal_be_brief ; 

__attribute__((used)) static void normal_fmt_prepare(const char *file, int line, struct strbuf *buf)
{
	strbuf_setlen(buf, 0);

	if (!tr2env_normal_be_brief) {
		struct tr2_tbuf tb_now;

		tr2_tbuf_local_time(&tb_now);
		strbuf_addstr(buf, tb_now.buf);
		strbuf_addch(buf, ' ');

		if (file && *file)
			strbuf_addf(buf, "%s:%d ", file, line);
		while (buf->len < TR2FMT_NORMAL_FL_WIDTH)
			strbuf_addch(buf, ' ');
	}
}