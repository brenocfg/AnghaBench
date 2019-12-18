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
struct TYPE_2__ {scalar_t__* c_cc; } ;
struct tty {int /*<<< orphan*/  t_inq; TYPE_1__ t_termios; } ;
typedef  scalar_t__ cc_t ;

/* Variables and functions */
 scalar_t__ CNL ; 
 size_t VREPRINT ; 
 scalar_t__ _POSIX_VDISABLE ; 
 int /*<<< orphan*/  ttydisc_echo (struct tty*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_reprint_char ; 
 int /*<<< orphan*/  ttyinq_line_iterate_from_linestart (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tty*) ; 
 int /*<<< orphan*/  ttyinq_reprintpos_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ttydisc_reprint(struct tty *tp)
{
	cc_t c;

	/* Print  ^R\n, followed by the line. */
	c = tp->t_termios.c_cc[VREPRINT];
	if (c != _POSIX_VDISABLE)
		ttydisc_echo(tp, c, 0);
	ttydisc_echo(tp, CNL, 0);
	ttyinq_reprintpos_reset(&tp->t_inq);

	ttyinq_line_iterate_from_linestart(&tp->t_inq, ttydisc_reprint_char, tp);
}