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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
openfile(
	const char *name,
	int mode
	)
{
	int ifd;

	ifd = open(name, mode);
	if (ifd < 0)
	{
		(void) fprintf(stderr, "%s: open %s: ", progname, name);
		perror("");
		exit(1);
	}
	return ifd;
}