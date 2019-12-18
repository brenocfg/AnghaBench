#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  string ;
struct TYPE_4__ {char* acu_name; int /*<<< orphan*/  (* acu_abort ) () ;scalar_t__ (* acu_dialer ) (char*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AT ; 
 scalar_t__ CM ; 
 int /*<<< orphan*/  CU ; 
 int /*<<< orphan*/  DU ; 
 char* DV ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  HOST ; 
 TYPE_1__* NOACU ; 
 int /*<<< orphan*/ * NOFILE ; 
 scalar_t__ NOSTR ; 
 char* PH ; 
 char* PN ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  VERBOSE ; 
 TYPE_1__* acu ; 
 int /*<<< orphan*/  acuabort ; 
 TYPE_1__* acutype (int /*<<< orphan*/ ) ; 
 scalar_t__ conflag ; 
 int /*<<< orphan*/  disconnect (scalar_t__) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  jmpbuf ; 
 int /*<<< orphan*/  logent (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  parwrite (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setboolean (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size (scalar_t__) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strcspn (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ stub2 (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 () ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

char *
con(void)
{
	char *cp = PN;
	char *phnum, string[256];
	FILE *fd;
	volatile int tried = 0;

	if (!DU) {		/* regular connect message */
		if (CM != NOSTR)
			parwrite(FD, CM, size(CM));
		logent(value(HOST), "", DV, "call completed");
		return (NOSTR);
	}
	/*
	 * @ =>'s use data base in PHONES environment variable
	 *        otherwise, use /etc/phones
	 */
	signal(SIGINT, acuabort);
	signal(SIGQUIT, acuabort);
	if (setjmp(jmpbuf)) {
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		printf("\ncall aborted\n");
		logent(value(HOST), "", "", "call aborted");
		if (acu != NOACU) {
			setboolean(value(VERBOSE), FALSE);
			if (conflag)
				disconnect(NOSTR);
			else
				(*acu->acu_abort)();
		}
		return ("interrupt");
	}
	if ((acu = acutype(AT)) == NOACU)
		return ("unknown ACU type");
	if (*cp != '@') {
		while (*cp) {
			phnum = cp;
			cp += strcspn(cp, ",");
			if (*cp != '\0')
				*cp++ = '\0';

			if (strlen(phnum) == 0)
				continue;

			conflag = (*acu->acu_dialer)(phnum, CU);
			if (conflag)
				break;

			logent(value(HOST), phnum, acu->acu_name, "call failed");
			tried++;
		}
	} else {
		if ((fd = fopen(PH, "r")) == NOFILE) {
			printf("%s: ", PH);
			return ("can't open phone number file");
		}
		while (fgets(string, sizeof(string), fd) != NOSTR) {
			cp = &string[strcspn(string, " \t\n")];
			if (*cp != '\0')
				*cp++ = '\0';

			if (strcmp(string, value(HOST)) != 0)
				continue;

			cp += strspn(cp, " \t\n");
			phnum = cp;
			*(cp + strcspn(cp, ",\n")) = '\0';

			if (strlen(phnum) == 0)
				continue;

			conflag = (*acu->acu_dialer)(phnum, CU);
			if (conflag)
				break;

			logent(value(HOST), phnum, acu->acu_name, "call failed");
			tried++;
		}
		fclose(fd);
	}
	if (conflag) {
		if (CM != NOSTR)
			parwrite(FD, CM, size(CM));
		logent(value(HOST), phnum, acu->acu_name, "call completed");
		return (NOSTR);
	} else if (!tried) {
		logent(value(HOST), "", acu->acu_name, "missing phone number");
		return ("missing phone number");
	} else {
		(*acu->acu_abort)();
		return ("call failed");
	}
}