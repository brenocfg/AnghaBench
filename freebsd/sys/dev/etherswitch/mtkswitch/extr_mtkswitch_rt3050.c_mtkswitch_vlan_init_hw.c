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
typedef  int uint32_t ;
struct TYPE_2__ {int es_nvlangroups; int es_nports; } ;
struct mtkswitch_softc {scalar_t__ sc_switchtype; int numports; int valid_vlans; TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK (struct mtkswitch_softc*) ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK_ASSERT (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_POC2 ; 
 int /*<<< orphan*/  MTKSWITCH_PVID (int) ; 
 int MTKSWITCH_READ (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_UNLOCK (struct mtkswitch_softc*) ; 
 int /*<<< orphan*/  MTKSWITCH_VLANI (int) ; 
 int /*<<< orphan*/  MTKSWITCH_VMSC (int) ; 
 int /*<<< orphan*/  MTKSWITCH_VUB (int) ; 
 int /*<<< orphan*/  MTKSWITCH_WRITE (struct mtkswitch_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MTK_SWITCH_RT3050 ; 
 int POC2_UNTAG_VLAN ; 
 int PVID_MASK ; 
 int PVID_OFF (int) ; 
 int VLANI_MASK ; 
 int VLANI_OFF (int) ; 
 int VMSC_MASK ; 
 int VMSC_OFF (int) ; 
 int VUB_MASK ; 
 int VUB_OFF (int) ; 

__attribute__((used)) static void
mtkswitch_vlan_init_hw(struct mtkswitch_softc *sc)
{
	uint32_t val, vid;
	int i;

	MTKSWITCH_LOCK_ASSERT(sc, MA_NOTOWNED);
	MTKSWITCH_LOCK(sc);

	/* Reset everything to defaults first */
	for (i = 0; i < sc->info.es_nvlangroups; i++) {
		/* Remove all VLAN members and untag info, if any */
		if (i % 4 == 0) {
			MTKSWITCH_WRITE(sc, MTKSWITCH_VMSC(i), 0);
			if (sc->sc_switchtype != MTK_SWITCH_RT3050)
				MTKSWITCH_WRITE(sc, MTKSWITCH_VUB(i), 0);
		}
		/* Reset to default VIDs */
		val = MTKSWITCH_READ(sc, MTKSWITCH_VLANI(i));
		val &= ~(VLANI_MASK << VLANI_OFF(i));
		val |= ((i + 1) << VLANI_OFF(i));
		MTKSWITCH_WRITE(sc, MTKSWITCH_VLANI(i), val);
	}

	/* Now, add all ports as untagged members to VLAN1 */
	vid = 0;
	val = MTKSWITCH_READ(sc, MTKSWITCH_VMSC(vid));
	val &= ~(VMSC_MASK << VMSC_OFF(vid));
	val |= (((1<<sc->numports)-1) << VMSC_OFF(vid));
	MTKSWITCH_WRITE(sc, MTKSWITCH_VMSC(vid), val);
	if (sc->sc_switchtype != MTK_SWITCH_RT3050) {
		val = MTKSWITCH_READ(sc, MTKSWITCH_VUB(vid));
		val &= ~(VUB_MASK << VUB_OFF(vid));
		val |= (((1<<sc->numports)-1) << VUB_OFF(vid));
		MTKSWITCH_WRITE(sc, MTKSWITCH_VUB(vid), val);
	}
	val = MTKSWITCH_READ(sc, MTKSWITCH_POC2);
	if (sc->sc_switchtype != MTK_SWITCH_RT3050)
		val |= POC2_UNTAG_VLAN;
	val |= ((1<<sc->numports)-1);
	MTKSWITCH_WRITE(sc, MTKSWITCH_POC2, val);

	/* only the first vlangroup is valid */
	sc->valid_vlans = (1<<0);

	/* Set all port PVIDs to 1 */
	vid = 1;
	for (i = 0; i < sc->info.es_nports; i++) {
		val = MTKSWITCH_READ(sc, MTKSWITCH_PVID(i));
		val &= ~(PVID_MASK << PVID_OFF(i));
		val |= (vid << PVID_OFF(i));
		MTKSWITCH_WRITE(sc, MTKSWITCH_PVID(i), val);
	}

	MTKSWITCH_UNLOCK(sc);
}