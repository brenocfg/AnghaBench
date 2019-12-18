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
struct config_options {int respect_includes; int ignore_repo; int ignore_worktree; int ignore_cmdline; int system_gently; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  config_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_with_options (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,struct config_options*) ; 

void read_very_early_config(config_fn_t cb, void *data)
{
	struct config_options opts = { 0 };

	opts.respect_includes = 1;
	opts.ignore_repo = 1;
	opts.ignore_worktree = 1;
	opts.ignore_cmdline = 1;
	opts.system_gently = 1;

	config_with_options(cb, data, NULL, &opts);
}