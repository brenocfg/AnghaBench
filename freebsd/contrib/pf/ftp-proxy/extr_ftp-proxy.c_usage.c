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
 char* __progname ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
usage(void)
{
	fprintf(stderr, "usage: %s [-6Adrv] [-a address] [-b address]"
	    " [-D level] [-m maxsessions]\n                 [-P port]"
	    " [-p port] [-q queue] [-R address] [-T tag]\n"
            "                 [-t timeout]\n", __progname);
	exit(1);
}