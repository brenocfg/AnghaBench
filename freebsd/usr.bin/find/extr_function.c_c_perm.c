#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  m_data; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ PLAN ;
typedef  TYPE_2__ OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  FTS_NOSTAT ; 
 int /*<<< orphan*/  F_ANY ; 
 int /*<<< orphan*/  F_ATLEAST ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftsoptions ; 
 int /*<<< orphan*/  getmode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* nextarg (TYPE_2__*,char***) ; 
 TYPE_1__* palloc (TYPE_2__*) ; 
 int /*<<< orphan*/ * setmode (char*) ; 

PLAN *
c_perm(OPTION *option, char ***argvp)
{
	char *perm;
	PLAN *new;
	mode_t *set;

	perm = nextarg(option, argvp);
	ftsoptions &= ~FTS_NOSTAT;

	new = palloc(option);

	if (*perm == '-') {
		new->flags |= F_ATLEAST;
		++perm;
	} else if (*perm == '+') {
		new->flags |= F_ANY;
		++perm;
	}

	if ((set = setmode(perm)) == NULL)
		errx(1, "%s: %s: illegal mode string", option->name, perm);

	new->m_data = getmode(set, 0);
	free(set);
	return new;
}