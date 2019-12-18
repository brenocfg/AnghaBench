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
struct dcons_softc {struct tty* tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dcons_close_refs ; 
 struct dcons_softc* sc ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_rel_gone (struct tty*) ; 

__attribute__((used)) static int
dcons_detach(int port)
{
	struct	tty *tp;
	struct dcons_softc *dc;

	dc = &sc[port];
	tp = dc->tty;

	/* tty_rel_gone() schedules a deferred free callback, count it. */
	atomic_add_int(&dcons_close_refs, 1);
	tty_lock(tp);
	tty_rel_gone(tp);

	return(0);
}