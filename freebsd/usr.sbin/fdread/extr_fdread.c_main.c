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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int doread (int,int /*<<< orphan*/ *,char const*) ; 
 int doreadid (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 unsigned long fillbyte ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 scalar_t__ quiet ; 
 scalar_t__ recover ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 
 unsigned long strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,unsigned long) ; 

int
main(int argc, char **argv)
{
	int c, errs = 0;
	unsigned int numids = 0, trackno = 0;
	const char *fname = 0, *_devname = "/dev/fd0";
	char *cp;
	FILE *of = stdout;
	int fd;
	unsigned long ul;

	while ((c = getopt(argc, argv, "d:f:I:o:qrt:")) != -1)
		switch (c) {
		case 'd':
			_devname = optarg;
			break;

		case 'f':
			ul = strtoul(optarg, &cp, 0);
			if (*cp != '\0') {
				fprintf(stderr,
			"Bad argument %s to -f option; must be numeric\n",
					optarg);
				usage();
			}
			if (ul > 0xff)
				warnx(
			"Warning: fillbyte %#lx too large, truncating\n",
				      ul);
			fillbyte = ul & 0xff;
			break;

		case 'I':
			ul = strtoul(optarg, &cp, 0);
			if (*cp != '\0') {
				fprintf(stderr,
			"Bad argument %s to -I option; must be numeric\n",
					optarg);
				usage();
			}
			numids = ul;
			break;

		case 'o':
			fname = optarg;
			break;

		case 'q':
			quiet++;
			break;

		case 'r':
			recover++;
			break;

		case 't':
			ul = strtoul(optarg, &cp, 0);
			if (*cp != '\0') {
				fprintf(stderr,
			"Bad argument %s to -t option; must be numeric\n",
					optarg);
				usage();
			}
			trackno = ul;
			break;

		default:
			errs++;
		}
	argc -= optind;
	argv += optind;

	if (argc != 0 || errs)
		usage();
	/* check for mutually exclusive options */
	if (numids) {
		if (fname || quiet || recover)
			usage();
	} else {
		if (trackno)
			usage();
	}

	if (fname) {
		if ((of = fopen(fname, "w")) == NULL)
			err(EX_OSERR, "cannot create output file %s", fname);
	}

	if ((fd = open(_devname, O_RDONLY)) == -1)
		err(EX_OSERR, "cannot open device %s", _devname);

	return (numids? doreadid(fd, numids, trackno): doread(fd, of, _devname));
}