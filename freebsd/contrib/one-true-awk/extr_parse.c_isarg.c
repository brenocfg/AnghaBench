#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nval; } ;
struct TYPE_3__ {scalar_t__* narg; struct TYPE_3__* nnext; } ;
typedef  TYPE_1__ Node ;
typedef  TYPE_2__ Cell ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int isarg(const char *s)		/* is s in argument list for current function? */
{			/* return -1 if not, otherwise arg # */
	extern Node *arglist;
	Node *p = arglist;
	int n;

	for (n = 0; p != NULL; p = p->nnext, n++)
		if (strcmp(((Cell *)(p->narg[0]))->nval, s) == 0)
			return n;
	return -1;
}