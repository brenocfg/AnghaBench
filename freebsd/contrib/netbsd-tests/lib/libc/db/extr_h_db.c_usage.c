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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	(void)fprintf(stderr,
#ifdef __NetBSD__
	    "Usage: %s [-lu] [-f file] [-i info] [-o file] [-O file] "
#else
	    "Usage: %s [-l] [-f file] [-i info] [-o file] "
#endif
		"type script\n", getprogname());
	exit(1);
}