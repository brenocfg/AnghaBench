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

__attribute__((used)) static void
usage(void)
{

	fprintf(stderr,
"usage: mdconfig -a -t type [-n] [-o [no]option] ... [-f file]\n"
"                [-s size] [-S sectorsize] [-u unit] [-L label]\n"
"                [-x sectors/track] [-y heads/cylinder]\n"
"       mdconfig -d -u unit [-o [no]force]\n"
"       mdconfig -r -u unit -s size [-o [no]force]\n"
"       mdconfig -l [-v] [-n] [-f file] [-u unit]\n"
"       mdconfig file\n");
	fprintf(stderr, "\t\ttype = {malloc, vnode, swap}\n");
	fprintf(stderr, "\t\toption = {cache, cluster, compress, force,\n");
	fprintf(stderr, "\t\t          readonly, reserve, ro, verify}\n");
	fprintf(stderr, "\t\tsize = %%d (512 byte blocks), %%db (B),\n");
	fprintf(stderr, "\t\t       %%dk (kB), %%dm (MB), %%dg (GB), \n");
	fprintf(stderr, "\t\t       %%dt (TB), or %%dp (PB)\n");
	exit(1);
}