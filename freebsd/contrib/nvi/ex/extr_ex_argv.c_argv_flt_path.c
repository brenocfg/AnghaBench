#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; size_t d_namlen; } ;
struct TYPE_9__ {char* bp; size_t len; } ;
struct TYPE_8__ {size_t argc; TYPE_3__** argv; } ;
struct TYPE_7__ {int argsoff; TYPE_3__** args; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EX_PRIVATE ;
typedef  TYPE_2__ EXCMD ;
typedef  int /*<<< orphan*/  DIR ;
typedef  char CHAR_T ;
typedef  int /*<<< orphan*/  ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR2INT (int /*<<< orphan*/ *,char*,size_t,char*,size_t) ; 
 TYPE_1__* EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT2CHAR (int /*<<< orphan*/ *,char*,size_t,char*,size_t) ; 
 char* L (char*) ; 
 int /*<<< orphan*/  MEMCPY (char*,char*,size_t) ; 
 size_t STRLEN (char*) ; 
 char* STRRCHR (char*,char) ; 
 int /*<<< orphan*/  argv_alloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  argv_comp ; 
 int argv_flt_user (int /*<<< orphan*/ *,TYPE_2__*,char*,size_t) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 char* expanduser (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ memcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  qsort (TYPE_3__**,int,int,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 char* v_strdup (int /*<<< orphan*/ *,char*,size_t) ; 
 char* v_wstrdup (int /*<<< orphan*/ *,char*,size_t) ; 

int
argv_flt_path(SCR *sp, EXCMD *excp, CHAR_T *path, size_t plen)
{
	struct dirent *dp;
	DIR *dirp;
	EX_PRIVATE *exp;
	int off;
	size_t dlen, len, nlen;
	CHAR_T *dname;
	CHAR_T *p, *np, *n;
	char *name, *tp, *epd = NULL;
	CHAR_T *wp;
	size_t wlen;

	exp = EXP(sp);

	/* Set up the name and length for comparison. */
	if ((path = v_wstrdup(sp, path, plen)) == NULL)
		return (1);
	if ((p = STRRCHR(path, '/')) == NULL) {
		if (*path == '~') {
			int rc;
			
			/* Filter ~user list instead. */
			rc = argv_flt_user(sp, excp, path, plen);
			free(path);
			return (rc);
		}
		dname = L(".");
		dlen = 0;
		np = path;
	} else {
		if (p == path) {
			dname = L("/");
			dlen = 1;
		} else {
			*p = '\0';
			dname = path;
			dlen = p - path;
		}
		np = p + 1;
	}

	INT2CHAR(sp, dname, dlen + 1, tp, nlen);
	if ((epd = expanduser(tp)) != NULL)
		tp = epd;
	if ((dirp = opendir(tp)) == NULL) {
		free(epd);
		free(path);
		return (1);
	}
	free(epd);

	INT2CHAR(sp, np, STRLEN(np), tp, nlen);
	if ((name = v_strdup(sp, tp, nlen)) == NULL) {
		free(path);
		return (1);
	}

	for (off = exp->argsoff; (dp = readdir(dirp)) != NULL;) {
		if (nlen == 0) {
			if (dp->d_name[0] == '.')
				continue;
			len = dp->d_namlen;
		} else {
			len = dp->d_namlen;
			if (len < nlen || memcmp(dp->d_name, name, nlen))
				continue;
		}

		/* Directory + name + slash + null. */
		CHAR2INT(sp, dp->d_name, len + 1, wp, wlen);
		argv_alloc(sp, dlen + wlen + 1);
		n = exp->args[exp->argsoff]->bp;
		if (dlen != 0) {
			MEMCPY(n, dname, dlen);
			n += dlen;
			if (dlen > 1 || dname[0] != '/')
				*n++ = '/';
			exp->args[exp->argsoff]->len = dlen + 1;
		}
		MEMCPY(n, wp, wlen);
		exp->args[exp->argsoff]->len += wlen - 1;
		++exp->argsoff;
		excp->argv = exp->args;
		excp->argc = exp->argsoff;
	}
	closedir(dirp);
	free(name);
	free(path);

	qsort(exp->args + off, exp->argsoff - off, sizeof(ARGS *), argv_comp);
	return (0);
}