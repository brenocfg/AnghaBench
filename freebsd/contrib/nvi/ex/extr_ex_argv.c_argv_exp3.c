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
struct TYPE_9__ {int argc; TYPE_1__** argv; } ;
struct TYPE_8__ {int argsoff; int /*<<< orphan*/ * argv; TYPE_1__** args; } ;
struct TYPE_7__ {size_t len; int* bp; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ EX_PRIVATE ;
typedef  TYPE_3__ EXCMD ;
typedef  int CHAR_T ;

/* Variables and functions */
 TYPE_2__* EXP (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ESCAPE (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  TRACE (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_alloc (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ cmdskip (int) ; 
 size_t cnt ; 

int
argv_exp3(SCR *sp, EXCMD *excp, CHAR_T *cmd, size_t cmdlen)
{
	EX_PRIVATE *exp;
	size_t len;
	int ch, off;
	CHAR_T *ap, *p;

	for (exp = EXP(sp); cmdlen > 0; ++exp->argsoff) {
		/* Skip any leading whitespace. */
		for (; cmdlen > 0; --cmdlen, ++cmd) {
			ch = *cmd;
			if (!cmdskip(ch))
				break;
		}
		if (cmdlen == 0)
			break;

		/*
		 * Determine the length of this whitespace delimited
		 * argument.
		 *
		 * QUOTING NOTE:
		 *
		 * Skip any character preceded by the user's quoting
		 * character.
		 */
		for (ap = cmd, len = 0; cmdlen > 0; ++cmd, --cmdlen, ++len) {
			ch = *cmd;
			if (IS_ESCAPE(sp, excp, ch) && cmdlen > 1) {
				++cmd;
				--cmdlen;
			} else if (cmdskip(ch))
				break;
		}

		/*
		 * Copy the argument into place.
		 *
		 * QUOTING NOTE:
		 *
		 * Lose quote chars.
		 */
		argv_alloc(sp, len);
		off = exp->argsoff;
		exp->args[off]->len = len;
		for (p = exp->args[off]->bp; len > 0; --len, *p++ = *ap++)
			if (IS_ESCAPE(sp, excp, *ap))
				++ap;
		*p = '\0';
	}
	excp->argv = exp->args;
	excp->argc = exp->argsoff;

#if defined(DEBUG) && 0
	for (cnt = 0; cnt < exp->argsoff; ++cnt)
		TRACE(sp, "arg %d: {%s}\n", cnt, exp->argv[cnt]);
#endif
	return (0);
}