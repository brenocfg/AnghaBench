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

/* Variables and functions */
#define  EEXIST 129 
#define  ENOEXEC 128 
 int errno ; 
 int getopt (int,char**,char*) ; 
 int kldload (char*) ; 
 scalar_t__ optind ; 
 scalar_t__ path_check (char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char** argv)
{
	int c;
	int check_loaded;
	int errors;
	int fileid;
	int quiet;
	int verbose;

	errors = 0;
	verbose = 0;
	quiet = 0;
	check_loaded = 0;

	while ((c = getopt(argc, argv, "nqv")) != -1) {
		switch (c) {
		case 'q':
			quiet = 1;
			verbose = 0;
			break;
		case 'v':
			verbose = 1;
			quiet = 0;
			break;
		case 'n':
			check_loaded = 1;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc == 0)
		usage();

	while (argc-- != 0) {
		if (path_check(argv[0], quiet) == 0) {
			fileid = kldload(argv[0]);
			if (fileid < 0) {
				if (check_loaded != 0 && errno == EEXIST) {
					if (verbose)
						printf("%s is already "
						    "loaded\n", argv[0]);
				} else {
					switch (errno) {
					case EEXIST:
						warnx("can't load %s: module "
						    "already loaded or "
						    "in kernel", argv[0]);
						break;
					case ENOEXEC:
						warnx("an error occurred while "
						    "loading module %s. "
						    "Please check dmesg(8) for "
						    "more details.", argv[0]);
						break;
					default:
						warn("can't load %s", argv[0]);
						break;
					}
					errors++;
				}
			} else {
				if (verbose)
					printf("Loaded %s, id=%d\n", argv[0],
					    fileid);
			}
		} else
			errors++;
		argv++;
	}

	return (errors ? 1 : 0);
}