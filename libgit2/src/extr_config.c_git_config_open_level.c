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
typedef  int /*<<< orphan*/  git_config_level_t ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  backend_internal ;

/* Variables and functions */
 int find_backend_by_level (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int git_config__add_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_new (int /*<<< orphan*/ **) ; 

int git_config_open_level(
	git_config **cfg_out,
	const git_config *cfg_parent,
	git_config_level_t level)
{
	git_config *cfg;
	backend_internal *internal;
	int res;

	if ((res = find_backend_by_level(&internal, cfg_parent, level)) < 0)
		return res;

	if ((res = git_config_new(&cfg)) < 0)
		return res;

	if ((res = git_config__add_internal(cfg, internal, level, true)) < 0) {
		git_config_free(cfg);
		return res;
	}

	*cfg_out = cfg;

	return 0;
}