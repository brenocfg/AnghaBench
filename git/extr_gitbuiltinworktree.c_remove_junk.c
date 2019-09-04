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
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  is_junk ; 
 scalar_t__ junk_git_dir ; 
 scalar_t__ junk_pid ; 
 scalar_t__ junk_work_tree ; 
 int /*<<< orphan*/  remove_dir_recursively (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void remove_junk(void)
{
	struct strbuf sb = STRBUF_INIT;
	if (!is_junk || getpid() != junk_pid)
		return;
	if (junk_git_dir) {
		strbuf_addstr(&sb, junk_git_dir);
		remove_dir_recursively(&sb, 0);
		strbuf_reset(&sb);
	}
	if (junk_work_tree) {
		strbuf_addstr(&sb, junk_work_tree);
		remove_dir_recursively(&sb, 0);
	}
	strbuf_release(&sb);
}