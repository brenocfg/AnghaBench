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
struct tty {int dummy; } ;
struct terminal {int /*<<< orphan*/  tm_emulator; struct tty* tm_tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 char* teken_get_sequence (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint_simple (struct tty*,char const*,int /*<<< orphan*/ ) ; 

void
terminal_input_special(struct terminal *tm, unsigned int k)
{
	struct tty *tp;
	const char *str;

	tp = tm->tm_tty;
	if (tp == NULL)
		return;

	str = teken_get_sequence(&tm->tm_emulator, k);
	if (str == NULL)
		return;

	tty_lock(tp);
	ttydisc_rint_simple(tp, str, strlen(str));
	ttydisc_rint_done(tp);
	tty_unlock(tp);
}