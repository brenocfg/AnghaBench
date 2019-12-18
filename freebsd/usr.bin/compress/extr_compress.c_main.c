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
typedef  int /*<<< orphan*/  newname ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  compress (char*,char*,int) ; 
 int /*<<< orphan*/  cwarnx (char*,char*) ; 
 int /*<<< orphan*/  decompress (char*,char*,int) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  eval ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int force ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int strtol (int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  usage (int) ; 
 int verbose ; 

int
main(int argc, char *argv[])
{
	enum {COMPRESS, DECOMPRESS} style;
	size_t len;
	int bits, cat, ch;
	char *p, newname[MAXPATHLEN];

	cat = 0;
	if ((p = strrchr(argv[0], '/')) == NULL)
		p = argv[0];
	else
		++p;
	if (!strcmp(p, "uncompress"))
		style = DECOMPRESS;
	else if (!strcmp(p, "compress"))
		style = COMPRESS;
	else if (!strcmp(p, "zcat")) {
		cat = 1;
		style = DECOMPRESS;
	} else
		errx(1, "unknown program name");

	bits = 0;
	while ((ch = getopt(argc, argv, "b:cdfv")) != -1)
		switch(ch) {
		case 'b':
			bits = strtol(optarg, &p, 10);
			if (*p)
				errx(1, "illegal bit count -- %s", optarg);
			break;
		case 'c':
			cat = 1;
			break;
		case 'd':		/* Backward compatible. */
			style = DECOMPRESS;
			break;
		case 'f':
			force = 1;
			break;
		case 'v':
			verbose = 1;
			break;
		case '?':
		default:
			usage(style == COMPRESS);
		}
	argc -= optind;
	argv += optind;

	if (argc == 0) {
		switch(style) {
		case COMPRESS:
			(void)compress("/dev/stdin", "/dev/stdout", bits);
			break;
		case DECOMPRESS:
			(void)decompress("/dev/stdin", "/dev/stdout", bits);
			break;
		}
		exit (eval);
	}

	if (cat == 1 && style == COMPRESS && argc > 1)
		errx(1, "the -c option permits only a single file argument");

	for (; *argv; ++argv)
		switch(style) {
		case COMPRESS:
			if (strcmp(*argv, "-") == 0) {
				compress("/dev/stdin", "/dev/stdout", bits);
				break;
			} else if (cat) {
				compress(*argv, "/dev/stdout", bits);
				break;
			}
			if ((p = strrchr(*argv, '.')) != NULL &&
			    !strcmp(p, ".Z")) {
				cwarnx("%s: name already has trailing .Z",
				    *argv);
				break;
			}
			len = strlen(*argv);
			if (len > sizeof(newname) - 3) {
				cwarnx("%s: name too long", *argv);
				break;
			}
			memmove(newname, *argv, len);
			newname[len] = '.';
			newname[len + 1] = 'Z';
			newname[len + 2] = '\0';
			compress(*argv, newname, bits);
			break;
		case DECOMPRESS:
			if (strcmp(*argv, "-") == 0) {
				decompress("/dev/stdin", "/dev/stdout", bits);
				break;
			}
			len = strlen(*argv);
			if ((p = strrchr(*argv, '.')) == NULL ||
			    strcmp(p, ".Z")) {
				if (len > sizeof(newname) - 3) {
					cwarnx("%s: name too long", *argv);
					break;
				}
				memmove(newname, *argv, len);
				newname[len] = '.';
				newname[len + 1] = 'Z';
				newname[len + 2] = '\0';
				decompress(newname,
				    cat ? "/dev/stdout" : *argv, bits);
			} else {
				if (len - 2 > sizeof(newname) - 1) {
					cwarnx("%s: name too long", *argv);
					break;
				}
				memmove(newname, *argv, len - 2);
				newname[len - 2] = '\0';
				decompress(*argv,
				    cat ? "/dev/stdout" : newname, bits);
			}
			break;
		}
	exit (eval);
}