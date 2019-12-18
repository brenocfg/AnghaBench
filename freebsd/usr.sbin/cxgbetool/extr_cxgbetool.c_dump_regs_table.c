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
typedef  int /*<<< orphan*/  uint32_t ;
struct mod_regs {char* name; int /*<<< orphan*/  ri; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dump_block_regs (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
dump_regs_table(int argc, const char *argv[], const uint32_t *regs,
    const struct mod_regs *modtab, int nmodules)
{
	int i, j, match;

	for (i = 0; i < argc; i++) {
		for (j = 0; j < nmodules; j++) {
			if (!strcmp(argv[i], modtab[j].name))
				break;
		}

		if (j == nmodules) {
			warnx("invalid register block \"%s\"", argv[i]);
			fprintf(stderr, "\nAvailable blocks:");
			for ( ; nmodules; nmodules--, modtab++)
				fprintf(stderr, " %s", modtab->name);
			fprintf(stderr, "\n");
			return (EINVAL);
		}
	}

	for ( ; nmodules; nmodules--, modtab++) {

		match = argc == 0 ? 1 : 0;
		for (i = 0; !match && i < argc; i++) {
			if (!strcmp(argv[i], modtab->name))
				match = 1;
		}

		if (match)
			dump_block_regs(modtab->ri, regs);
	}

	return (0);
}