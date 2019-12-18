#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct glob_limit {int /*<<< orphan*/  l_stat_cnt; } ;
struct TYPE_7__ {int gl_flags; int /*<<< orphan*/  gl_matchc; } ;
typedef  TYPE_1__ glob_t ;
typedef  scalar_t__ Char ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 scalar_t__ EOS ; 
 int GLOB_LIMIT ; 
 scalar_t__ GLOB_LIMIT_STAT ; 
 int GLOB_MARK ; 
 int GLOB_NOSPACE ; 
 scalar_t__ SEP ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ UNPROT (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ g_lstat (scalar_t__*,struct stat*,TYPE_1__*) ; 
 scalar_t__ g_stat (scalar_t__*,struct stat*,TYPE_1__*) ; 
 int glob3 (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,TYPE_1__*,struct glob_limit*) ; 
 int globextend (scalar_t__*,TYPE_1__*,struct glob_limit*,int /*<<< orphan*/ *) ; 
 scalar_t__ ismeta (scalar_t__) ; 

__attribute__((used)) static int
glob2(Char *pathbuf, Char *pathend, Char *pathend_last, Char *pattern,
      glob_t *pglob, struct glob_limit *limit)
{
	struct stat sb;
	Char *p, *q;
	int anymeta;

	/*
	 * Loop over pattern segments until end of pattern or until
	 * segment with meta character found.
	 */
	for (anymeta = 0;;) {
		if (*pattern == EOS) {		/* End of pattern? */
			*pathend = EOS;
			if (g_lstat(pathbuf, &sb, pglob))
				return (0);

			if ((pglob->gl_flags & GLOB_LIMIT) &&
			    limit->l_stat_cnt++ >= GLOB_LIMIT_STAT) {
				errno = E2BIG;
				return (GLOB_NOSPACE);
			}
			if ((pglob->gl_flags & GLOB_MARK) &&
			    UNPROT(pathend[-1]) != SEP &&
			    (S_ISDIR(sb.st_mode) ||
			    (S_ISLNK(sb.st_mode) &&
			    g_stat(pathbuf, &sb, pglob) == 0 &&
			    S_ISDIR(sb.st_mode)))) {
				if (pathend + 1 > pathend_last) {
					errno = E2BIG;
					return (GLOB_NOSPACE);
				}
				*pathend++ = SEP;
				*pathend = EOS;
			}
			++pglob->gl_matchc;
			return (globextend(pathbuf, pglob, limit, NULL));
		}

		/* Find end of next segment, copy tentatively to pathend. */
		q = pathend;
		p = pattern;
		while (*p != EOS && UNPROT(*p) != SEP) {
			if (ismeta(*p))
				anymeta = 1;
			if (q + 1 > pathend_last) {
				errno = E2BIG;
				return (GLOB_NOSPACE);
			}
			*q++ = *p++;
		}

		if (!anymeta) {		/* No expansion, do next segment. */
			pathend = q;
			pattern = p;
			while (UNPROT(*pattern) == SEP) {
				if (pathend + 1 > pathend_last) {
					errno = E2BIG;
					return (GLOB_NOSPACE);
				}
				*pathend++ = *pattern++;
			}
		} else			/* Need expansion, recurse. */
			return (glob3(pathbuf, pathend, pathend_last, pattern,
			    p, pglob, limit));
	}
	/* NOTREACHED */
}