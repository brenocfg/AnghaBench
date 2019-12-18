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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 scalar_t__ ischown ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	if (ischown)
		(void)fprintf(stderr, "%s\n%s\n",
		    "usage: chown [-fhvx] [-R [-H | -L | -P]] owner[:group]"
		    " file ...",
		    "       chown [-fhvx] [-R [-H | -L | -P]] :group file ...");
	else
		(void)fprintf(stderr, "%s\n",
		    "usage: chgrp [-fhvx] [-R [-H | -L | -P]] group file ...");
	exit(1);
}