#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_12__ {int flags; TYPE_1__ t_data; } ;
typedef  TYPE_2__ PLAN ;
typedef  TYPE_3__ OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  FTS_NOSTAT ; 
 int F_EXACTTIME ; 
 int /*<<< orphan*/  TIME_CORRECT (TYPE_2__*) ; 
 int /*<<< orphan*/  find_parsetime (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ftsoptions ; 
 char* nextarg (TYPE_3__*,char***) ; 
 TYPE_2__* palloc (TYPE_3__*) ; 

PLAN *
c_Xtime(OPTION *option, char ***argvp)
{
	char *value;
	PLAN *new;

	value = nextarg(option, argvp);
	ftsoptions &= ~FTS_NOSTAT;

	new = palloc(option);
	new->t_data.tv_sec = find_parsetime(new, option->name, value);
	new->t_data.tv_nsec = 0;
	if (!(new->flags & F_EXACTTIME))
		TIME_CORRECT(new);
	return new;
}