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
struct terminal {int /*<<< orphan*/  tm_winsize; struct tty* tm_tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_set_winsize (struct tty*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

__attribute__((used)) static void
terminal_sync_ttysize(struct terminal *tm)
{
	struct tty *tp;

	tp = tm->tm_tty;
	if (tp == NULL)
		return;

	tty_lock(tp);
	tty_set_winsize(tp, &tm->tm_winsize);
	tty_unlock(tp);
}