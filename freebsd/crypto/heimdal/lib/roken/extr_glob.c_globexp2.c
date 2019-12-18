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
typedef  int /*<<< orphan*/  glob_t ;
typedef  scalar_t__ Char ;

/* Variables and functions */
#define  CHAR_COMMA 131 
 scalar_t__ const CHAR_EOS ; 
#define  CHAR_LBRACE 130 
#define  CHAR_LBRACKET 129 
#define  CHAR_RBRACE 128 
 scalar_t__ const CHAR_RBRACKET ; 
 int /*<<< orphan*/  MaxPathLen ; 
 int glob0 (scalar_t__*,int /*<<< orphan*/ *) ; 
 int globexp1 (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qprintf (char*,scalar_t__*) ; 

__attribute__((used)) static int globexp2(const Char *ptr, const Char *pattern,
		    glob_t *pglob, int *rv)
{
	int     i;
	Char   *lm, *ls;
	const Char *pe, *pm, *pl;
	Char    patbuf[MaxPathLen + 1];

	/* copy part up to the brace */
	for (lm = patbuf, pm = pattern; pm != ptr; *lm++ = *pm++)
		continue;
	ls = lm;

	/* Find the balanced brace */
	for (i = 0, pe = ++ptr; *pe; pe++)
		if (*pe == CHAR_LBRACKET) {
			/* Ignore everything between [] */
			for (pm = pe++; *pe != CHAR_RBRACKET && *pe != CHAR_EOS; pe++)
				continue;
			if (*pe == CHAR_EOS) {
				/*
				 * We could not find a matching CHAR_RBRACKET.
				 * Ignore and just look for CHAR_RBRACE
				 */
				pe = pm;
			}
		}
		else if (*pe == CHAR_LBRACE)
			i++;
		else if (*pe == CHAR_RBRACE) {
			if (i == 0)
				break;
			i--;
		}

	/* Non matching braces; just glob the pattern */
	if (i != 0 || *pe == CHAR_EOS) {
		*rv = glob0(patbuf, pglob);
		return 0;
	}

	for (i = 0, pl = pm = ptr; pm <= pe; pm++)
		switch (*pm) {
		case CHAR_LBRACKET:
			/* Ignore everything between [] */
			for (pl = pm++; *pm != CHAR_RBRACKET && *pm != CHAR_EOS; pm++)
				continue;
			if (*pm == CHAR_EOS) {
				/*
				 * We could not find a matching CHAR_RBRACKET.
				 * Ignore and just look for CHAR_RBRACE
				 */
				pm = pl;
			}
			break;

		case CHAR_LBRACE:
			i++;
			break;

		case CHAR_RBRACE:
			if (i) {
			    i--;
			    break;
			}
			/* FALLTHROUGH */
		case CHAR_COMMA:
			if (i && *pm == CHAR_COMMA)
				break;
			else {
				/* Append the current string */
				for (lm = ls; (pl < pm); *lm++ = *pl++)
					continue;
				/*
				 * Append the rest of the pattern after the
				 * closing brace
				 */
				for (pl = pe + 1; (*lm++ = *pl++) != CHAR_EOS;)
					continue;

				/* Expand the current pattern */
#ifdef DEBUG
				qprintf("globexp2:", patbuf);
#endif
				*rv = globexp1(patbuf, pglob);

				/* move after the comma, to the next string */
				pl = pm + 1;
			}
			break;

		default:
			break;
		}
	*rv = 0;
	return 0;
}