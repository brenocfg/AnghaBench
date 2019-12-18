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
 char* lafe_getprogname () ; 
 int /*<<< orphan*/  stderr ; 

void
usage(void)
{
	const char	*p;

	p = lafe_getprogname();

	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "  List:    %s -tf <archive-filename>\n", p);
	fprintf(stderr, "  Extract: %s -xf <archive-filename>\n", p);
	fprintf(stderr, "  Create:  %s -cf <archive-filename> [filenames...]\n", p);
	fprintf(stderr, "  Help:    %s --help\n", p);
	exit(1);
}