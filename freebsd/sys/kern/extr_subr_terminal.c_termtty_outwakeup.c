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
struct tty {int dummy; } ;
struct terminal {int tm_flags; TYPE_1__* tm_class; int /*<<< orphan*/  tm_emulator; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tc_bell ) (struct terminal*) ;int /*<<< orphan*/  (* tc_done ) (struct terminal*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TERMINAL_LOCK_TTY (struct terminal*) ; 
 int /*<<< orphan*/  TERMINAL_UNLOCK_TTY (struct terminal*) ; 
 unsigned int TF_BELL ; 
 int TF_MUTE ; 
 int /*<<< orphan*/  stub1 (struct terminal*) ; 
 int /*<<< orphan*/  stub2 (struct terminal*) ; 
 int /*<<< orphan*/  teken_input (int /*<<< orphan*/ *,char*,size_t) ; 
 struct terminal* tty_softc (struct tty*) ; 
 size_t ttydisc_getc (struct tty*,char*,int) ; 

__attribute__((used)) static void
termtty_outwakeup(struct tty *tp)
{
	struct terminal *tm = tty_softc(tp);
	char obuf[128];
	size_t olen;
	unsigned int flags = 0;

	while ((olen = ttydisc_getc(tp, obuf, sizeof obuf)) > 0) {
		TERMINAL_LOCK_TTY(tm);
		if (!(tm->tm_flags & TF_MUTE)) {
			tm->tm_flags &= ~TF_BELL;
			teken_input(&tm->tm_emulator, obuf, olen);
			flags |= tm->tm_flags;
		}
		TERMINAL_UNLOCK_TTY(tm);
	}

	TERMINAL_LOCK_TTY(tm);
	if (!(tm->tm_flags & TF_MUTE))
		tm->tm_class->tc_done(tm);
	TERMINAL_UNLOCK_TTY(tm);
	if (flags & TF_BELL)
		tm->tm_class->tc_bell(tm);
}