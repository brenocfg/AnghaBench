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
typedef  int term_char_t ;
struct tty {int dummy; } ;
struct terminal {struct tty* tm_tty; } ;

/* Variables and functions */
 int TCHAR_CHARACTER (int) ; 
 int TCHAR_FORMAT (int) ; 
 int TF_CJK_RIGHT ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint_simple (struct tty*,char*,int) ; 

void
terminal_input_char(struct terminal *tm, term_char_t c)
{
	struct tty *tp;

	tp = tm->tm_tty;
	if (tp == NULL)
		return;

	/*
	 * Strip off any attributes. Also ignore input of second part of
	 * CJK fullwidth characters, as we don't want to return these
	 * characters twice.
	 */
	if (TCHAR_FORMAT(c) & TF_CJK_RIGHT)
		return;
	c = TCHAR_CHARACTER(c);

	tty_lock(tp);
	/*
	 * Conversion to UTF-8.
	 */
	if (c < 0x80) {
		ttydisc_rint(tp, c, 0);
	} else if (c < 0x800) {
		char str[2] = {
			0xc0 | (c >> 6),
			0x80 | (c & 0x3f)
		};

		ttydisc_rint_simple(tp, str, sizeof str);
	} else if (c < 0x10000) {
		char str[3] = {
			0xe0 | (c >> 12),
			0x80 | ((c >> 6) & 0x3f),
			0x80 | (c & 0x3f)
		};

		ttydisc_rint_simple(tp, str, sizeof str);
	} else {
		char str[4] = {
			0xf0 | (c >> 18),
			0x80 | ((c >> 12) & 0x3f),
			0x80 | ((c >> 6) & 0x3f),
			0x80 | (c & 0x3f)
		};

		ttydisc_rint_simple(tp, str, sizeof str);
	}
	ttydisc_rint_done(tp);
	tty_unlock(tp);
}