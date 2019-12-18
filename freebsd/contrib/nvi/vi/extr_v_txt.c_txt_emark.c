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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {char* lb; size_t owrite; int /*<<< orphan*/  lno; scalar_t__ len; int /*<<< orphan*/  insert; int /*<<< orphan*/  lb_len; } ;
typedef  TYPE_1__ TEXT ;
typedef  int /*<<< orphan*/  SCR ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  BINC_RETW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char CH_ENDMARK ; 
 size_t KEY_COL (int /*<<< orphan*/ *,char) ; 
 scalar_t__ KEY_NAME (int /*<<< orphan*/ *,char) ; 
 scalar_t__ KEY_NEEDSWIDE (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  LINE_RESET ; 
 int /*<<< orphan*/  MEMMOVE (char*,char*,int /*<<< orphan*/ ) ; 
 int vs_change (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vs_columns (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t*,size_t*) ; 

__attribute__((used)) static int
txt_emark(SCR *sp, TEXT *tp, size_t cno)
{
	CHAR_T ch;
	u_char *kp;
	size_t chlen, nlen, olen;
	CHAR_T *p;

	ch = CH_ENDMARK;

	/*
	 * The end mark may not be the same size as the current character.
	 * Don't let the line shift.
	 */
	nlen = KEY_COL(sp, ch);
	if (tp->lb[cno] == '\t')
		(void)vs_columns(sp, tp->lb, tp->lno, &cno, &olen);
	else
		olen = KEY_COL(sp, tp->lb[cno]);

	/*
	 * If the line got longer, well, it's weird, but it's easy.  If
	 * it's the same length, it's easy.  If it got shorter, we have
	 * to fix it up.
	 */
	if (olen > nlen) {
		BINC_RETW(sp, tp->lb, tp->lb_len, tp->len + olen);
		chlen = olen - nlen;
		if (tp->insert != 0)
			MEMMOVE(tp->lb + cno + 1 + chlen,
			    tp->lb + cno + 1, tp->insert);

		tp->len += chlen;
		tp->owrite += chlen;
		p = tp->lb + cno;
		if (tp->lb[cno] == '\t' ||
		    KEY_NEEDSWIDE(sp, tp->lb[cno]))
			for (cno += chlen; chlen--;)
				*p++ = ' ';
		else
			for (kp = (u_char *)
			    KEY_NAME(sp, tp->lb[cno]),
			    cno += chlen; chlen--;)
				*p++ = *kp++;
	}
	tp->lb[cno] = ch;
	return (vs_change(sp, tp->lno, LINE_RESET));
}