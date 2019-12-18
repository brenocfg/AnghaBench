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
struct iconv_fallbacks {int /*<<< orphan*/ * data; int /*<<< orphan*/  wc_to_mb_fallback; int /*<<< orphan*/  mb_to_uc_fallback; int /*<<< orphan*/  mb_to_wc_fallback; int /*<<< orphan*/  uc_to_mb_fallback; } ;
typedef  int /*<<< orphan*/  iconv_t ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  ICONV_SET_FALLBACKS ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,char*,char*) ; 
 int cflag ; 
 char* citrus_common ; 
 int dflag ; 
 int /*<<< orphan*/  do_conv (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 char getopt_long (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ iconv_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iconv_open (char*,char*) ; 
 scalar_t__ iconvctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iconv_fallbacks*) ; 
 int iflag ; 
 int lflag ; 
 int /*<<< orphan*/  long_options ; 
 int /*<<< orphan*/  mb_to_uc_fb ; 
 int /*<<< orphan*/  mb_to_wc_fb ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  optstr ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rflag ; 
 int tflag ; 
 int /*<<< orphan*/  uc_to_mb_fb ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  wc_to_mb_fb ; 

int
main (int argc, char *argv[])
{
	struct iconv_fallbacks fbs;
	iconv_t cd;
	char *tocode;
	char c;

	while (((c = getopt_long(argc, argv, optstr, long_options, NULL)) != -1)) {
		switch (c) {
		case 'c':
			cflag = true;
			break;
		case 'd':
			dflag = true;
			break;
		case 'i':
			iflag = true;
			break;
		case 'l':
			lflag = true;
			break;
		case 'r':
			rflag = true;
			break;
		case 't':
			tflag = true;
			break;
		}
	}
	argc -= optind;
	argv += optind;

	if (argc < 1)
		usage();

	fbs.uc_to_mb_fallback = uc_to_mb_fb;
	fbs.mb_to_wc_fallback = mb_to_wc_fb;
	fbs.mb_to_uc_fallback = mb_to_uc_fb;
	fbs.wc_to_mb_fallback = wc_to_mb_fb;
	fbs.data = NULL;

	if (argc == 2) {
		asprintf(&tocode, "%s%s%s", argv[1], tflag ? "//TRASNLIT" : "",
		    iflag ? "//IGNORE" : "");

		if ((cd = iconv_open(tocode, argv[0])) == (iconv_t)-1)
			err(1, NULL);
		if (dflag) {
			if (iconvctl(cd, ICONV_SET_FALLBACKS, &fbs) != 0)
				err(1, NULL);
		}
		do_conv(cd, false);
	} else if (rflag) {
		asprintf(&tocode, "%s%s%s", argv[0], tflag ? "//TRANSLIT" : "",
		    iflag ? "//IGNORE" : "");

		if ((cd = iconv_open(tocode, "UTF-32LE")) == (iconv_t)-1)
			err(1, NULL);
		if (dflag && iconvctl(cd, ICONV_SET_FALLBACKS, &fbs) != 0)
			err(1, NULL);
		if (cflag) {
			printf("# $FreeBSD$\n\n");
			printf("TYPE\t\tROWCOL\n");
			printf("NAME\t\tUCS/%s\n", argv[0]);
			printf("%s", citrus_common);
		}
		do_conv(cd, true);
	} else {
		if ((cd = iconv_open("UTF-32LE//TRANSLIT", argv[0])) == (iconv_t)-1)
			err(1, NULL);
		if (dflag && (iconvctl(cd, ICONV_SET_FALLBACKS, &fbs) != 0))
			err(1, NULL);
		if (cflag) {
			printf("# $FreeBSD$\n\n");
			printf("TYPE\t\tROWCOL\n");
			printf("NAME\t\t%s/UCS\n", argv[0]);
			printf("%s", citrus_common);
                }
		do_conv(cd, false);
	}

	if (iconv_close(cd) != 0)
		err(1, NULL);

	return (EXIT_SUCCESS);
}