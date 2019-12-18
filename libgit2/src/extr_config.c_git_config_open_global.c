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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_XDG ; 
 int git_config_open_level (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_config_open_global(git_config **cfg_out, git_config *cfg)
{
	if (!git_config_open_level(cfg_out, cfg, GIT_CONFIG_LEVEL_XDG))
		return 0;

	return git_config_open_level(cfg_out, cfg, GIT_CONFIG_LEVEL_GLOBAL);
}