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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct pts_softc {TYPE_1__ pts_inpoll; int /*<<< orphan*/  pts_inwait; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selwakeup (TYPE_1__*) ; 
 struct pts_softc* tty_softc (struct tty*) ; 

__attribute__((used)) static void
ptsdrv_inwakeup(struct tty *tp)
{
	struct pts_softc *psc = tty_softc(tp);

	cv_broadcast(&psc->pts_inwait);
	selwakeup(&psc->pts_inpoll);
	KNOTE_LOCKED(&psc->pts_inpoll.si_note, 0);
}