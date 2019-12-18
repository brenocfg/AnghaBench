#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ prog_t ;

/* Variables and functions */
 int /*<<< orphan*/  fillin_program (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  gen_output_cfile () ; 
 int /*<<< orphan*/  gen_output_makefile () ; 
 int /*<<< orphan*/  gen_specials_cache () ; 
 char* outmkname ; 
 char* path_make ; 
 TYPE_1__* progs ; 
 int /*<<< orphan*/  remove_error_progs () ; 
 int /*<<< orphan*/  status (char*) ; 
 int /*<<< orphan*/  stderr ; 

void
gen_outputs(void)
{
	prog_t *p;

	for (p = progs; p != NULL; p = p->next)
		fillin_program(p);

	remove_error_progs();
	gen_specials_cache();
	gen_output_cfile();
	gen_output_makefile();
	status("");
	fprintf(stderr,
	    "Run \"%s -f %s\" to build crunched binary.\n",
	    path_make, outmkname);
}