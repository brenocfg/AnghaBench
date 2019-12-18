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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ isgroups ; 
 scalar_t__ iswhoami ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	if (isgroups)
		(void)fprintf(stderr, "usage: groups [user]\n");
	else if (iswhoami)
		(void)fprintf(stderr, "usage: whoami\n");
	else
		(void)fprintf(stderr, "%s\n%s%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
		    "usage: id [user]",
#ifdef USE_BSM_AUDIT
		    "       id -A\n",
#else
		    "",
#endif
		    "       id -G [-n] [user]",
		    "       id -M",
		    "       id -P [user]",
		    "       id -c",
		    "       id -g [-nr] [user]",
		    "       id -p [user]",
		    "       id -u [-nr] [user]");
	exit(1);
}