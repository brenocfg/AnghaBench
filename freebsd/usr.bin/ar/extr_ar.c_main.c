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
struct bsdar {char* progname; int options; char* filename; char mode; int argc; char** argv; int /*<<< orphan*/ * posarg; } ;

/* Variables and functions */
 int AR_A ; 
 int AR_B ; 
 int AR_C ; 
 int AR_CC ; 
 int AR_D ; 
 int AR_J ; 
 int AR_O ; 
 int AR_S ; 
 int AR_SS ; 
 int AR_TR ; 
 int AR_U ; 
 int AR_V ; 
 int AR_Z ; 
 int /*<<< orphan*/  EX_OK ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  EX_USAGE ; 
#define  OPTION_HELP 128 
 int /*<<< orphan*/  ar_mode_d (struct bsdar*) ; 
 int /*<<< orphan*/  ar_mode_m (struct bsdar*) ; 
 int /*<<< orphan*/  ar_mode_p (struct bsdar*) ; 
 int /*<<< orphan*/  ar_mode_q (struct bsdar*) ; 
 int /*<<< orphan*/  ar_mode_r (struct bsdar*) ; 
 int /*<<< orphan*/  ar_mode_s (struct bsdar*) ; 
 int /*<<< orphan*/  ar_mode_script (struct bsdar*) ; 
 int /*<<< orphan*/  ar_mode_t (struct bsdar*) ; 
 int /*<<< orphan*/  ar_mode_x (struct bsdar*) ; 
 int /*<<< orphan*/ * basename (char*) ; 
 int /*<<< orphan*/  bsdar_errc (struct bsdar*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bsdar_usage () ; 
 int /*<<< orphan*/  bsdar_version () ; 
 int /*<<< orphan*/  bsdar_warnc (struct bsdar*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  longopts ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memset (struct bsdar*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  only_mode (struct bsdar*,char*,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  ranlib_usage () ; 
 int /*<<< orphan*/  ranlib_version () ; 
 int /*<<< orphan*/  set_mode (struct bsdar*,int) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 int strlen (char*) ; 

int
main(int argc, char **argv)
{
	struct bsdar	*bsdar, bsdar_storage;
	char		*p;
	size_t		 len;
	int		 i, opt, Dflag, Uflag;

	bsdar = &bsdar_storage;
	memset(bsdar, 0, sizeof(*bsdar));
	Dflag = 0;
	Uflag = 0;

	if ((bsdar->progname = getprogname()) == NULL)
		bsdar->progname = "ar";

	/* Act like ranlib if our name ends in "ranlib"; this
	 * accommodates arm-freebsd7.1-ranlib, bsdranlib, etc. */
	len = strlen(bsdar->progname);
	if (len >= strlen("ranlib") &&
	    strcmp(bsdar->progname + len - strlen("ranlib"), "ranlib") == 0) {
		while ((opt = getopt_long(argc, argv, "tDUV", longopts,
		    NULL)) != -1) {
			switch(opt) {
			case 't':
				/* Ignored. */
				break;
			case 'D':
				Dflag = 1;
				Uflag = 0;
				break;
			case 'U':
				Uflag = 1;
				Dflag = 0;
				break;
			case 'V':
				ranlib_version();
				break;
			case OPTION_HELP:
				ranlib_usage();
			default:
				ranlib_usage();
			}
		}
		argv += optind;
		argc -= optind;

		if (*argv == NULL)
			ranlib_usage();

		/* Enable determinstic mode unless -U is set. */
		if (Uflag == 0)
			bsdar->options |= AR_D;
		bsdar->options |= AR_S;
		while ((bsdar->filename = *argv++) != NULL)
			ar_mode_s(bsdar);

		exit(EX_OK);
	} else {
		if (argc < 2)
			bsdar_usage();

		if (*argv[1] != '-') {
			len = strlen(argv[1]) + 2;
			if ((p = malloc(len)) == NULL)
				bsdar_errc(bsdar, EX_SOFTWARE, errno,
				    "malloc failed");
			*p = '-';
			(void)strlcpy(p + 1, argv[1], len - 1);
			argv[1] = p;
		}
	}

	while ((opt = getopt_long(argc, argv, "abCcdDfijlMmopqrSsTtUuVvxz",
	    longopts, NULL)) != -1) {
		switch(opt) {
		case 'a':
			bsdar->options |= AR_A;
			break;
		case 'b':
		case 'i':
			bsdar->options |= AR_B;
			break;
		case 'C':
			bsdar->options |= AR_CC;
			break;
		case 'c':
			bsdar->options |= AR_C;
			break;
		case 'd':
			set_mode(bsdar, opt);
			break;
		case 'D':
			Dflag = 1;
			Uflag = 0;
			break;
		case 'f':
		case 'T':
			bsdar->options |= AR_TR;
			break;
		case 'j':
			/* ignored */
			break;
		case 'l':
			/* ignored, for GNU ar comptibility */
			break;
		case 'M':
			set_mode(bsdar, opt);
			break;
		case 'm':
			set_mode(bsdar, opt);
			break;
		case 'o':
			bsdar->options |= AR_O;
			break;
		case 'p':
			set_mode(bsdar, opt);
			break;
		case 'q':
			set_mode(bsdar, opt);
			break;
		case 'r':
			set_mode(bsdar, opt);
			break;
		case 'S':
			bsdar->options |= AR_SS;
			break;
		case 's':
			bsdar->options |= AR_S;
			break;
		case 't':
			set_mode(bsdar, opt);
			break;
		case 'U':
			Uflag = 1;
			Dflag = 0;
			break;
		case 'u':
			bsdar->options |= AR_U;
			break;
		case 'V':
			bsdar_version();
			break;
		case 'v':
			bsdar->options |= AR_V;
			break;
		case 'x':
			set_mode(bsdar, opt);
			break;
		case 'z':
			/* ignored */
			break;
		case OPTION_HELP:
			bsdar_usage();
		default:
			bsdar_usage();
		}
	}

	argv += optind;
	argc -= optind;

	if (*argv == NULL && bsdar->mode != 'M')
		bsdar_usage();

	if (bsdar->options & AR_A && bsdar->options & AR_B)
		bsdar_errc(bsdar, EX_USAGE, 0,
		    "only one of -a and -[bi] options allowed");

	if (bsdar->options & AR_J && bsdar->options & AR_Z)
		bsdar_errc(bsdar, EX_USAGE, 0,
		    "only one of -j and -z options allowed");

	if (bsdar->options & AR_S && bsdar->options & AR_SS)
		bsdar_errc(bsdar, EX_USAGE, 0,
		    "only one of -s and -S options allowed");

	if (bsdar->options & (AR_A | AR_B)) {
		if (*argv == NULL)
			bsdar_errc(bsdar, EX_USAGE, 0,
			    "no position operand specified");
		if ((bsdar->posarg = basename(*argv)) == NULL)
			bsdar_errc(bsdar, EX_SOFTWARE, errno,
			    "basename failed");
		argc--;
		argv++;
	}

	/* Set determinstic mode for -D, and by default without -U. */
	if (Dflag || (Uflag == 0 && (bsdar->mode == 'q' || bsdar->mode == 'r' ||
	    (bsdar->mode == '\0' && bsdar->options & AR_S))))
		bsdar->options |= AR_D;

	if (bsdar->options & AR_A)
		only_mode(bsdar, "-a", "mqr");
	if (bsdar->options & AR_B)
		only_mode(bsdar, "-b", "mqr");
	if (bsdar->options & AR_C)
		only_mode(bsdar, "-c", "qr");
	if (bsdar->options & AR_CC)
		only_mode(bsdar, "-C", "x");
	if (Dflag)
		only_mode(bsdar, "-D", "qr");
	if (Uflag)
		only_mode(bsdar, "-U", "qr");
	if (bsdar->options & AR_O)
		only_mode(bsdar, "-o", "x");
	if (bsdar->options & AR_SS)
		only_mode(bsdar, "-S", "mqr");
	if (bsdar->options & AR_U)
		only_mode(bsdar, "-u", "qrx");

	if (bsdar->mode == 'M') {
		ar_mode_script(bsdar);
		exit(EX_OK);
	}

	if ((bsdar->filename = *argv) == NULL)
		bsdar_usage();

	bsdar->argc = --argc;
	bsdar->argv = ++argv;

	if ((!bsdar->mode || strchr("ptx", bsdar->mode)) &&
	    bsdar->options & AR_S) {
		ar_mode_s(bsdar);
		if (!bsdar->mode)
			exit(EX_OK);
	}

	switch(bsdar->mode) {
	case 'd':
		ar_mode_d(bsdar);
		break;
	case 'm':
		ar_mode_m(bsdar);
		break;
	case 'p':
		ar_mode_p(bsdar);
		break;
	case 'q':
		ar_mode_q(bsdar);
		break;
	case 'r':
		ar_mode_r(bsdar);
		break;
	case 't':
		ar_mode_t(bsdar);
		break;
	case 'x':
		ar_mode_x(bsdar);
		break;
	default:
		bsdar_usage();
		/* NOTREACHED */
	}

	for (i = 0; i < bsdar->argc; i++)
		if (bsdar->argv[i] != NULL)
			bsdar_warnc(bsdar, 0, "%s: not found in archive",
			    bsdar->argv[i]);

	exit(EX_OK);
}