#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  VI_PRIVATE ;
struct TYPE_4__ {int cno; size_t ai; size_t offset; int insert; int owrite; int len; int /*<<< orphan*/ * lb; } ;
typedef  TYPE_1__ TEXT ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 scalar_t__ LF_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXT_APPENDEOL ; 
 int /*<<< orphan*/ * VIP (int /*<<< orphan*/ *) ; 
 scalar_t__ isblank (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
txt_margin(SCR *sp, TEXT *tp, TEXT *wmtp, int *didbreak, u_int32_t flags)
{
	VI_PRIVATE *vip;
	size_t len, off;
	CHAR_T *p, *wp;

	/* Find the nearest previous blank. */
	for (off = tp->cno - 1, p = tp->lb + off, len = 0;; --off, --p, ++len) {
		if (isblank(*p)) {
			wp = p + 1;
			break;
		}

		/*
		 * If reach the start of the line, there's nowhere to break.
		 *
		 * !!!
		 * Historic vi belled each time a character was entered after
		 * crossing the margin until a space was entered which could
		 * be used to break the line.  I don't as it tends to wake the
		 * cats.
		 */
		if (off == tp->ai || off == tp->offset) {
			*didbreak = 0;
			return (0);
		}
	}

	/*
	 * Store saved information about the rest of the line in the
	 * wrapmargin TEXT structure.
	 *
	 * !!!
	 * The offset field holds the length of the current characters
	 * that the user entered, but which are getting split to the new
	 * line -- it's going to be used to set the cursor value when we
	 * move to the new line.
	 */
	vip = VIP(sp);
	wmtp->lb = p + 1;
	wmtp->offset = len;
	wmtp->insert = LF_ISSET(TXT_APPENDEOL) ?  tp->insert - 1 : tp->insert;
	wmtp->owrite = tp->owrite;

	/* Correct current bookkeeping information. */
	tp->cno -= len;
	if (LF_ISSET(TXT_APPENDEOL)) {
		tp->len -= len + tp->owrite + (tp->insert - 1);
		tp->insert = 1;
	} else {
		tp->len -= len + tp->owrite + tp->insert;
		tp->insert = 0;
	}
	tp->owrite = 0;

	/*
	 * !!!
	 * Delete any trailing whitespace from the current line.
	 */
	for (;; --p, --off) {
		if (!isblank(*p))
			break;
		--tp->cno;
		--tp->len;
		if (off == tp->ai || off == tp->offset)
			break;
	}
	*didbreak = 1;
	return (0);
}