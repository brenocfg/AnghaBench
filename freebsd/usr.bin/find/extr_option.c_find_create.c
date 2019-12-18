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
struct TYPE_4__ {int /*<<< orphan*/ * (* create ) (TYPE_1__*,char***) ;} ;
typedef  int /*<<< orphan*/  PLAN ;
typedef  TYPE_1__ OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 TYPE_1__* lookup_option (char*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,char***) ; 

PLAN *
find_create(char ***argvp)
{
	OPTION *p;
	PLAN *new;
	char **argv;

	argv = *argvp;

	if ((p = lookup_option(*argv)) == NULL)
		errx(1, "%s: unknown primary or operator", *argv);
	++argv;

	new = (p->create)(p, &argv);
	*argvp = argv;
	return (new);
}