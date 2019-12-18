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
 char* DEFLP ; 
 int /*<<< orphan*/  account (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acctfile ; 
 scalar_t__ allflag ; 
 int /*<<< orphan*/  atof (char const*) ; 
 int /*<<< orphan*/  chkprinter (char const*) ; 
 int /*<<< orphan*/  dumpit () ; 
 int /*<<< orphan*/  enter (char const*) ; 
 int errs ; 
 int /*<<< orphan*/  euid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  getuid () ; 
 int mflag ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int pflag ; 
 int /*<<< orphan*/  price ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  reverse ; 
 int /*<<< orphan*/  rewrite () ; 
 int /*<<< orphan*/  sort ; 
 int /*<<< orphan*/  sumfile ; 
 scalar_t__ summarize ; 
 int /*<<< orphan*/  uid ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	FILE *acctf;
	const char *cp, *printer;

	printer = NULL;
	euid = geteuid();	/* these aren't used in pac(1) */
	uid = getuid();
	while (--argc) {
		cp = *++argv;
		if (*cp++ == '-') {
			switch(*cp++) {
			case 'P':
				/*
				 * Printer name.
				 */
				printer = cp;
				continue;

			case 'p':
				/*
				 * get the price.
				 */
				price = atof(cp);
				pflag = 1;
				continue;

			case 's':
				/*
				 * Summarize and compress accounting file.
				 */
				summarize++;
				continue;

			case 'c':
				/*
				 * Sort by cost.
				 */
				sort++;
				continue;

			case 'm':
				/*
				 * disregard machine names for each user
				 */
				mflag = 1;
				continue;

			case 'r':
				/*
				 * Reverse sorting order.
				 */
				reverse++;
				continue;

			default:
				usage();
			}
		}
		(void) enter(--cp);
		allflag = 0;
	}
	if (printer == NULL && (printer = getenv("PRINTER")) == NULL)
		printer = DEFLP;
	if (!chkprinter(printer)) {
		printf("pac: unknown printer %s\n", printer);
		exit(2);
	}

	if ((acctf = fopen(acctfile, "r")) == NULL) {
		perror(acctfile);
		exit(1);
	}
	account(acctf);
	fclose(acctf);
	if ((acctf = fopen(sumfile, "r")) != NULL) {
		account(acctf);
		fclose(acctf);
	}
	if (summarize)
		rewrite();
	else
		dumpit();
	exit(errs);
}