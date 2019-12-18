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
struct apply_state {int dummy; } ;

/* Variables and functions */
 int apply_all_patches (struct apply_state*,int,char const**,int) ; 
 int apply_parse_options (int,char const**,struct apply_state*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_usage ; 
 scalar_t__ check_apply_state (struct apply_state*,int) ; 
 int /*<<< orphan*/  clear_apply_state (struct apply_state*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ init_apply_state (struct apply_state*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  the_repository ; 

int cmd_apply(int argc, const char **argv, const char *prefix)
{
	int force_apply = 0;
	int options = 0;
	int ret;
	struct apply_state state;

	if (init_apply_state(&state, the_repository, prefix))
		exit(128);

	argc = apply_parse_options(argc, argv,
				   &state, &force_apply, &options,
				   apply_usage);

	if (check_apply_state(&state, force_apply))
		exit(128);

	ret = apply_all_patches(&state, argc, argv, options);

	clear_apply_state(&state);

	return ret;
}