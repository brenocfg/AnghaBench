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
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	(void)fprintf(stderr,
"usage: install [-bCcpSsUv] [-f flags] [-g group] [-m mode] [-o owner]\n"
"               [-M log] [-D dest] [-h hash] [-T tags]\n"
"               [-B suffix] [-l linkflags] [-N dbdir]\n"
"               file1 file2\n"
"       install [-bCcpSsUv] [-f flags] [-g group] [-m mode] [-o owner]\n"
"               [-M log] [-D dest] [-h hash] [-T tags]\n"
"               [-B suffix] [-l linkflags] [-N dbdir]\n"
"               file1 ... fileN directory\n"
"       install -dU [-vU] [-g group] [-m mode] [-N dbdir] [-o owner]\n"
"               [-M log] [-D dest] [-h hash] [-T tags]\n"
"               directory ...\n");
	exit(EX_USAGE);
	/* NOTREACHED */
}