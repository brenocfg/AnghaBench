#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct passwd {int /*<<< orphan*/  pw_name; } ;
struct TYPE_8__ {char* bp; size_t len; } ;
struct TYPE_7__ {size_t argc; TYPE_3__** argv; } ;
struct TYPE_6__ {int argsoff; TYPE_3__** args; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EX_PRIVATE ;
typedef  TYPE_2__ EXCMD ;
typedef  int /*<<< orphan*/  CHAR_T ;
typedef  int /*<<< orphan*/  ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR2INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__* EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT2CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,char*,size_t) ; 
 int /*<<< orphan*/  MEMCPY (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  argv_alloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  argv_comp ; 
 int /*<<< orphan*/  endpwent () ; 
 int /*<<< orphan*/  free (char*) ; 
 struct passwd* getpwent () ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  qsort (TYPE_3__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpwent () ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 char* v_strdup (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static int
argv_flt_user(SCR *sp, EXCMD *excp, CHAR_T *uname, size_t ulen)
{
	EX_PRIVATE *exp;
	struct passwd *pw;
	int off;
	char *np;
	size_t len, nlen;

	exp = EXP(sp);
	off = exp->argsoff;

	/* The input must come with a leading '~'. */
	INT2CHAR(sp, uname + 1, ulen - 1, np, nlen);
	if ((np = v_strdup(sp, np, nlen)) == NULL)
		return (1);

	setpwent();
	while ((pw = getpwent()) != NULL) {
		len = strlen(pw->pw_name);
		if (nlen > 0 &&
		    (nlen > len || memcmp(np, pw->pw_name, nlen)))
			continue;

		/* Copy '~' + the matched user name. */
		CHAR2INT(sp, pw->pw_name, len + 1, uname, ulen);
		argv_alloc(sp, ulen + 1);
		exp->args[exp->argsoff]->bp[0] = '~';
		MEMCPY(exp->args[exp->argsoff]->bp + 1, uname, ulen);
		exp->args[exp->argsoff]->len = ulen;
		++exp->argsoff;
		excp->argv = exp->args;
		excp->argc = exp->argsoff;
	}
	endpwent();
	free(np);

	qsort(exp->args + off, exp->argsoff - off, sizeof(ARGS *), argv_comp);
	return (0);
}