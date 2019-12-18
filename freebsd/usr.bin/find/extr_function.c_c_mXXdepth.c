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
struct TYPE_5__ {int flags; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  PLAN ;
typedef  TYPE_1__ OPTION ;

/* Variables and functions */
 int F_MAXDEPTH ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,char*) ; 
 void* find_parsenum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 void* maxdepth ; 
 void* mindepth ; 
 char* nextarg (TYPE_1__*,char***) ; 
 int /*<<< orphan*/ * palloc (TYPE_1__*) ; 

PLAN *
c_mXXdepth(OPTION *option, char ***argvp)
{
	char *dstr;
	PLAN *new;

	dstr = nextarg(option, argvp);
	if (dstr[0] == '-')
		/* all other errors handled by find_parsenum() */
		errx(1, "%s: %s: value must be positive", option->name, dstr);

	new = palloc(option);
	if (option->flags & F_MAXDEPTH)
		maxdepth = find_parsenum(new, option->name, dstr, NULL);
	else
		mindepth = find_parsenum(new, option->name, dstr, NULL);
	return new;
}