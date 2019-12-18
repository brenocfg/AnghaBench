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
 int /*<<< orphan*/  X_STARTUP ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr,
		"usage: dump [-0123456789acLnSu] [-B records] [-b blocksize] [-C cachesize]\n"
		"            [-D dumpdates] [-d density] [-f file | -P pipecommand] [-h level]\n"
		"            [-s feet] [-T date] filesystem\n"
		"       dump -W | -w\n");
	exit(X_STARTUP);
}