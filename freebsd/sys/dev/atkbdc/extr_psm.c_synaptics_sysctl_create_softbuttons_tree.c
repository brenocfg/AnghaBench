#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int softbuttons_y; int softbutton2_x; int softbutton3_x; int /*<<< orphan*/  sysctl_tree; int /*<<< orphan*/  sysctl_ctx; } ;
struct TYPE_3__ {scalar_t__ topButtonPad; } ;
struct psm_softc {TYPE_2__ syninfo; TYPE_1__ synhw; } ;

/* Variables and functions */
 int CTLFLAG_ANYBODY ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYNAPTICS_SYSCTL_SOFTBUTTON2_X ; 
 int /*<<< orphan*/  SYNAPTICS_SYSCTL_SOFTBUTTON3_X ; 
 int /*<<< orphan*/  SYNAPTICS_SYSCTL_SOFTBUTTONS_Y ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct psm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synaptics_sysctl ; 

__attribute__((used)) static void
synaptics_sysctl_create_softbuttons_tree(struct psm_softc *sc)
{
	/*
	 * Set predefined sizes for softbuttons.
	 * Values are taken to match HP Pavilion dv6 clickpad drawings
	 * with thin middle softbutton placed on separator
	 */

	/* hw.psm.synaptics.softbuttons_y */
	sc->syninfo.softbuttons_y = sc->synhw.topButtonPad ? -1700 : 1700;
	SYSCTL_ADD_PROC(&sc->syninfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->syninfo.sysctl_tree), OID_AUTO,
	    "softbuttons_y", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, SYNAPTICS_SYSCTL_SOFTBUTTONS_Y,
	    synaptics_sysctl, "I",
	    "Vertical size of softbuttons area");

	/* hw.psm.synaptics.softbutton2_x */
	sc->syninfo.softbutton2_x = 3100;
	SYSCTL_ADD_PROC(&sc->syninfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->syninfo.sysctl_tree), OID_AUTO,
	    "softbutton2_x", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, SYNAPTICS_SYSCTL_SOFTBUTTON2_X,
	    synaptics_sysctl, "I",
	    "Horisontal position of 2-nd softbutton left edge (0-disable)");

	/* hw.psm.synaptics.softbutton3_x */
	sc->syninfo.softbutton3_x = 3900;
	SYSCTL_ADD_PROC(&sc->syninfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->syninfo.sysctl_tree), OID_AUTO,
	    "softbutton3_x", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, SYNAPTICS_SYSCTL_SOFTBUTTON3_X,
	    synaptics_sysctl, "I",
	    "Horisontal position of 3-rd softbutton left edge (0-disable)");
}