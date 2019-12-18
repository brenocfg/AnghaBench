#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ goterror; int /*<<< orphan*/ * buildopts; int /*<<< orphan*/ * keeplist; int /*<<< orphan*/ * objs; int /*<<< orphan*/ * libs_so; int /*<<< orphan*/ * libs; int /*<<< orphan*/ * links; int /*<<< orphan*/ * objdir; int /*<<< orphan*/ * realsrcdir; int /*<<< orphan*/ * srcdir; int /*<<< orphan*/ * ident; struct TYPE_5__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ prog_t ;

/* Variables and functions */
 scalar_t__ list_mode ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_of_memory () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 TYPE_1__* progs ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

void
add_prog(char *progname)
{
	prog_t *p1, *p2;

	/* add to end, but be smart about dups */

	for (p1 = NULL, p2 = progs; p2 != NULL; p1 = p2, p2 = p2->next)
		if (!strcmp(p2->name, progname))
			return;

	p2 = malloc(sizeof(prog_t));
	if(p2) {
		memset(p2, 0, sizeof(prog_t));
		p2->name = strdup(progname);
	}
	if (!p2 || !p2->name)
		out_of_memory();

	p2->next = NULL;
	if (p1 == NULL)
		progs = p2;
	else
		p1->next = p2;

	p2->ident = NULL;
	p2->srcdir = NULL;
	p2->realsrcdir = NULL;
	p2->objdir = NULL;
	p2->links = NULL;
	p2->libs = NULL;
	p2->libs_so = NULL;
	p2->objs = NULL;
	p2->keeplist = NULL;
	p2->buildopts = NULL;
	p2->goterror = 0;

	if (list_mode)
		printf("%s\n",progname);
}