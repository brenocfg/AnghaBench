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
 int /*<<< orphan*/  GIT_DIR_ENVIRONMENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ setenv (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  setup_git_env (char const*) ; 

__attribute__((used)) static void set_git_dir_1(const char *path)
{
	if (setenv(GIT_DIR_ENVIRONMENT, path, 1))
		die(_("could not set GIT_DIR to '%s'"), path);
	setup_git_env(path);
}