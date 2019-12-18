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
struct stat {int dummy; } ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  assert_config_entry_on_init (char*,int) ; 
 int /*<<< orphan*/  cl_git_write2file (char*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ p_stat (char*,struct stat*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_repo_init__detect_precompose_unicode_required(void)
{
#ifdef GIT_USE_ICONV
	char *composed = "ḱṷṓn", *decomposed = "ḱṷṓn";
	struct stat st;
	bool found_with_nfd;

	cl_git_write2file(composed, "whatever\n", 0, O_CREAT | O_WRONLY, 0666);
	found_with_nfd = (p_stat(decomposed, &st) == 0);
	cl_must_pass(p_unlink(composed));

	assert_config_entry_on_init("core.precomposeunicode", found_with_nfd);
#else
	assert_config_entry_on_init("core.precomposeunicode", GIT_ENOTFOUND);
#endif
}