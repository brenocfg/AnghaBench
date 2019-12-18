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
typedef  int /*<<< orphan*/  regex_t ;
struct TYPE_9__ {int flags; } ;
struct TYPE_8__ {int /*<<< orphan*/ * re_data; } ;
typedef  TYPE_1__ PLAN ;
typedef  TYPE_2__ OPTION ;

/* Variables and functions */
 int F_IGNCASE ; 
 int LINE_MAX ; 
 int REG_ICASE ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 char* nextarg (TYPE_2__*,char***) ; 
 TYPE_1__* palloc (TYPE_2__*) ; 
 int regcomp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int regexp_flags ; 

PLAN *
c_regex(OPTION *option, char ***argvp)
{
	PLAN *new;
	char *pattern;
	regex_t *pre;
	int errcode;
	char errbuf[LINE_MAX];

	if ((pre = malloc(sizeof(regex_t))) == NULL)
		err(1, NULL);

	pattern = nextarg(option, argvp);

	if ((errcode = regcomp(pre, pattern,
	    regexp_flags | (option->flags & F_IGNCASE ? REG_ICASE : 0))) != 0) {
		regerror(errcode, pre, errbuf, sizeof errbuf);
		errx(1, "%s: %s: %s",
		     option->flags & F_IGNCASE ? "-iregex" : "-regex",
		     pattern, errbuf);
	}

	new = palloc(option);
	new->re_data = pre;

	return new;
}