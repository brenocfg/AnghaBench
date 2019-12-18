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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
usage(void)
{
	(void) fprintf(stderr,
	    "usage: scp [-346BCpqrTv] [-c cipher] [-F ssh_config] [-i identity_file]\n"
	    "           [-l limit] [-o ssh_option] [-P port] [-S program] source ... target\n");
	exit(1);
}