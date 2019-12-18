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
typedef  int /*<<< orphan*/  git_config_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int) ; 
 int config_error_readonly () ; 

__attribute__((used)) static int config_snapshot_unlock(git_config_backend *_cfg, int success)
{
	GIT_UNUSED(_cfg);
	GIT_UNUSED(success);

	return config_error_readonly();
}