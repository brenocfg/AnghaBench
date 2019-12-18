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
typedef  scalar_t__ uid_t ;
struct passwd {scalar_t__ pw_uid; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {scalar_t__ u_data; } ;
typedef  TYPE_1__ PLAN ;
typedef  TYPE_2__ OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  FTS_NOSTAT ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ find_parsenum (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftsoptions ; 
 struct passwd* getpwnam (char*) ; 
 char* nextarg (TYPE_2__*,char***) ; 
 TYPE_1__* palloc (TYPE_2__*) ; 

PLAN *
c_user(OPTION *option, char ***argvp)
{
	char *username;
	PLAN *new;
	struct passwd *p;
	uid_t uid;

	username = nextarg(option, argvp);
	ftsoptions &= ~FTS_NOSTAT;

	new = palloc(option);
	p = getpwnam(username);
	if (p == NULL) {
		char* cp = username;
		if( username[0] == '-' || username[0] == '+' )
			username++;
		uid = atoi(username);
		if (uid == 0 && username[0] != '0')
			errx(1, "%s: %s: no such user", option->name, username);
		uid = find_parsenum(new, option->name, cp, NULL);
	} else
		uid = p->pw_uid;

	new->u_data = uid;
	return new;
}