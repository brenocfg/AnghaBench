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
struct stat {scalar_t__ st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (scalar_t__) ; 
 scalar_t__ S_ISREG (scalar_t__) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*,char const*) ; 
 char* read_gitfile (char const*) ; 
 scalar_t__ rename (char const*,char const*) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  write_file (char const*,char*,char const*) ; 

__attribute__((used)) static void separate_git_dir(const char *git_dir, const char *git_link)
{
	struct stat st;

	if (!stat(git_link, &st)) {
		const char *src;

		if (S_ISREG(st.st_mode))
			src = read_gitfile(git_link);
		else if (S_ISDIR(st.st_mode))
			src = git_link;
		else
			die(_("unable to handle file type %d"), (int)st.st_mode);

		if (rename(src, git_dir))
			die_errno(_("unable to move %s to %s"), src, git_dir);
	}

	write_file(git_link, "gitdir: %s", git_dir);
}