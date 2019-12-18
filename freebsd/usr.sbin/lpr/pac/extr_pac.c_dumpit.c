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
struct hent {int h_count; float h_feetpages; char* h_name; struct hent* h_link; } ;

/* Variables and functions */
 scalar_t__ allflag ; 
 scalar_t__ calloc (int,size_t) ; 
 struct hent** hashtab ; 
 size_t hcount ; 
 double price ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  qsort (struct hent**,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qucmp ; 

__attribute__((used)) static void
dumpit(void)
{
	struct hent **base;
	register struct hent *hp, **ap;
	register int hno, runs;
	size_t c;
	float feet;

	hp = hashtab[0];
	hno = 1;
	base = (struct hent **) calloc(sizeof hp, hcount);
	for (ap = base, c = hcount; c--; ap++) {
		while (hp == NULL)
			hp = hashtab[hno++];
		*ap = hp;
		hp = hp->h_link;
	}
	qsort(base, hcount, sizeof hp, qucmp);
	printf("  Login               pages/feet   runs    price\n");
	feet = 0.0;
	runs = 0;
	for (ap = base, c = hcount; c--; ap++) {
		hp = *ap;
		runs += hp->h_count;
		feet += hp->h_feetpages;
		printf("%-24s %7.2f %4d   $%6.2f\n", hp->h_name,
		    hp->h_feetpages, hp->h_count, hp->h_feetpages * price);
	}
	if (allflag) {
		printf("\n");
		printf("%-24s %7.2f %4d   $%6.2f\n", "total", feet,
		    runs, feet * price);
	}
}