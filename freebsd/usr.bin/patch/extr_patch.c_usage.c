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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  my_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr,
"usage: patch [-bCcEeflNnRstuv] [-B backup-prefix] [-D symbol] [-d directory]\n"
"             [-F max-fuzz] [-i patchfile] [-o out-file] [-p strip-count]\n"
"             [-r rej-name] [-V t | nil | never | none] [-x number]\n"
"             [-z backup-ext] [--posix] [origfile [patchfile]]\n"
"       patch <patchfile\n");
	my_exit(EXIT_FAILURE);
}