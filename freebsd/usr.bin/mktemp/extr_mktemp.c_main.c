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
 char* _PATH_TMP ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * mkdtemp (char*) ; 
 int mkstemp (char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
main(int argc, char **argv)
{
	int c, fd, ret;
	char *tmpdir;
	const char *prefix;
	char *name;
	int dflag, qflag, tflag, uflag;

	ret = dflag = qflag = tflag = uflag = 0;
	prefix = "mktemp";
	name = NULL;

	while ((c = getopt(argc, argv, "dqt:u")) != -1)
		switch (c) {
		case 'd':
			dflag++;
			break;

		case 'q':
			qflag++;
			break;

		case 't':
			prefix = optarg;
			tflag++;
			break;

		case 'u':
			uflag++;
			break;

		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (!tflag && argc < 1) {
		tflag = 1;
		prefix = "tmp";
	}

	if (tflag) {
		tmpdir = getenv("TMPDIR");
		if (tmpdir == NULL)
			asprintf(&name, "%s%s.XXXXXXXX", _PATH_TMP, prefix);
		else
			asprintf(&name, "%s/%s.XXXXXXXX", tmpdir, prefix);
		/* if this fails, the program is in big trouble already */
		if (name == NULL) {
			if (qflag)
				return (1);
			else
				errx(1, "cannot generate template");
		}
	}
		
	/* generate all requested files */
	while (name != NULL || argc > 0) {
		if (name == NULL) {
			name = strdup(argv[0]);
			argv++;
			argc--;
		}

		if (dflag) {
			if (mkdtemp(name) == NULL) {
				ret = 1;
				if (!qflag)
					warn("mkdtemp failed on %s", name);
			} else {
				printf("%s\n", name);
				if (uflag)
					rmdir(name);
			}
		} else {
			fd = mkstemp(name);
			if (fd < 0) {
				ret = 1;
				if (!qflag)
					warn("mkstemp failed on %s", name);
			} else {
				close(fd);
				if (uflag)
					unlink(name);
				printf("%s\n", name);
			}
		}
		if (name)
			free(name);
		name = NULL;
	}
	return (ret);
}