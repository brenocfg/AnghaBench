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
struct xenbusb_softc {scalar_t__ xbs_connecting_children; int xbs_flags; int /*<<< orphan*/  xbs_lock; int /*<<< orphan*/  xbs_attach_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int XBS_ATTACH_CH_ACTIVE ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xenbusb_release_confighook(struct xenbusb_softc *xbs)
{
	mtx_lock(&xbs->xbs_lock);
	KASSERT(xbs->xbs_connecting_children > 0,
		("Connecting device count error\n"));
	xbs->xbs_connecting_children--;
	if (xbs->xbs_connecting_children == 0
	 && (xbs->xbs_flags & XBS_ATTACH_CH_ACTIVE) != 0) {
		xbs->xbs_flags &= ~XBS_ATTACH_CH_ACTIVE;
		mtx_unlock(&xbs->xbs_lock);
		config_intrhook_disestablish(&xbs->xbs_attach_ch);
	} else {
		mtx_unlock(&xbs->xbs_lock);
	}
}