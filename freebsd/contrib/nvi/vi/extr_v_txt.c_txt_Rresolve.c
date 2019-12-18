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
struct TYPE_6__ {size_t owrite; size_t insert; scalar_t__ len; scalar_t__ cno; scalar_t__ lb; int /*<<< orphan*/  lno; scalar_t__ R_erase; } ;
typedef  int /*<<< orphan*/  TEXTH ;
typedef  TYPE_1__ TEXT ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int DBG_FATAL ; 
 int DBG_NOCACHE ; 
 int /*<<< orphan*/  MEMCPY (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 size_t MIN (size_t,size_t const) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ db_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  q ; 

__attribute__((used)) static void
txt_Rresolve(SCR *sp, TEXTH *tiqh, TEXT *tp, const size_t orig_len)
{
	TEXT *ttp;
	size_t input_len, retain;
	CHAR_T *p;

	/*
	 * Check to make sure that the cursor hasn't moved beyond
	 * the end of the line.
	 */
	if (tp->owrite == 0)
		return;

	/*
	 * Calculate how many characters the user has entered,
	 * plus the blanks erased by <carriage-return>/<newline>s.
	 */
	for (ttp = TAILQ_FIRST(tiqh), input_len = 0;;) {
		input_len += ttp == tp ? tp->cno : ttp->len + ttp->R_erase;
		if ((ttp = TAILQ_NEXT(ttp, q)) == NULL)
			break;
	}

	/*
	 * If the user has entered less characters than the original line
	 * was long, restore any overwriteable characters to the original
	 * characters.  These characters are entered as "insert characters",
	 * because they're after the cursor and we don't want to lose them.
	 * (This is okay because the R command has no insert characters.)
	 * We set owrite to 0 so that the insert characters don't get copied
	 * to somewhere else, which means that the line and the length have
	 * to be adjusted here as well.
	 *
	 * We have to retrieve the original line because the original pinned
	 * page has long since been discarded.  If it doesn't exist, that's
	 * okay, the user just extended the file.
	 */
	if (input_len < orig_len) {
		retain = MIN(tp->owrite, orig_len - input_len);
		if (db_get(sp,
		    TAILQ_FIRST(tiqh)->lno, DBG_FATAL | DBG_NOCACHE, &p, NULL))
			return;
		MEMCPY(tp->lb + tp->cno, p + input_len, retain);
		tp->len -= tp->owrite - retain;
		tp->owrite = 0;
		tp->insert += retain;
	}
}