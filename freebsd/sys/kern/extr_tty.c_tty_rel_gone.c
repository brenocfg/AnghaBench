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
struct tty {int /*<<< orphan*/  t_flags; int /*<<< orphan*/  t_dcdwait; int /*<<< orphan*/  t_bgwait; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TF_GONE ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_gone (struct tty*) ; 
 int /*<<< orphan*/  tty_rel_free (struct tty*) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty*,int) ; 
 int /*<<< orphan*/  ttydisc_modem (struct tty*,int /*<<< orphan*/ ) ; 

void
tty_rel_gone(struct tty *tp)
{

	MPASS(!tty_gone(tp));

	/* Simulate carrier removal. */
	ttydisc_modem(tp, 0);

	/* Wake up all blocked threads. */
	tty_wakeup(tp, FREAD|FWRITE);
	cv_broadcast(&tp->t_bgwait);
	cv_broadcast(&tp->t_dcdwait);

	tp->t_flags |= TF_GONE;
	tty_rel_free(tp);
}