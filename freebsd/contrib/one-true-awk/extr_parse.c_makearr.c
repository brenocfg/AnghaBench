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
struct TYPE_9__ {char* sval; int /*<<< orphan*/  tval; int /*<<< orphan*/  nval; } ;
struct TYPE_8__ {scalar_t__* narg; } ;
typedef  TYPE_1__ Node ;
typedef  TYPE_2__ Cell ;

/* Variables and functions */
 int /*<<< orphan*/  ARR ; 
 int /*<<< orphan*/  NSYMTAB ; 
 int /*<<< orphan*/  SYNTAX (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isarr (TYPE_2__*) ; 
 scalar_t__ isfcn (TYPE_2__*) ; 
 scalar_t__ isvalue (TYPE_1__*) ; 
 scalar_t__ makesymtab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (char*) ; 

Node *makearr(Node *p)
{
	Cell *cp;

	if (isvalue(p)) {
		cp = (Cell *) (p->narg[0]);
		if (isfcn(cp))
			SYNTAX( "%s is a function, not an array", cp->nval );
		else if (!isarr(cp)) {
			xfree(cp->sval);
			cp->sval = (char *) makesymtab(NSYMTAB);
			cp->tval = ARR;
		}
	}
	return p;
}