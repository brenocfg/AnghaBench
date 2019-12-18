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
typedef  int xbd_flag_t ;
struct xbd_softc {int xbd_flags; int /*<<< orphan*/  xbd_qfrozen_cnt; } ;

/* Variables and functions */
 int XBDF_NONE ; 

__attribute__((used)) static void
xbd_freeze(struct xbd_softc *sc, xbd_flag_t xbd_flag)
{
	if (xbd_flag != XBDF_NONE && (sc->xbd_flags & xbd_flag) != 0)
		return;

	sc->xbd_flags |= xbd_flag;
	sc->xbd_qfrozen_cnt++;
}