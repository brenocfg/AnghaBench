#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct glob_limit {scalar_t__ l_path_lim; scalar_t__ l_string_cnt; } ;
struct TYPE_3__ {int gl_flags; scalar_t__ gl_matchc; int gl_pathc; int gl_offs; char** gl_pathv; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 scalar_t__ EOS ; 
 int GLOB_LIMIT ; 
 scalar_t__ GLOB_LIMIT_STRING ; 
 int GLOB_NOSPACE ; 
 size_t MB_CUR_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ g_Ctoc (int /*<<< orphan*/  const*,char*,size_t) ; 
 char* malloc (size_t) ; 
 char** reallocarray (char**,size_t,int) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
globextend(const Char *path, glob_t *pglob, struct glob_limit *limit,
    const char *origpat)
{
	char **pathv;
	size_t i, newn, len;
	char *copy;
	const Char *p;

	if ((pglob->gl_flags & GLOB_LIMIT) &&
	    pglob->gl_matchc > limit->l_path_lim) {
		errno = E2BIG;
		return (GLOB_NOSPACE);
	}

	newn = 2 + pglob->gl_pathc + pglob->gl_offs;
	/* reallocarray(NULL, newn, size) is equivalent to malloc(newn*size). */
	pathv = reallocarray(pglob->gl_pathv, newn, sizeof(*pathv));
	if (pathv == NULL)
		return (GLOB_NOSPACE);

	if (pglob->gl_pathv == NULL && pglob->gl_offs > 0) {
		/* first time around -- clear initial gl_offs items */
		pathv += pglob->gl_offs;
		for (i = pglob->gl_offs + 1; --i > 0; )
			*--pathv = NULL;
	}
	pglob->gl_pathv = pathv;

	if (origpat != NULL)
		copy = strdup(origpat);
	else {
		for (p = path; *p++ != EOS;)
			continue;
		len = MB_CUR_MAX * (size_t)(p - path); /* XXX overallocation */
		if ((copy = malloc(len)) != NULL) {
			if (g_Ctoc(path, copy, len)) {
				free(copy);
				errno = E2BIG;
				return (GLOB_NOSPACE);
			}
		}
	}
	if (copy != NULL) {
		limit->l_string_cnt += strlen(copy) + 1;
		if ((pglob->gl_flags & GLOB_LIMIT) &&
		    limit->l_string_cnt >= GLOB_LIMIT_STRING) {
			free(copy);
			errno = E2BIG;
			return (GLOB_NOSPACE);
		}
		pathv[pglob->gl_offs + pglob->gl_pathc++] = copy;
	}
	pathv[pglob->gl_offs + pglob->gl_pathc] = NULL;
	return (copy == NULL ? GLOB_NOSPACE : 0);
}