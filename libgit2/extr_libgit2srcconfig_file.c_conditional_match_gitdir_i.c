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
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int do_match_gitdir (int*,int /*<<< orphan*/  const*,char const*,char const*,int) ; 

__attribute__((used)) static int conditional_match_gitdir_i(
	int *matches,
	const git_repository *repo,
	const char *cfg_file,
	const char *value)
{
	return do_match_gitdir(matches, repo, cfg_file, value, true);
}