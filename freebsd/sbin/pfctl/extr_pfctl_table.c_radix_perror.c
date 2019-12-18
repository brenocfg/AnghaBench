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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* pfr_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
radix_perror(void)
{
	extern char *__progname;
	fprintf(stderr, "%s: %s.\n", __progname, pfr_strerror(errno));
}