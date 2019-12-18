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
struct printer {double price100; int /*<<< orphan*/ * acct_file; } ;

/* Variables and functions */
#define  PCAPERR_NOTFOUND 130 
#define  PCAPERR_OSERR 129 
#define  PCAPERR_TCLOOP 128 
 int /*<<< orphan*/ * acctfile ; 
 scalar_t__ calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (struct printer*,char*,char*) ; 
 int getprintcap (char const*,struct printer*) ; 
 int /*<<< orphan*/  init_printer (struct printer*) ; 
 char* pcaperr (int) ; 
 int /*<<< orphan*/  pflag ; 
 double price ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 char* sumfile ; 

__attribute__((used)) static int
chkprinter(const char *ptrname)
{
	int stat;
	struct printer myprinter, *pp = &myprinter;

	init_printer(&myprinter);
	stat = getprintcap(ptrname, pp);
	switch(stat) {
	case PCAPERR_OSERR:
		printf("pac: getprintcap: %s\n", pcaperr(stat));
		exit(3);
	case PCAPERR_NOTFOUND:
		return 0;
	case PCAPERR_TCLOOP:
		fatal(pp, "%s", pcaperr(stat));
	}
	if ((acctfile = pp->acct_file) == NULL)
		errx(3, "accounting not enabled for printer %s", ptrname);
	if (!pflag && pp->price100)
		price = pp->price100/10000.0;
	sumfile = (char *) calloc(sizeof(char), strlen(acctfile)+5);
	if (sumfile == NULL)
		errx(1, "calloc failed");
	strcpy(sumfile, acctfile);
	strcat(sumfile, "_sum");
	return(1);
}