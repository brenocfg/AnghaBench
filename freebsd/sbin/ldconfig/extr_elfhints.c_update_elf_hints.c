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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_dir (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_dirs_from_file (char const*,char*) ; 
 int /*<<< orphan*/  read_elf_hints (char const*,int /*<<< orphan*/ ) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  write_elf_hints (char const*) ; 

void
update_elf_hints(const char *hintsfile, int argc, char **argv, int merge)
{
	int	i;

	if (merge)
		read_elf_hints(hintsfile, 0);
	for (i = 0;  i < argc;  i++) {
		struct stat	s;

		if (stat(argv[i], &s) == -1)
			warn("warning: %s", argv[i]);
		else if (S_ISREG(s.st_mode))
			read_dirs_from_file(hintsfile, argv[i]);
		else
			add_dir(hintsfile, argv[i], 0);
	}
	write_elf_hints(hintsfile);
}