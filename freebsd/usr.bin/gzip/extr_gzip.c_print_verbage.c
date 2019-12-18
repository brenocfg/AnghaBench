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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_ratio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
print_verbage(const char *file, const char *nfile, off_t usize, off_t gsize)
{
	if (file)
		fprintf(stderr, "%s:%s  ", file,
		    strlen(file) < 7 ? "\t\t" : "\t");
	print_ratio(usize, gsize, stderr);
	if (nfile)
		fprintf(stderr, " -- replaced with %s", nfile);
	fprintf(stderr, "\n");
	fflush(stderr);
}