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
struct hent {double h_feetpages; scalar_t__ h_count; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  allflag ; 
 scalar_t__ any (char,char*) ; 
 double atof (char*) ; 
 int atoi (char*) ; 
 struct hent* enter (char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 struct hent* lookup (char*) ; 
 scalar_t__ mflag ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
account(FILE *acctf)
{
	char linebuf[BUFSIZ];
	double t;
	register char *cp, *cp2;
	register struct hent *hp;
	register int ic;

	while (fgets(linebuf, BUFSIZ, acctf) != NULL) {
		cp = linebuf;
		while (any(*cp, " \t"))
			cp++;
		t = atof(cp);
		while (any(*cp, ".0123456789"))
			cp++;
		while (any(*cp, " \t"))
			cp++;
		for (cp2 = cp; !any(*cp2, " \t\n"); cp2++)
			;
		ic = atoi(cp2);
		*cp2 = '\0';
		if (mflag && strchr(cp, ':'))
		    cp = strchr(cp, ':') + 1;
		hp = lookup(cp);
		if (hp == NULL) {
			if (!allflag)
				continue;
			hp = enter(cp);
		}
		hp->h_feetpages += t;
		if (ic)
			hp->h_count += ic;
		else
			hp->h_count++;
	}
}