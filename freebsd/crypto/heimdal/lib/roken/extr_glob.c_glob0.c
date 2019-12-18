#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int gl_pathc; int gl_flags; scalar_t__ gl_offs; scalar_t__ gl_pathv; } ;
typedef  TYPE_1__ glob_t ;
typedef  int Char ;

/* Variables and functions */
 void* CHAR (int) ; 
 int CHAR_EOS ; 
#define  CHAR_LBRACKET 130 
 int CHAR_NOT ; 
#define  CHAR_QUESTION 129 
 int const CHAR_RANGE ; 
 int CHAR_RBRACKET ; 
#define  CHAR_STAR 128 
 int GLOB_MAGCHAR ; 
 int GLOB_NOCHECK ; 
 int GLOB_NOMAGIC ; 
 int GLOB_NOSORT ; 
 int M_ALL ; 
 int /*<<< orphan*/  M_END ; 
 int /*<<< orphan*/  M_NOT ; 
 int /*<<< orphan*/  M_ONE ; 
 int /*<<< orphan*/  M_RNG ; 
 int /*<<< orphan*/  M_SET ; 
 int /*<<< orphan*/  MaxPathLen ; 
 int /*<<< orphan*/  compare ; 
 int /*<<< orphan*/ * g_strchr (int const*,int) ; 
 int glob1 (int*,TYPE_1__*,size_t*) ; 
 int globextend (int const*,TYPE_1__*,size_t*) ; 
 int* globtilde (int const*,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  qprintf (char*,int*) ; 
 int /*<<< orphan*/  qsort (scalar_t__,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
glob0(const Char *pattern, glob_t *pglob)
{
	const Char *qpatnext;
	int c, err, oldpathc;
	Char *bufnext, patbuf[MaxPathLen+1];
	size_t limit = 0;

	qpatnext = globtilde(pattern, patbuf, pglob);
	oldpathc = pglob->gl_pathc;
	bufnext = patbuf;

	/* We don't need to check for buffer overflow any more. */
	while ((c = *qpatnext++) != CHAR_EOS) {
		switch (c) {
		case CHAR_LBRACKET:
			c = *qpatnext;
			if (c == CHAR_NOT)
				++qpatnext;
			if (*qpatnext == CHAR_EOS ||
			    g_strchr(qpatnext+1, CHAR_RBRACKET) == NULL) {
				*bufnext++ = CHAR_LBRACKET;
				if (c == CHAR_NOT)
					--qpatnext;
				break;
			}
			*bufnext++ = M_SET;
			if (c == CHAR_NOT)
				*bufnext++ = M_NOT;
			c = *qpatnext++;
			do {
				*bufnext++ = CHAR(c);
				if (*qpatnext == CHAR_RANGE &&
				    (c = qpatnext[1]) != CHAR_RBRACKET) {
					*bufnext++ = M_RNG;
					*bufnext++ = CHAR(c);
					qpatnext += 2;
				}
			} while ((c = *qpatnext++) != CHAR_RBRACKET);
			pglob->gl_flags |= GLOB_MAGCHAR;
			*bufnext++ = M_END;
			break;
		case CHAR_QUESTION:
			pglob->gl_flags |= GLOB_MAGCHAR;
			*bufnext++ = M_ONE;
			break;
		case CHAR_STAR:
			pglob->gl_flags |= GLOB_MAGCHAR;
			/* collapse adjacent stars to one,
			 * to avoid exponential behavior
			 */
			if (bufnext == patbuf || bufnext[-1] != M_ALL)
			    *bufnext++ = M_ALL;
			break;
		default:
			*bufnext++ = CHAR(c);
			break;
		}
	}
	*bufnext = CHAR_EOS;
#ifdef DEBUG
	qprintf("glob0:", patbuf);
#endif

	if ((err = glob1(patbuf, pglob, &limit)) != 0)
		return(err);

	/*
	 * If there was no match we are going to append the pattern
	 * if GLOB_NOCHECK was specified or if GLOB_NOMAGIC was specified
	 * and the pattern did not contain any magic characters
	 * GLOB_NOMAGIC is there just for compatibility with csh.
	 */
	if (pglob->gl_pathc == oldpathc &&
	    ((pglob->gl_flags & GLOB_NOCHECK) ||
	      ((pglob->gl_flags & GLOB_NOMAGIC) &&
	       !(pglob->gl_flags & GLOB_MAGCHAR))))
		return(globextend(pattern, pglob, &limit));
	else if (!(pglob->gl_flags & GLOB_NOSORT))
		qsort(pglob->gl_pathv + pglob->gl_offs + oldpathc,
		    pglob->gl_pathc - oldpathc, sizeof(char *), compare);
	return(0);
}