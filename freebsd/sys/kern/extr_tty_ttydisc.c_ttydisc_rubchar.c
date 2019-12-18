#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * c_cc; } ;
struct tty {int t_writepos; int t_column; TYPE_1__ t_termios; int /*<<< orphan*/  t_outq; int /*<<< orphan*/  t_inq; } ;

/* Variables and functions */
 scalar_t__ CMP_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char CTAB ; 
 scalar_t__ CTL_PRINT (char,int) ; 
 int /*<<< orphan*/  ECHO ; 
 int /*<<< orphan*/  ECHOCTL ; 
 int /*<<< orphan*/  ECHOE ; 
 size_t VERASE ; 
 int /*<<< orphan*/  l ; 
 int /*<<< orphan*/  ttydisc_echo (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ttydisc_recalc_linelength (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_reprint (struct tty*) ; 
 scalar_t__ ttyinq_peekchar (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  ttyinq_unputchar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttyoutq_write_nofrag (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
ttydisc_rubchar(struct tty *tp)
{
	char c;
	int quote;
	unsigned int prevpos, tablen;

	if (ttyinq_peekchar(&tp->t_inq, &c, &quote) != 0)
		return (-1);
	ttyinq_unputchar(&tp->t_inq);

	if (CMP_FLAG(l, ECHO)) {
		/*
		 * Remove the character from the screen. This is even
		 * safe for characters that span multiple characters
		 * (tabs, quoted, etc).
		 */
		if (tp->t_writepos >= tp->t_column) {
			/* Retype the sentence. */
			ttydisc_reprint(tp);
		} else if (CMP_FLAG(l, ECHOE)) {
			if (CTL_PRINT(c, quote)) {
				/* Remove ^X formatted chars. */
				if (CMP_FLAG(l, ECHOCTL)) {
					tp->t_column -= 2;
					ttyoutq_write_nofrag(&tp->t_outq,
					    "\b\b  \b\b", 6);
				}
			} else if (c == ' ') {
				/* Space character needs no rubbing. */
				tp->t_column -= 1;
				ttyoutq_write_nofrag(&tp->t_outq, "\b", 1);
			} else if (c == CTAB) {
				/*
				 * Making backspace work with tabs is
				 * quite hard. Recalculate the length of
				 * this character and remove it.
				 *
				 * Because terminal settings could be
				 * changed while the line is being
				 * inserted, the calculations don't have
				 * to be correct. Make sure we keep the
				 * tab length within proper bounds.
				 */
				prevpos = ttydisc_recalc_linelength(tp);
				if (prevpos >= tp->t_column)
					tablen = 1;
				else
					tablen = tp->t_column - prevpos;
				if (tablen > 8)
					tablen = 8;

				tp->t_column = prevpos;
				ttyoutq_write_nofrag(&tp->t_outq,
				    "\b\b\b\b\b\b\b\b", tablen);
				return (0);
			} else {
				/*
				 * Remove a regular character by
				 * punching a space over it.
				 */
				tp->t_column -= 1;
				ttyoutq_write_nofrag(&tp->t_outq, "\b \b", 3);
			}
		} else {
			/* Don't print spaces. */
			ttydisc_echo(tp, tp->t_termios.c_cc[VERASE], 0);
		}
	}

	return (0);
}