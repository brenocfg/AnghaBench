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
struct ifnet {size_t if_index; int /*<<< orphan*/  if_xname; int /*<<< orphan*/ * if_input; } ;
struct hn_softc {int hn_flags; int hn_xvf_flags; scalar_t__ hn_vf_rdytick; TYPE_1__* hn_ifp; int /*<<< orphan*/  hn_saved_tsosegsz; int /*<<< orphan*/  hn_saved_tsosegcnt; int /*<<< orphan*/  hn_saved_tsomax; int /*<<< orphan*/  hn_saved_caps; int /*<<< orphan*/ * hn_vf_input; int /*<<< orphan*/  hn_vf_init; int /*<<< orphan*/  hn_vf_taskq; int /*<<< orphan*/ * hn_vf_ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_xname; int /*<<< orphan*/  if_hw_tsomaxsegsize; int /*<<< orphan*/  if_hw_tsomaxsegcount; int /*<<< orphan*/  if_hw_tsomax; int /*<<< orphan*/  if_capabilities; } ;

/* Variables and functions */
 int HN_FLAG_SYNTH_ATTACHED ; 
 int /*<<< orphan*/  HN_LOCK (struct hn_softc*) ; 
 int /*<<< orphan*/  HN_NVS_DATAPATH_SYNTH ; 
 int /*<<< orphan*/  HN_UNLOCK (struct hn_softc*) ; 
 int HN_XVFFLAG_ENABLED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  hn_ismyvf (struct hn_softc*,struct ifnet*) ; 
 int /*<<< orphan*/  hn_nvs_set_datapath (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_resume_mgmt (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_vf_rss_restore (struct hn_softc*) ; 
 TYPE_1__** hn_vfmap ; 
 int /*<<< orphan*/  hn_vfmap_lock ; 
 size_t hn_vfmap_size ; 
 scalar_t__ hn_xpnt_vf ; 
 int /*<<< orphan*/  hn_xpnt_vf_setdisable (struct hn_softc*,int) ; 
 int /*<<< orphan*/  rm_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_ifnet_detevent(void *xsc, struct ifnet *ifp)
{
	struct hn_softc *sc = xsc;

	HN_LOCK(sc);

	if (sc->hn_vf_ifp == NULL)
		goto done;

	if (!hn_ismyvf(sc, ifp))
		goto done;

	if (hn_xpnt_vf) {
		/*
		 * Make sure that the delayed initialization is not running.
		 *
		 * NOTE:
		 * - This lock _must_ be released, since the hn_vf_init task
		 *   will try holding this lock.
		 * - It is safe to release this lock here, since the
		 *   hn_ifnet_attevent() is interlocked by the hn_vf_ifp.
		 *
		 * XXX racy, if hn(4) ever detached.
		 */
		HN_UNLOCK(sc);
		taskqueue_drain_timeout(sc->hn_vf_taskq, &sc->hn_vf_init);
		HN_LOCK(sc);

		KASSERT(sc->hn_vf_input != NULL, ("%s VF input is not saved",
		    sc->hn_ifp->if_xname));
		ifp->if_input = sc->hn_vf_input;
		sc->hn_vf_input = NULL;

		if ((sc->hn_flags & HN_FLAG_SYNTH_ATTACHED) &&
		    (sc->hn_xvf_flags & HN_XVFFLAG_ENABLED))
			hn_nvs_set_datapath(sc, HN_NVS_DATAPATH_SYNTH);

		if (sc->hn_vf_rdytick == 0) {
			/*
			 * The VF was ready; restore some settings.
			 */
			sc->hn_ifp->if_capabilities = sc->hn_saved_caps;
			/*
			 * NOTE:
			 * There is _no_ need to fixup if_capenable and
			 * if_hwassist, since the if_capabilities before
			 * restoration was an intersection of the VF's
			 * if_capabilites and the synthetic device's
			 * if_capabilites.
			 */
			sc->hn_ifp->if_hw_tsomax = sc->hn_saved_tsomax;
			sc->hn_ifp->if_hw_tsomaxsegcount =
			    sc->hn_saved_tsosegcnt;
			sc->hn_ifp->if_hw_tsomaxsegsize = sc->hn_saved_tsosegsz;
		}

		if (sc->hn_flags & HN_FLAG_SYNTH_ATTACHED) {
			/*
			 * Restore RSS settings.
			 */
			hn_vf_rss_restore(sc);

			/*
			 * Resume link status management, which was suspended
			 * by hn_ifnet_attevent().
			 */
			hn_resume_mgmt(sc);
		}
	}

	/* Mark transparent mode VF as disabled. */
	hn_xpnt_vf_setdisable(sc, true /* clear hn_vf_ifp */);

	rm_wlock(&hn_vfmap_lock);

	KASSERT(ifp->if_index < hn_vfmap_size,
	    ("ifindex %d, vfmapsize %d", ifp->if_index, hn_vfmap_size));
	if (hn_vfmap[ifp->if_index] != NULL) {
		KASSERT(hn_vfmap[ifp->if_index] == sc->hn_ifp,
		    ("%s: ifindex %d was mapped to %s",
		     ifp->if_xname, ifp->if_index,
		     hn_vfmap[ifp->if_index]->if_xname));
		hn_vfmap[ifp->if_index] = NULL;
	}

	rm_wunlock(&hn_vfmap_lock);
done:
	HN_UNLOCK(sc);
}