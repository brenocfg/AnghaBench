#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dir_struct {char* exclude_per_dir; int /*<<< orphan*/  ss_info_exclude; scalar_t__ untracked; int /*<<< orphan*/  ss_excludes_file; } ;
struct TYPE_2__ {scalar_t__ have_repository; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  access_or_warn (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_patterns_from_file_1 (struct dir_struct*,char const*,int /*<<< orphan*/ *) ; 
 char const* excludes_file ; 
 char* git_path_info_exclude () ; 
 TYPE_1__* startup_info ; 
 char* xdg_config_home (char*) ; 

void setup_standard_excludes(struct dir_struct *dir)
{
	dir->exclude_per_dir = ".gitignore";

	/* core.excludesfile defaulting to $XDG_CONFIG_HOME/git/ignore */
	if (!excludes_file)
		excludes_file = xdg_config_home("ignore");
	if (excludes_file && !access_or_warn(excludes_file, R_OK, 0))
		add_patterns_from_file_1(dir, excludes_file,
					 dir->untracked ? &dir->ss_excludes_file : NULL);

	/* per repository user preference */
	if (startup_info->have_repository) {
		const char *path = git_path_info_exclude();
		if (!access_or_warn(path, R_OK, 0))
			add_patterns_from_file_1(dir, path,
						 dir->untracked ? &dir->ss_info_exclude : NULL);
	}
}