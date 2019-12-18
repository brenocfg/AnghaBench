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
 int /*<<< orphan*/  xo_error (char*,char*,char*,char*) ; 

__attribute__((used)) static void
usage(void)
{
	xo_error("%s\n%s\n%s\n",
	    "usage: savecore -c [-v] [device ...]",
	    "       savecore -C [-v] [device ...]",
	    "       savecore [-fkvz] [-m maxdumps] [directory [device ...]]");
	exit(1);
}