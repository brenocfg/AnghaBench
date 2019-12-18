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
struct stat {int /*<<< orphan*/  st_ino; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_data; } ;
typedef  TYPE_1__ PLAN ;
typedef  int /*<<< orphan*/  OPTION ;

/* Variables and functions */
 int FTS_NOSTAT ; 
 int FTS_PHYSICAL ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int ftsoptions ; 
 int lstat (char*,struct stat*) ; 
 char* nextarg (int /*<<< orphan*/ *,char***) ; 
 TYPE_1__* palloc (int /*<<< orphan*/ *) ; 
 int stat (char*,struct stat*) ; 

PLAN *
c_samefile(OPTION *option, char ***argvp)
{
	char *fn;
	PLAN *new;
	struct stat sb;
	int error;

	fn = nextarg(option, argvp);
	ftsoptions &= ~FTS_NOSTAT;

	new = palloc(option);
	if (ftsoptions & FTS_PHYSICAL)
		error = lstat(fn, &sb);
	else
		error = stat(fn, &sb);
	if (error != 0)
		err(1, "%s", fn);
	new->i_data = sb.st_ino;
	return new;
}