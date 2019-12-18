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
struct getentdb {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RV_USAGE ; 
 struct getentdb* databases ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
usage(void)
{
	struct getentdb	*curdb;

	fprintf(stderr, "Usage: %s database [key ...]\n",
	    getprogname());
	fprintf(stderr, "       database may be one of:\n\t");
	for (curdb = databases; curdb->name != NULL; curdb++) {
		fprintf(stderr, " %s", curdb->name);
	}
	fprintf(stderr, "\n");
	exit(RV_USAGE);
	/* NOTREACHED */
}