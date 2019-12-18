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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(const char* cmd)
{
	fprintf(stderr, "%s: daemon for UFS file system freeze/thaw\n"
	    " -d : enable debug log printing. Default is disabled.\n"
	    " -n : run as a regular process instead of a daemon. Default is a daemon.\n"
	    " -h : print usage.\n", cmd);
	exit(1);
}