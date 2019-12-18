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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_new () ; 
 scalar_t__ BN_dec2bn (int /*<<< orphan*/ **,char*) ; 
 scalar_t__ BN_hex2bn (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int LINE_MAX ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  hflag ; 
 scalar_t__ isblank (char) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  pr_fact (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	BIGNUM *val;
	int ch;
	char *p, buf[LINE_MAX];		/* > max number of digits. */

	ctx = BN_CTX_new();
	val = BN_new();
	if (val == NULL)
		errx(1, "can't initialise bignum");

	while ((ch = getopt(argc, argv, "h")) != -1)
		switch (ch) {
		case 'h':
			hflag++;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	/* No args supplied, read numbers from stdin. */
	if (argc == 0)
		for (;;) {
			if (fgets(buf, sizeof(buf), stdin) == NULL) {
				if (ferror(stdin))
					err(1, "stdin");
				exit (0);
			}
			for (p = buf; isblank(*p); ++p);
			if (*p == '\n' || *p == '\0')
				continue;
			if (*p == '-')
				errx(1, "negative numbers aren't permitted.");
			if (BN_dec2bn(&val, buf) == 0 &&
			    BN_hex2bn(&val, buf) == 0)
				errx(1, "%s: illegal numeric format.", buf);
			pr_fact(val);
		}
	/* Factor the arguments. */
	else
		for (; *argv != NULL; ++argv) {
			if (argv[0][0] == '-')
				errx(1, "negative numbers aren't permitted.");
			if (BN_dec2bn(&val, argv[0]) == 0 &&
			    BN_hex2bn(&val, argv[0]) == 0)
				errx(1, "%s: illegal numeric format.", argv[0]);
			pr_fact(val);
		}
	exit(0);
}