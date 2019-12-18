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
struct TYPE_4__ {scalar_t__ recursed; void* www; int /*<<< orphan*/  n_rdep; void* rdep; int /*<<< orphan*/  n_bdep; void* bdep; int /*<<< orphan*/  n_fdep; void* fdep; int /*<<< orphan*/  n_pdep; void* pdep; int /*<<< orphan*/  n_edep; void* edep; void* categories; void* maintainer; void* pkgdescr; void* comment; void* prefix; void* portdir; void* pkgname; } ;
typedef  TYPE_1__ PORT ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 void* makelist (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 
 void* strdup2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strsep (char**,char*) ; 

__attribute__((used)) static PORT *
portify(char * line)
{
	PORT * p;
	size_t i, n;

	/* Verify that line has the right number of fields */
	for (n = i = 0; line[i] != 0; i++)
		if (line[i] == '|')
			n++;
	if (n != 12)
		errx(1, "Port describe line is corrupt:\n%s\n", line);

	p = malloc(sizeof(PORT));
	if (p == NULL)
		err(1, "malloc(PORT)");

	p->pkgname = strdup2(strsep(&line, "|"));
	p->portdir = strdup2(strsep(&line, "|"));
	p->prefix = strdup2(strsep(&line, "|"));
	p->comment = strdup2(strsep(&line, "|"));
	p->pkgdescr = strdup2(strsep(&line, "|"));
	p->maintainer = strdup2(strsep(&line, "|"));
	p->categories = strdup2(strsep(&line, "|"));
	p->edep = makelist(strsep(&line, "|"), &p->n_edep);
	p->pdep = makelist(strsep(&line, "|"), &p->n_pdep);
	p->fdep = makelist(strsep(&line, "|"), &p->n_fdep);
	p->bdep = makelist(strsep(&line, "|"), &p->n_bdep);
	p->rdep = makelist(strsep(&line, "|"), &p->n_rdep);
	p->www = strdup2(strsep(&line, "|"));

	p->recursed = 0;

	/*
	 * line will now be equal to NULL -- we counted the field
	 * separators at the top of the function.
	 */

	return p;
}