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
struct strbuf {int len; int /*<<< orphan*/ * buf; } ;
struct repository {int /*<<< orphan*/  commondir; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_dir_sep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_cleanup_path (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_vaddf (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_git_common_path(const struct repository *repo,
			       struct strbuf *buf,
			       const char *fmt,
			       va_list args)
{
	strbuf_addstr(buf, repo->commondir);
	if (buf->len && !is_dir_sep(buf->buf[buf->len - 1]))
		strbuf_addch(buf, '/');
	strbuf_vaddf(buf, fmt, args);
	strbuf_cleanup_path(buf);
}