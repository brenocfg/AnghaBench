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
typedef  scalar_t__ u_long ;
struct TYPE_3__ {scalar_t__* lb; size_t cno; size_t ai; size_t offset; size_t len; int /*<<< orphan*/  insert; int /*<<< orphan*/  owrite; } ;
typedef  TYPE_1__ TEXT ;
typedef  int /*<<< orphan*/  SCR ;
typedef  scalar_t__ CHAR_T ;

/* Variables and functions */
 scalar_t__ CH_HEX ; 
 int /*<<< orphan*/  MEMMOVE (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ STRTOL (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ UCHAR_MAX ; 
 scalar_t__ errno ; 

__attribute__((used)) static int
txt_hex(SCR *sp, TEXT *tp)
{
	CHAR_T savec;
	size_t len, off;
	u_long value;
	CHAR_T *p, *wp;

	/*
	 * Null-terminate the string.  Since nul isn't a legal hex value,
	 * this should be okay, and lets us use a local routine, which
	 * presumably understands the character set, to convert the value.
	 */
	savec = tp->lb[tp->cno];
	tp->lb[tp->cno] = 0;

	/* Find the previous CH_HEX character. */
	for (off = tp->cno - 1, p = tp->lb + off, len = 0;; --p, --off, ++len) {
		if (*p == CH_HEX) {
			wp = p + 1;
			break;
		}
		/* Not on this line?  Shouldn't happen. */
		if (off == tp->ai || off == tp->offset)
			goto nothex;
	}

	/* If length of 0, then it wasn't a hex value. */
	if (len == 0)
		goto nothex;

	/* Get the value. */
	errno = 0;
	value = STRTOL(wp, NULL, 16);
	if (errno || value > UCHAR_MAX) {
nothex:		tp->lb[tp->cno] = savec;
		return (0);
	}

	/* Restore the original character. */
	tp->lb[tp->cno] = savec;

	/* Adjust the bookkeeping. */
	tp->cno -= len;
	tp->len -= len;
	tp->lb[tp->cno - 1] = value;

	/* Copy down any overwrite characters. */
	if (tp->owrite)
		MEMMOVE(tp->lb + tp->cno, tp->lb + tp->cno + len, 
		    tp->owrite);

	/* Copy down any insert characters. */
	if (tp->insert)
		MEMMOVE(tp->lb + tp->cno + tp->owrite,
		    tp->lb + tp->cno + tp->owrite + len, 
		    tp->insert);

	return (0);
}