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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  setup_git_directory_gently (int*) ; 
 int /*<<< orphan*/  skip_prefix (int /*<<< orphan*/ ,char*,char const**) ; 
 scalar_t__ strbuf_check_branch_ref (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int check_ref_format_branch(const char *arg)
{
	struct strbuf sb = STRBUF_INIT;
	const char *name;
	int nongit;

	setup_git_directory_gently(&nongit);
	if (strbuf_check_branch_ref(&sb, arg) ||
	    !skip_prefix(sb.buf, "refs/heads/", &name))
		die("'%s' is not a valid branch name", arg);
	printf("%s\n", name);
	strbuf_release(&sb);
	return 0;
}