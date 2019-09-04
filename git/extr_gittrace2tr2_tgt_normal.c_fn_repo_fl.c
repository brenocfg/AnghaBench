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
struct repository {int /*<<< orphan*/  worktree; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  normal_io_write_fl (char const*,int,struct strbuf*) ; 
 int /*<<< orphan*/  sq_quote_buf_pretty (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void fn_repo_fl(const char *file, int line,
		       const struct repository *repo)
{
	struct strbuf buf_payload = STRBUF_INIT;

	strbuf_addstr(&buf_payload, "worktree ");
	sq_quote_buf_pretty(&buf_payload, repo->worktree);
	normal_io_write_fl(file, line, &buf_payload);
	strbuf_release(&buf_payload);
}