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
struct direct {scalar_t__ d_ino; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 scalar_t__ TSTINO (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumpmap ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 struct direct* pathsearch (char const*) ; 
 int /*<<< orphan*/  stderr ; 

ino_t
dirlookup(const char *name)
{
	struct direct *dp;
	ino_t ino;

	ino = ((dp = pathsearch(name)) == NULL) ? 0 : dp->d_ino;

	if (ino == 0 || TSTINO(ino, dumpmap) == 0)
		fprintf(stderr, "%s is not on the tape\n", name);
	return (ino);
}