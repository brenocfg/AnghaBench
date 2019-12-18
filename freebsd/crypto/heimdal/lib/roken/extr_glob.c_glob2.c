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
struct TYPE_7__ {int gl_flags; int /*<<< orphan*/  gl_matchc; } ;
typedef  TYPE_1__ glob_t ;
typedef  scalar_t__ Char ;

/* Variables and functions */
 scalar_t__ CHAR_EOS ; 
 scalar_t__ CHAR_SEP ; 
 int GLOB_MARK ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ g_lstat (scalar_t__*,struct stat*,TYPE_1__*) ; 
 scalar_t__ g_stat (scalar_t__*,struct stat*,TYPE_1__*) ; 
 int glob3 (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,TYPE_1__*,size_t*) ; 
 int globextend (scalar_t__*,TYPE_1__*,size_t*) ; 
 scalar_t__ ismeta (scalar_t__) ; 

__attribute__((used)) static int
glob2(Char *pathbuf, Char *pathend, Char *pattern, glob_t *pglob,
      size_t *limit)
{
	struct stat sb;
	Char *p, *q;
	int anymeta;

	/*
	 * Loop over pattern segments until end of pattern or until
	 * segment with meta character found.
	 */
	for (anymeta = 0;;) {
		if (*pattern == CHAR_EOS) {		/* End of pattern? */
			*pathend = CHAR_EOS;
			if (g_lstat(pathbuf, &sb, pglob))
				return(0);

			if (((pglob->gl_flags & GLOB_MARK) &&
			    pathend[-1] != CHAR_SEP) && (S_ISDIR(sb.st_mode)
			    || (S_ISLNK(sb.st_mode) &&
			    (g_stat(pathbuf, &sb, pglob) == 0) &&
			    S_ISDIR(sb.st_mode)))) {
				*pathend++ = CHAR_SEP;
				*pathend = CHAR_EOS;
			}
			++pglob->gl_matchc;
			return(globextend(pathbuf, pglob, limit));
		}

		/* Find end of next segment, copy tentatively to pathend. */
		q = pathend;
		p = pattern;
		while (*p != CHAR_EOS && *p != CHAR_SEP) {
			if (ismeta(*p))
				anymeta = 1;
			*q++ = *p++;
		}

		if (!anymeta) {		/* No expansion, do next segment. */
			pathend = q;
			pattern = p;
			while (*pattern == CHAR_SEP)
				*pathend++ = *pattern++;
		} else			/* Need expansion, recurse. */
			return(glob3(pathbuf, pathend, pattern, p, pglob,
			    limit));
	}
	/* NOTREACHED */
}