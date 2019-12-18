#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct glob_limit {int dummy; } ;
typedef  int /*<<< orphan*/  glob11_t ;
typedef  scalar_t__ Char ;

/* Variables and functions */
#define  COMMA 131 
 scalar_t__ const EOS ; 
#define  LBRACE 130 
#define  LBRACKET 129 
 int MAXPATHLEN ; 
#define  RBRACE 128 
 scalar_t__ const RBRACKET ; 
 int glob0 (scalar_t__ const*,int /*<<< orphan*/ *,struct glob_limit*,int /*<<< orphan*/ *) ; 
 int globexp1 (scalar_t__*,int /*<<< orphan*/ *,struct glob_limit*) ; 
 int /*<<< orphan*/  qprintf (char*,scalar_t__*) ; 

__attribute__((used)) static int
globexp2(const Char *ptr, const Char *pattern, glob11_t *pglob,
    struct glob_limit *limit)
{
	int     i, rv;
	Char   *lm, *ls;
	const Char *pe, *pm, *pm1, *pl;
	Char    patbuf[MAXPATHLEN];

	/* copy part up to the brace */
	for (lm = patbuf, pm = pattern; pm != ptr; *lm++ = *pm++)
		continue;
	*lm = EOS;
	ls = lm;

	/* Find the balanced brace */
	for (i = 0, pe = ++ptr; *pe != EOS; pe++)
		if (*pe == LBRACKET) {
			/* Ignore everything between [] */
			for (pm = pe++; *pe != RBRACKET && *pe != EOS; pe++)
				continue;
			if (*pe == EOS) {
				/*
				 * We could not find a matching RBRACKET.
				 * Ignore and just look for RBRACE
				 */
				pe = pm;
			}
		}
		else if (*pe == LBRACE)
			i++;
		else if (*pe == RBRACE) {
			if (i == 0)
				break;
			i--;
		}

	/* Non matching braces; just glob the pattern */
	if (i != 0 || *pe == EOS)
		return (glob0(pattern, pglob, limit, NULL));

	for (i = 0, pl = pm = ptr; pm <= pe; pm++)
		switch (*pm) {
		case LBRACKET:
			/* Ignore everything between [] */
			for (pm1 = pm++; *pm != RBRACKET && *pm != EOS; pm++)
				continue;
			if (*pm == EOS) {
				/*
				 * We could not find a matching RBRACKET.
				 * Ignore and just look for RBRACE
				 */
				pm = pm1;
			}
			break;

		case LBRACE:
			i++;
			break;

		case RBRACE:
			if (i) {
			    i--;
			    break;
			}
			/* FALLTHROUGH */
		case COMMA:
			if (i && *pm == COMMA)
				break;
			else {
				/* Append the current string */
				for (lm = ls; (pl < pm); *lm++ = *pl++)
					continue;
				/*
				 * Append the rest of the pattern after the
				 * closing brace
				 */
				for (pl = pe + 1; (*lm++ = *pl++) != EOS;)
					continue;

				/* Expand the current pattern */
#ifdef DEBUG
				qprintf("globexp2:", patbuf);
#endif
				rv = globexp1(patbuf, pglob, limit);
				if (rv)
					return (rv);

				/* move after the comma, to the next string */
				pl = pm + 1;
			}
			break;

		default:
			break;
		}
	return (0);
}