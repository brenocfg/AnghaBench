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
struct hent {double h_feetpages; char* h_name; int h_count; struct hent* h_link; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int HSHSIZE ; 
 int /*<<< orphan*/  acctfile ; 
 int /*<<< orphan*/  errs ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,double,char*,int) ; 
 struct hent** hashtab ; 
 int /*<<< orphan*/  sumfile ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rewrite(void)
{
	register struct hent *hp;
	register int i;
	FILE *acctf;

	if ((acctf = fopen(sumfile, "w")) == NULL) {
		warn("%s", sumfile);
		errs++;
		return;
	}
	for (i = 0; i < HSHSIZE; i++) {
		hp = hashtab[i];
		while (hp != NULL) {
			fprintf(acctf, "%7.2f\t%s\t%d\n", hp->h_feetpages,
			    hp->h_name, hp->h_count);
			hp = hp->h_link;
		}
	}
	fflush(acctf);
	if (ferror(acctf)) {
		warn("%s", sumfile);
		errs++;
	}
	fclose(acctf);
	if ((acctf = fopen(acctfile, "w")) == NULL)
		warn("%s", acctfile);
	else
		fclose(acctf);
}