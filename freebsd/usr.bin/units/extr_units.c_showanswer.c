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
struct unittype {scalar_t__ offset; int factor; scalar_t__ quantity; } ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,char*,...) ; 
 scalar_t__ compareunits (struct unittype*,struct unittype*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* havestr ; 
 char* outputformat ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  showunit (struct unittype*) ; 
 scalar_t__ terse ; 
 scalar_t__ verbose ; 
 char* wantstr ; 

__attribute__((used)) static void 
showanswer(struct unittype * have, struct unittype * want)
{
	double ans;
	char* oformat;

	if (compareunits(have, want)) {
		printf("conformability error\n");
		if (verbose)
			printf("\t%s = ", havestr);
		else if (!terse)
			printf("\t");
		showunit(have);
		if (!terse) {
			if (verbose)
				printf("\t%s = ", wantstr);
			else
				printf("\t");
			showunit(want);
		}
	}
	else if (have->offset != want->offset) {
		if (want->quantity)
			printf("WARNING: conversion of non-proportional quantities.\n");
		if (have->quantity) {
			asprintf(&oformat, "\t%s\n", outputformat);
			printf(oformat,
			    (have->factor + have->offset-want->offset)/want->factor);
			free(oformat);
		}
		else {
			asprintf(&oformat, "\t (-> x*%sg %sg)\n\t (<- y*%sg %sg)\n",
			    outputformat, outputformat, outputformat, outputformat);
			printf(oformat,
			    have->factor / want->factor,
			    (have->offset-want->offset)/want->factor,
			    want->factor / have->factor,
			    (want->offset - have->offset)/have->factor);
		}
	}
	else {
		ans = have->factor / want->factor;

		if (verbose) {
			printf("\t%s = ", havestr);
			printf(outputformat, ans);
			printf(" * %s", wantstr);
			printf("\n");
		}
		else if (terse) {
			printf(outputformat, ans);
			printf("\n");
		}
		else {
			printf("\t* ");
			printf(outputformat, ans);
			printf("\n");
		}

		if (verbose) {
			printf("\t%s = (1 / ", havestr);
			printf(outputformat, 1/ans);
			printf(") * %s\n", wantstr);
		}
		else if (!terse) {
			printf("\t/ ");
			printf(outputformat, 1/ans);
			printf("\n");
		}
	}
}