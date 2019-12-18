#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_10__ {size_t cols; int /*<<< orphan*/ * gp; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  GS ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_LIST ; 
 scalar_t__ INTERRUPTED (TYPE_1__*) ; 
 size_t KEY_COL (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* KEY_NAME (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L (char) ; 
 int /*<<< orphan*/  LF_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LF_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ O_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_LIST ; 
 int /*<<< orphan*/  O_TABSTOP ; 
 size_t O_VAL (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_printf (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  ex_puts (TYPE_1__*,char*) ; 

__attribute__((used)) static int
ex_prchars(SCR *sp, const CHAR_T *p, size_t *colp, size_t len, 
	    u_int flags, int repeatc)
{
	CHAR_T ch;
	char *kp;
	GS *gp;
	size_t col, tlen, ts;

	if (O_ISSET(sp, O_LIST))
		LF_SET(E_C_LIST);
	gp = sp->gp;
	ts = O_VAL(sp, O_TABSTOP);
	for (col = *colp; len--;)
		if ((ch = *p++) == L('\t') && !LF_ISSET(E_C_LIST))
			for (tlen = ts - col % ts;
			    col < sp->cols && tlen--; ++col) {
				(void)ex_printf(sp,
				    "%c", repeatc ? repeatc : ' ');
				if (INTERRUPTED(sp))
					goto intr;
			}
		else {
			kp = KEY_NAME(sp, ch);
			tlen = KEY_COL(sp, ch);

			/*
			 * Start a new line if the last character does not fit
			 * into the current line.  The implicit new lines are
			 * not interruptible.
			 */
			if (col + tlen > sp->cols) {
				col = 0;
				(void)ex_puts(sp, "\n");
			}

			col += tlen;
			if (!repeatc) {
				(void)ex_puts(sp, kp);
				if (INTERRUPTED(sp))
					goto intr;
			} else while (tlen--) {
				(void)ex_printf(sp, "%c", repeatc);
				if (INTERRUPTED(sp))
					goto intr;
			}
			if (col == sp->cols) {
				col = 0;
				(void)ex_puts(sp, "\n");
			}
		}
intr:	*colp = col;
	return (0);
}