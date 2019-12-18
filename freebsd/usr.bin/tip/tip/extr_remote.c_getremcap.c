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
 char* AT ; 
 int /*<<< orphan*/  BEAUTIFY ; 
 int BR ; 
 int CL ; 
 char* CU ; 
 int /*<<< orphan*/  DC ; 
 int DEFBR ; 
 int DEFFS ; 
 int DL ; 
 scalar_t__ DU ; 
 char* DV ; 
 int /*<<< orphan*/  ECHOCHECK ; 
 char* ES ; 
 int ET ; 
 char* EX ; 
 char* FO ; 
 int FS ; 
 int /*<<< orphan*/  HALFDUPLEX ; 
 int /*<<< orphan*/  HARDWAREFLOW ; 
 scalar_t__ HD ; 
 char* HO ; 
 int HW ; 
 int LD ; 
 char* NOSTR ; 
 char* PN ; 
 char* PR ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RAWFTP ; 
 char* RC ; 
 char* RE ; 
 int R_OK ; 
 int /*<<< orphan*/  SCRIPT ; 
 int /*<<< orphan*/  TABEXPAND ; 
 int /*<<< orphan*/  TAND ; 
 int TTYDISC ; 
 int /*<<< orphan*/  VERBOSE ; 
 int W_OK ; 
 char* _PATH_REMOTE ; 
 char* __progname ; 
 scalar_t__ access (char*,int) ; 
 char*** caps ; 
 char** capstrings ; 
 int cgetent (char**,char**,char*) ; 
 scalar_t__ cgetflag (char*) ; 
 int cgetnum (char*,char*,int*) ; 
 int /*<<< orphan*/  cgetset (char*) ; 
 int /*<<< orphan*/  cgetstr (char*,char*,char**) ; 
 char** db_array ; 
 scalar_t__ equal (char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  setboolean (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vstring (char*,char*) ; 

__attribute__((used)) static void
getremcap(char *host)
{
	char **p, ***q, *bp, *rempath;
	int   stat;

	rempath = getenv("REMOTE");
	if (rempath != NULL) {
		if (*rempath != '/')
			/* we have an entry */
			cgetset(rempath);
		else {	/* we have a path */
			db_array[1] = rempath;
			db_array[2] = _PATH_REMOTE;
		}
	}

	if ((stat = cgetent(&bp, db_array, host)) < 0) {
		if ((DV != NULL) ||
		    (host[0] == '/' && access(DV = host, R_OK | W_OK) == 0)) {
			CU = DV;
			HO = host;
			HW = 1;
			DU = 0;
			if (!BR)
				BR = DEFBR;
			FS = DEFFS;
			return;
		}
		switch (stat) {
		case -1:
			fprintf(stderr, "%s: unknown host %s\n", __progname,
			    host);
			break;
		case -2:
			fprintf(stderr,
			    "%s: can't open host description file\n",
			    __progname);
			break;
		case -3:
			fprintf(stderr,
			    "%s: possible reference loop in host description file\n", __progname);
			break;
		}
		exit(3);
	}

	for (p = capstrings, q = caps; *p != NULL; p++, q++)
		if (**q == NULL)
			cgetstr(bp, *p, *q);
	if (!BR && (cgetnum(bp, "br", &BR) == -1))
		BR = DEFBR;
	if (!LD && (cgetnum(bp, "ld", &LD) == -1))
		LD = TTYDISC;
	if (cgetnum(bp, "fs", &FS) == -1)
		FS = DEFFS;
	if (DU < 0)
		DU = 0;
	else
		DU = cgetflag("du");
	if (DV == NOSTR) {
		fprintf(stderr, "%s: missing device spec\n", host);
		exit(3);
	}
	if (DU && CU == NOSTR)
		CU = DV;
	if (DU && PN == NOSTR) {
		fprintf(stderr, "%s: missing phone number\n", host);
		exit(3);
	}
	if (DU && AT == NOSTR) {
		fprintf(stderr, "%s: missing acu type\n", host);
		exit(3);
	}

	HD = cgetflag("hd");

	/*
	 * This effectively eliminates the "hw" attribute
	 *   from the description file
	 */
	if (!HW)
		HW = (CU == NOSTR) || (DU && equal(DV, CU));
	HO = host;
	/*
	 * see if uppercase mode should be turned on initially
	 */
	if (cgetflag("ra"))
		setboolean(value(RAISE), 1);
	if (cgetflag("ec"))
		setboolean(value(ECHOCHECK), 1);
	if (cgetflag("be"))
		setboolean(value(BEAUTIFY), 1);
	if (cgetflag("nb"))
		setboolean(value(BEAUTIFY), 0);
	if (cgetflag("sc"))
		setboolean(value(SCRIPT), 1);
	if (cgetflag("tb"))
		setboolean(value(TABEXPAND), 1);
	if (cgetflag("vb"))
		setboolean(value(VERBOSE), 1);
	if (cgetflag("nv"))
		setboolean(value(VERBOSE), 0);
	if (cgetflag("ta"))
		setboolean(value(TAND), 1);
	if (cgetflag("nt"))
		setboolean(value(TAND), 0);
	if (cgetflag("rw"))
		setboolean(value(RAWFTP), 1);
	if (cgetflag("hd"))
		setboolean(value(HALFDUPLEX), 1);
	if (cgetflag("dc"))
		setboolean(value(DC), 1);
	if (cgetflag("hf"))
		setboolean(value(HARDWAREFLOW), 1);
	if (RE == NOSTR)
		RE = (char *)"tip.record";
	if (EX == NOSTR)
		EX = (char *)"\t\n\b\f";
	if (ES != NOSTR)
		vstring("es", ES);
	if (FO != NOSTR)
		vstring("fo", FO);
	if (PR != NOSTR)
		vstring("pr", PR);
	if (RC != NOSTR)
		vstring("rc", RC);
	if (cgetnum(bp, "dl", &DL) == -1)
		DL = 0;
	if (cgetnum(bp, "cl", &CL) == -1)
		CL = 0;
	if (cgetnum(bp, "et", &ET) == -1)
		ET = 10;
}