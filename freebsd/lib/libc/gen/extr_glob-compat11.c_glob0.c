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
struct glob_limit {int dummy; } ;
struct TYPE_6__ {size_t gl_pathc; int /*<<< orphan*/  gl_flags; } ;
typedef  TYPE_1__ glob11_t ;
typedef  int Char ;

/* Variables and functions */
 void* CHAR (int) ; 
 int /*<<< orphan*/  E2BIG ; 
 int EOS ; 
 int /*<<< orphan*/  GLOB_MAGCHAR ; 
 int GLOB_NOSPACE ; 
#define  LBRACKET 130 
 int MAXPATHLEN ; 
 int M_ALL ; 
 int /*<<< orphan*/  M_END ; 
 int /*<<< orphan*/  M_NOT ; 
 int /*<<< orphan*/  M_ONE ; 
 int /*<<< orphan*/  M_RNG ; 
 int /*<<< orphan*/  M_SET ; 
 int NOT ; 
#define  QUESTION 129 
 int const RANGE ; 
 int RBRACKET ; 
#define  STAR 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * g_strchr (int const*,int) ; 
 int glob1 (int*,TYPE_1__*,struct glob_limit*) ; 
 int globfinal (TYPE_1__*,struct glob_limit*,size_t,char const*) ; 
 int* globtilde (int const*,int*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  qprintf (char*,int*) ; 

__attribute__((used)) static int
glob0(const Char *pattern, glob11_t *pglob, struct glob_limit *limit,
    const char *origpat) {
	const Char *qpatnext;
	int err;
	size_t oldpathc;
	Char *bufnext, c, patbuf[MAXPATHLEN];

	qpatnext = globtilde(pattern, patbuf, MAXPATHLEN, pglob);
	if (qpatnext == NULL) {
		errno = E2BIG;
		return (GLOB_NOSPACE);
	}
	oldpathc = pglob->gl_pathc;
	bufnext = patbuf;

	/* We don't need to check for buffer overflow any more. */
	while ((c = *qpatnext++) != EOS) {
		switch (c) {
		case LBRACKET:
			c = *qpatnext;
			if (c == NOT)
				++qpatnext;
			if (*qpatnext == EOS ||
			    g_strchr(qpatnext+1, RBRACKET) == NULL) {
				*bufnext++ = LBRACKET;
				if (c == NOT)
					--qpatnext;
				break;
			}
			*bufnext++ = M_SET;
			if (c == NOT)
				*bufnext++ = M_NOT;
			c = *qpatnext++;
			do {
				*bufnext++ = CHAR(c);
				if (*qpatnext == RANGE &&
				    (c = qpatnext[1]) != RBRACKET) {
					*bufnext++ = M_RNG;
					*bufnext++ = CHAR(c);
					qpatnext += 2;
				}
			} while ((c = *qpatnext++) != RBRACKET);
			pglob->gl_flags |= GLOB_MAGCHAR;
			*bufnext++ = M_END;
			break;
		case QUESTION:
			pglob->gl_flags |= GLOB_MAGCHAR;
			*bufnext++ = M_ONE;
			break;
		case STAR:
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
	*bufnext = EOS;
#ifdef DEBUG
	qprintf("glob0:", patbuf);
#endif

	if ((err = glob1(patbuf, pglob, limit)) != 0)
		return(err);

	if (origpat != NULL)
		return (globfinal(pglob, limit, oldpathc, origpat));

	return (0);
}