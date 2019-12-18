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
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  EX_PRIVATE ;
typedef  int /*<<< orphan*/  EXCMD ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/ * EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FREE_SPACEW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  GET_SPACE_RETW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  argv_exp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ argv_fexp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ **,size_t*,int) ; 
 int /*<<< orphan*/  cmdskip (int /*<<< orphan*/ ) ; 

int
argv_exp1(SCR *sp, EXCMD *excp, CHAR_T *cmd, size_t cmdlen, int is_bang)
{
	EX_PRIVATE *exp;
	size_t blen, len;
	CHAR_T *p, *t, *bp;

	GET_SPACE_RETW(sp, bp, blen, 512);

	len = 0;
	exp = EXP(sp);
	if (argv_fexp(sp, excp, cmd, cmdlen, bp, &len, &bp, &blen, is_bang)) {
		FREE_SPACEW(sp, bp, blen);
		return (1);
	}

	/* If it's empty, we're done. */
	if (len != 0) {
		for (p = bp, t = bp + len; p < t; ++p)
			if (!cmdskip(*p))
				break;
		if (p == t)
			goto ret;
	} else
		goto ret;

	(void)argv_exp0(sp, excp, bp, len);

ret:	FREE_SPACEW(sp, bp, blen);
	return (0);
}