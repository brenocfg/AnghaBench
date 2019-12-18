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
struct tty {int /*<<< orphan*/  t_outq; scalar_t__ t_column; } ;

/* Variables and functions */
 scalar_t__ CMP_CC (int /*<<< orphan*/ ,char) ; 
 scalar_t__ CMP_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CTL_ECHO (char,int) ; 
 scalar_t__ CTL_PRINT (char,int) ; 
 int /*<<< orphan*/  ECHOCTL ; 
 int /*<<< orphan*/  OPOST ; 
 int /*<<< orphan*/  VEOF ; 
 int /*<<< orphan*/  l ; 
 int /*<<< orphan*/  o ; 
 int ttydisc_write_oproc (struct tty*,char) ; 
 int ttyoutq_write_nofrag (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
ttydisc_echo_force(struct tty *tp, char c, int quote)
{

	if (CMP_FLAG(o, OPOST) && CTL_ECHO(c, quote)) {
		/*
		 * Only perform postprocessing when OPOST is turned on
		 * and the character is an unquoted BS/TB/NL/CR.
		 */
		return ttydisc_write_oproc(tp, c);
	} else if (CMP_FLAG(l, ECHOCTL) && CTL_PRINT(c, quote)) {
		/*
		 * Only use ^X notation when ECHOCTL is turned on and
		 * we've got an quoted control character.
		 *
		 * Print backspaces when echoing an end-of-file.
		 */
		char ob[4] = "^?\b\b";

		/* Print ^X notation. */
		if (c != 0x7f)
			ob[1] = c + 'A' - 1;

		if (!quote && CMP_CC(VEOF, c)) {
			return ttyoutq_write_nofrag(&tp->t_outq, ob, 4);
		} else {
			tp->t_column += 2;
			return ttyoutq_write_nofrag(&tp->t_outq, ob, 2);
		}
	} else {
		/* Can just be printed. */
		tp->t_column++;
		return ttyoutq_write_nofrag(&tp->t_outq, &c, 1);
	}
}