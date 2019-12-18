#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct group {scalar_t__ gr_gid; } ;
typedef  scalar_t__ gid_t ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {scalar_t__ g_data; } ;
typedef  TYPE_1__ PLAN ;
typedef  TYPE_2__ OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  FTS_NOSTAT ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ find_parsenum (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftsoptions ; 
 struct group* getgrnam (char*) ; 
 char* nextarg (TYPE_2__*,char***) ; 
 TYPE_1__* palloc (TYPE_2__*) ; 

PLAN *
c_group(OPTION *option, char ***argvp)
{
	char *gname;
	PLAN *new;
	struct group *g;
	gid_t gid;

	gname = nextarg(option, argvp);
	ftsoptions &= ~FTS_NOSTAT;

	new = palloc(option);
	g = getgrnam(gname);
	if (g == NULL) {
		char* cp = gname;
		if (gname[0] == '-' || gname[0] == '+')
			gname++;
		gid = atoi(gname);
		if (gid == 0 && gname[0] != '0')
			errx(1, "%s: %s: no such group", option->name, gname);
		gid = find_parsenum(new, option->name, cp, NULL);
	} else
		gid = g->gr_gid;

	new->g_data = gid;
	return new;
}