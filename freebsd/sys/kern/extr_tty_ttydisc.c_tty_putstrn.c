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
struct tty {int /*<<< orphan*/  t_inq; int /*<<< orphan*/  t_column; int /*<<< orphan*/  t_writepos; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ tty_gone (struct tty*) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydevsw_outwakeup (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_echo_force (struct tty*,char const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyinq_reprintpos_set (int /*<<< orphan*/ *) ; 

int
tty_putstrn(struct tty *tp, const char *p, size_t n)
{
	size_t i;

	tty_lock_assert(tp, MA_OWNED);

	if (tty_gone(tp))
		return (-1);

	for (i = 0; i < n; i++)
		ttydisc_echo_force(tp, p[i], 0);

	tp->t_writepos = tp->t_column;
	ttyinq_reprintpos_set(&tp->t_inq);

	ttydevsw_outwakeup(tp);
	return (0);
}