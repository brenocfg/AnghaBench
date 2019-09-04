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
struct diff_flags {scalar_t__ ignore_submodules; int /*<<< orphan*/  override_submodule_config; } ;
struct diff_options {struct diff_flags flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_diffopt_flags_from_submodule_config (struct diff_options*,char const*) ; 

__attribute__((used)) static int is_submodule_ignored(const char *path, struct diff_options *options)
{
	int ignored = 0;
	struct diff_flags orig_flags = options->flags;
	if (!options->flags.override_submodule_config)
		set_diffopt_flags_from_submodule_config(options, path);
	if (options->flags.ignore_submodules)
		ignored = 1;
	options->flags = orig_flags;
	return ignored;
}