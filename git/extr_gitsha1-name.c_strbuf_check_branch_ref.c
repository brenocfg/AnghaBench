#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {scalar_t__ have_repository; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERPRET_BRANCH_LOCAL ; 
 int check_refname_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* startup_info ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_branchname (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_splice (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int strbuf_check_branch_ref(struct strbuf *sb, const char *name)
{
	if (startup_info->have_repository)
		strbuf_branchname(sb, name, INTERPRET_BRANCH_LOCAL);
	else
		strbuf_addstr(sb, name);

	/*
	 * This splice must be done even if we end up rejecting the
	 * name; builtin/branch.c::copy_or_rename_branch() still wants
	 * to see what the name expanded to so that "branch -m" can be
	 * used as a tool to correct earlier mistakes.
	 */
	strbuf_splice(sb, 0, 0, "refs/heads/", 11);

	if (*name == '-' ||
	    !strcmp(sb->buf, "refs/heads/HEAD"))
		return -1;

	return check_refname_format(sb->buf, 0);
}