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
 int /*<<< orphan*/  GIT_COMMON_DIR_ENVIRONMENT ; 
 int get_common_dir_noenv (struct strbuf*,char const*) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 

int get_common_dir(struct strbuf *sb, const char *gitdir)
{
	const char *git_env_common_dir = getenv(GIT_COMMON_DIR_ENVIRONMENT);
	if (git_env_common_dir) {
		strbuf_addstr(sb, git_env_common_dir);
		return 1;
	} else {
		return get_common_dir_noenv(sb, gitdir);
	}
}