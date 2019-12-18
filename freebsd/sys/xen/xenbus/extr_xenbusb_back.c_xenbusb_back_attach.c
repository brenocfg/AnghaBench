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
struct xenbusb_softc {int xbs_flags; int /*<<< orphan*/  xbs_lock; int /*<<< orphan*/  xbs_attach_ch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int XBS_ATTACH_CH_ACTIVE ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct xenbusb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int xenbusb_attach (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
xenbusb_back_attach(device_t dev)
{
	struct xenbusb_softc *xbs;
	int error;

	xbs = device_get_softc(dev);
	error = xenbusb_attach(dev, "backend", /*id_components*/2);

	/*
	 * Backend devices operate to serve other domains,
	 * so there is no need to hold up boot processing
	 * while connections to foreign domains are made.
	 */
	mtx_lock(&xbs->xbs_lock);
	if ((xbs->xbs_flags & XBS_ATTACH_CH_ACTIVE) != 0) {
		xbs->xbs_flags &= ~XBS_ATTACH_CH_ACTIVE;
		mtx_unlock(&xbs->xbs_lock);
		config_intrhook_disestablish(&xbs->xbs_attach_ch);
	} else {
		mtx_unlock(&xbs->xbs_lock);
	}

	return (error);
}