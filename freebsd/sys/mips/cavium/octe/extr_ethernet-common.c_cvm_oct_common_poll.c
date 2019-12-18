#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ifnet {scalar_t__ if_softc; } ;
struct TYPE_6__ {scalar_t__ u64; } ;
typedef  TYPE_1__ cvmx_helper_link_info_t ;
struct TYPE_7__ {scalar_t__ link_info; int need_link_update; int /*<<< orphan*/  port; int /*<<< orphan*/ * miibus; int /*<<< orphan*/  (* poll ) (struct ifnet*) ;} ;
typedef  TYPE_2__ cvm_oct_private_t ;
struct TYPE_8__ {scalar_t__ board_type; } ;

/* Variables and functions */
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
 TYPE_1__ cvmx_helper_link_autoconf (int /*<<< orphan*/ ) ; 
 TYPE_1__ cvmx_helper_link_get (int /*<<< orphan*/ ) ; 
 TYPE_3__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  stub1 (struct ifnet*) ; 

void cvm_oct_common_poll(struct ifnet *ifp)
{
	cvm_oct_private_t *priv = (cvm_oct_private_t *)ifp->if_softc;
	cvmx_helper_link_info_t link_info;

	/*
	 * If this is a simulation, do nothing.
	 */
	if (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM)
		return;

	/*
	 * If there is a device-specific poll method, use it.
	 */
	if (priv->poll != NULL) {
		priv->poll(ifp);
		return;
	}

	/*
	 * If an MII bus is attached, don't use the Simple Executive's link
	 * state routines.
	 */
	if (priv->miibus != NULL)
		return;

	/*
	 * Use the Simple Executive's link state routines.
	 */
	link_info = cvmx_helper_link_get(priv->port);
	if (link_info.u64 == priv->link_info)
		return;

	link_info = cvmx_helper_link_autoconf(priv->port);
	priv->link_info = link_info.u64;
	priv->need_link_update = 1;
}