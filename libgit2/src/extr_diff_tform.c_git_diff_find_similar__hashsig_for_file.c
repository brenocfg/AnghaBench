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
typedef  int /*<<< orphan*/  git_hashsig_option_t ;
typedef  int /*<<< orphan*/  git_hashsig ;
typedef  int /*<<< orphan*/  git_diff_file ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int git_hashsig_create_fromfile (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 

int git_diff_find_similar__hashsig_for_file(
	void **out, const git_diff_file *f, const char *path, void *p)
{
	git_hashsig_option_t opt = (git_hashsig_option_t)(intptr_t)p;

	GIT_UNUSED(f);
	return git_hashsig_create_fromfile((git_hashsig **)out, path, opt);
}