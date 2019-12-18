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
typedef  int /*<<< orphan*/  u_char ;
struct glob_lim {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {scalar_t__ gl_pathc; scalar_t__ gl_offs; int gl_flags; int (* gl_errfunc ) (char const*,int) ;scalar_t__ gl_matchc; int /*<<< orphan*/ * gl_statv; int /*<<< orphan*/ * gl_pathv; } ;
typedef  TYPE_1__ glob_t ;
typedef  int Char ;

/* Variables and functions */
 int EOS ; 
 int GLOB_APPEND ; 
 int GLOB_BRACE ; 
 int GLOB_DOOFFS ; 
 int GLOB_MAGCHAR ; 
 int GLOB_NOESCAPE ; 
 int GLOB_NOMATCH ; 
 int GLOB_NOSPACE ; 
 scalar_t__ INT_MAX ; 
 int MAXPATHLEN ; 
 int M_PROTECT ; 
 scalar_t__ PATH_MAX ; 
 int QUOTE ; 
 int glob0 (int*,TYPE_1__*,struct glob_lim*) ; 
 int globexp1 (int*,TYPE_1__*,struct glob_lim*) ; 
 scalar_t__ strnlen (char const*,scalar_t__) ; 

int
glob(const char *pattern, int flags, int (*errfunc)(const char *, int),
    glob_t *pglob)
{
	const u_char *patnext;
	int c;
	Char *bufnext, *bufend, patbuf[MAXPATHLEN];
	struct glob_lim limit = { 0, 0, 0 };

	if (strnlen(pattern, PATH_MAX) == PATH_MAX)
		return(GLOB_NOMATCH);

	patnext = (u_char *) pattern;
	if (!(flags & GLOB_APPEND)) {
		pglob->gl_pathc = 0;
		pglob->gl_pathv = NULL;
		pglob->gl_statv = NULL;
		if (!(flags & GLOB_DOOFFS))
			pglob->gl_offs = 0;
	}
	pglob->gl_flags = flags & ~GLOB_MAGCHAR;
	pglob->gl_errfunc = errfunc;
	pglob->gl_matchc = 0;

	if (pglob->gl_offs < 0 || pglob->gl_pathc < 0 ||
	    pglob->gl_offs >= INT_MAX || pglob->gl_pathc >= INT_MAX ||
	    pglob->gl_pathc >= INT_MAX - pglob->gl_offs - 1)
		return GLOB_NOSPACE;

	bufnext = patbuf;
	bufend = bufnext + MAXPATHLEN - 1;
	if (flags & GLOB_NOESCAPE)
		while (bufnext < bufend && (c = *patnext++) != EOS)
			*bufnext++ = c;
	else {
		/* Protect the quoted characters. */
		while (bufnext < bufend && (c = *patnext++) != EOS)
			if (c == QUOTE) {
				if ((c = *patnext++) == EOS) {
					c = QUOTE;
					--patnext;
				}
				*bufnext++ = c | M_PROTECT;
			} else
				*bufnext++ = c;
	}
	*bufnext = EOS;

	if (flags & GLOB_BRACE)
		return globexp1(patbuf, pglob, &limit);
	else
		return glob0(patbuf, pglob, &limit);
}