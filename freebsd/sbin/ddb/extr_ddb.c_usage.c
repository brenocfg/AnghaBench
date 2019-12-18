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
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
usage(void)
{

	fprintf(stderr, "usage: ddb capture [-M core] [-N system] print\n");
	fprintf(stderr, "       ddb capture [-M core] [-N system] status\n");
	fprintf(stderr, "       ddb script scriptname\n");
	fprintf(stderr, "       ddb script scriptname=script\n");
	fprintf(stderr, "       ddb scripts\n");
	fprintf(stderr, "       ddb unscript scriptname\n");
	fprintf(stderr, "       ddb pathname\n");
	exit(EX_USAGE);
}