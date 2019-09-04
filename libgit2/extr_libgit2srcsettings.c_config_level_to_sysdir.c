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
#define  GIT_CONFIG_LEVEL_GLOBAL 131 
#define  GIT_CONFIG_LEVEL_PROGRAMDATA 130 
#define  GIT_CONFIG_LEVEL_SYSTEM 129 
#define  GIT_CONFIG_LEVEL_XDG 128 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int GIT_SYSDIR_GLOBAL ; 
 int GIT_SYSDIR_PROGRAMDATA ; 
 int GIT_SYSDIR_SYSTEM ; 
 int GIT_SYSDIR_XDG ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int config_level_to_sysdir(int config_level)
{
	int val = -1;

	switch (config_level) {
	case GIT_CONFIG_LEVEL_SYSTEM:
		val = GIT_SYSDIR_SYSTEM;
		break;
	case GIT_CONFIG_LEVEL_XDG:
		val = GIT_SYSDIR_XDG;
		break;
	case GIT_CONFIG_LEVEL_GLOBAL:
		val = GIT_SYSDIR_GLOBAL;
		break;
	case GIT_CONFIG_LEVEL_PROGRAMDATA:
		val = GIT_SYSDIR_PROGRAMDATA;
		break;
	default:
		git_error_set(
			GIT_ERROR_INVALID, "invalid config path selector %d", config_level);
	}

	return val;
}