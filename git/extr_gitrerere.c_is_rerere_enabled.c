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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_rr_cache () ; 
 int is_directory (int /*<<< orphan*/ ) ; 
 scalar_t__ mkdir_in_gitdir (int /*<<< orphan*/ ) ; 
 scalar_t__ rerere_enabled ; 

__attribute__((used)) static int is_rerere_enabled(void)
{
	int rr_cache_exists;

	if (!rerere_enabled)
		return 0;

	rr_cache_exists = is_directory(git_path_rr_cache());
	if (rerere_enabled < 0)
		return rr_cache_exists;

	if (!rr_cache_exists && mkdir_in_gitdir(git_path_rr_cache()))
		die(_("could not create directory '%s'"), git_path_rr_cache());
	return 1;
}