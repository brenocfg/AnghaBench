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
struct TYPE_3__ {int obp_len; char* obp; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EX_PRIVATE ;

/* Variables and functions */
 TYPE_1__* EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ex_fflush (int /*<<< orphan*/ *) ; 

int
ex_puts(SCR *sp, const char *str)
{
	EX_PRIVATE *exp;
	int doflush, n;

	exp = EXP(sp);

	/* Flush when reach a <newline> or the end of the buffer. */
	for (doflush = n = 0; *str != '\0'; ++n) {
		if (exp->obp_len > sizeof(exp->obp))
			(void)ex_fflush(sp);
		if ((exp->obp[exp->obp_len++] = *str++) == '\n')
			doflush = 1;
	}
	if (doflush)
		(void)ex_fflush(sp);
	return (n);
}