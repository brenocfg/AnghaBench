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
 int /*<<< orphan*/  _PATH_ELF32_HINTS ; 
 int /*<<< orphan*/  _PATH_ELFSOFT_HINTS ; 
 int /*<<< orphan*/  _PATH_ELF_HINTS ; 
 int /*<<< orphan*/  _PATH_LD32_HINTS ; 
 int /*<<< orphan*/  _PATH_LD_HINTS ; 
 int /*<<< orphan*/  add_search_path (char*) ; 
 int buildhints () ; 
 char* concat (char*,char*,int /*<<< orphan*/ ) ; 
 char* dir_list ; 
 int dodir (int /*<<< orphan*/ ,int) ; 
 int dofile (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  hints_file ; 
 int insecure ; 
 int justread ; 
 int /*<<< orphan*/  list_elf_hints (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listhints () ; 
 int merge ; 
 int n_search_dirs ; 
 int nostd ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int readhints () ; 
 int rescan ; 
 int /*<<< orphan*/ * search_dirs ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  std_search_path () ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  update_elf_hints (int /*<<< orphan*/ ,int,char**,int) ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char **argv)
{
	int		i, c;
	int		rval = 0;
	int		is_aout = 0;
	int		is_32 = 0;
	int		is_soft = 0;

	while (argc > 1) {
		if (strcmp(argv[1], "-aout") == 0) {
			is_aout = 1;
			argc--;
			argv++;
		} else if (strcmp(argv[1], "-elf") == 0) {
			is_aout = 0;
			argc--;
			argv++;
		} else if (strcmp(argv[1], "-32") == 0) {
			is_32 = 1;
			argc--;
			argv++;
		} else if (strcmp(argv[1], "-soft") == 0) {
			is_soft = 1;
			argc--;
			argv++;
		} else {
			break;
		}
	}

	if (is_soft)
		hints_file = _PATH_ELFSOFT_HINTS;	/* Never will have a.out softfloat */
	else if (is_32)
		hints_file = is_aout ? _PATH_LD32_HINTS : _PATH_ELF32_HINTS;
	else
		hints_file = is_aout ? _PATH_LD_HINTS : _PATH_ELF_HINTS;
	if (argc == 1)
		rescan = 1;
	else while((c = getopt(argc, argv, "Rf:imrsv")) != -1) {
		switch (c) {
		case 'R':
			rescan = 1;
			break;
		case 'f':
			hints_file = optarg;
			break;
		case 'i':
			insecure = 1;
			break;
		case 'm':
			merge = 1;
			break;
		case 'r':
			justread = 1;
			break;
		case 's':
			nostd = 1;
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			usage();
			break;
		}
	}

	if (!is_aout) {
		if (justread)
			list_elf_hints(hints_file);
		else
			update_elf_hints(hints_file, argc - optind,
			    argv + optind, merge || rescan);
		return 0;
	}

	/* Here begins the aout libs processing */
	dir_list = strdup("");

	if (justread || merge || rescan) {
		if ((rval = readhints()) != 0)
			return rval;
	}

	if (!nostd && !merge && !rescan)
		std_search_path();

	/* Add any directories/files from the command line */
	if (!justread) {
		for (i = optind; i < argc; i++) {
			struct stat stbuf;

			if (stat(argv[i], &stbuf) == -1) {
				warn("%s", argv[i]);
				rval = -1;
			} else if (strcmp(argv[i], "/usr/lib") == 0) {
				warnx("WARNING! '%s' can not be used", argv[i]);
				rval = -1;
			} else {
				/*
				 * See if this is a directory-containing
				 * file instead of a directory
				 */
				if (S_ISREG(stbuf.st_mode))
					rval |= dofile(argv[i], 0);
				else
					add_search_path(argv[i]);
			}
		}
	}

	for (i = 0; i < n_search_dirs; i++) {
		char *cp = concat(dir_list, *dir_list?":":"", search_dirs[i]);
		free(dir_list);
		dir_list = cp;
	}

	if (justread) {
		listhints();
		return 0;
	}

	for (i = 0; i < n_search_dirs; i++)
		rval |= dodir(search_dirs[i], 1);

	rval |= buildhints();

	return rval;
}