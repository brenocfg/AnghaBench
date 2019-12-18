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
struct hn_softc {int hn_xvf_flags; TYPE_1__* hn_vf_ifp; TYPE_2__* hn_ifp; } ;
struct TYPE_4__ {int /*<<< orphan*/  if_xname; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_xname; int /*<<< orphan*/  if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  HN_NVS_DATAPATH_VF ; 
 int HN_XVFFLAG_ENABLED ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  hn_nvs_set_datapath (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_vf_rss_fixup (struct hn_softc*,int) ; 
 int hn_xpnt_vf_iocsetflags (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_xpnt_vf_saveifflags (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_xpnt_vf_setenable (struct hn_softc*) ; 
 int /*<<< orphan*/  if_printf (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
hn_xpnt_vf_init(struct hn_softc *sc)
{
	int error;

	HN_LOCK_ASSERT(sc);

	KASSERT((sc->hn_xvf_flags & HN_XVFFLAG_ENABLED) == 0,
	    ("%s: transparent VF was enabled", sc->hn_ifp->if_xname));

	if (bootverbose) {
		if_printf(sc->hn_ifp, "try bringing up %s\n",
		    sc->hn_vf_ifp->if_xname);
	}

	/*
	 * Bring the VF up.
	 */
	hn_xpnt_vf_saveifflags(sc);
	sc->hn_vf_ifp->if_flags |= IFF_UP;
	error = hn_xpnt_vf_iocsetflags(sc);
	if (error) {
		if_printf(sc->hn_ifp, "bringing up %s failed: %d\n",
		    sc->hn_vf_ifp->if_xname, error);
		return;
	}

	/*
	 * NOTE:
	 * Datapath setting must happen _after_ bringing the VF up.
	 */
	hn_nvs_set_datapath(sc, HN_NVS_DATAPATH_VF);

	/*
	 * NOTE:
	 * Fixup RSS related bits _after_ the VF is brought up, since
	 * many VFs generate RSS key during it's initialization.
	 */
	hn_vf_rss_fixup(sc, true);

	/* Mark transparent mode VF as enabled. */
	hn_xpnt_vf_setenable(sc);
}