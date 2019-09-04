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
 int /*<<< orphan*/  normal_fmt_prepare (char const*,int,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  tr2_dst_write_line (int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  tr2dst_normal ; 

__attribute__((used)) static void normal_io_write_fl(const char *file, int line,
			       const struct strbuf *buf_payload)
{
	struct strbuf buf_line = STRBUF_INIT;

	normal_fmt_prepare(file, line, &buf_line);
	strbuf_addbuf(&buf_line, buf_payload);
	tr2_dst_write_line(&tr2dst_normal, &buf_line);
	strbuf_release(&buf_line);
}