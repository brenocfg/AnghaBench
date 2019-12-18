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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  tmd ;
struct letmd {int /*<<< orphan*/  tmd2; int /*<<< orphan*/  tmd0; int /*<<< orphan*/  tmd1; } ;
struct lance_softc {int sc_first_td; scalar_t__ sc_no_td; int sc_flags; int sc_ntbuf; int sc_wdog_timer; int /*<<< orphan*/  (* sc_nocarrier ) (struct lance_softc*) ;int /*<<< orphan*/  (* sc_copyfromdesc ) (struct lance_softc*,struct letmd*,int /*<<< orphan*/ ,int) ;struct ifnet* sc_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int LE_CARRIER ; 
 int LE_DEBUG ; 
 int LE_LE32TOH (int /*<<< orphan*/ ) ; 
 int LE_T1_ERR ; 
 int LE_T1_MORE ; 
 int LE_T1_ONE ; 
 int LE_T1_OWN ; 
 int LE_T2_BUFF ; 
 int LE_T2_LCAR ; 
 int LE_T2_LCOL ; 
 int LE_T2_RTRY ; 
 int LE_T2_UFLO ; 
 int /*<<< orphan*/  LE_TMDADDR (struct lance_softc*,int) ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,...) ; 
 int /*<<< orphan*/  lance_init_locked (struct lance_softc*) ; 
 int /*<<< orphan*/  stub1 (struct lance_softc*,struct letmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct lance_softc*) ; 

__attribute__((used)) static inline void
am79900_tint(struct lance_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;
	struct letmd tmd;
	uint32_t tmd1, tmd2;
	int bix;

	bix = sc->sc_first_td;

	for (;;) {
		if (sc->sc_no_td <= 0)
			break;

		(*sc->sc_copyfromdesc)(sc, &tmd, LE_TMDADDR(sc, bix),
		    sizeof(tmd));

		tmd1 = LE_LE32TOH(tmd.tmd1);

#ifdef LEDEBUG
		if (sc->sc_flags & LE_DEBUG)
			if_printf(ifp, "trans tmd: "
			    "adr %08x, flags/blen %08x\n",
			    LE_LE32TOH(tmd.tmd0), tmd1);
#endif

		if (tmd1 & LE_T1_OWN)
			break;

		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

		if (tmd1 & LE_T1_ERR) {
			tmd2 = LE_LE32TOH(tmd.tmd2);
			if (tmd2 & LE_T2_BUFF)
				if_printf(ifp, "transmit buffer error\n");
			else if (tmd2 & LE_T2_UFLO)
				if_printf(ifp, "underflow\n");
			if (tmd2 & (LE_T2_BUFF | LE_T2_UFLO)) {
				lance_init_locked(sc);
				return;
			}
			if (tmd2 & LE_T2_LCAR) {
				if (sc->sc_flags & LE_CARRIER)
					if_link_state_change(ifp,
					    LINK_STATE_DOWN);
				sc->sc_flags &= ~LE_CARRIER;
				if (sc->sc_nocarrier)
					(*sc->sc_nocarrier)(sc);
				else
					if_printf(ifp, "lost carrier\n");
			}
			if (tmd2 & LE_T2_LCOL)
				if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 1);
			if (tmd2 & LE_T2_RTRY) {
#ifdef LEDEBUG
				if_printf(ifp, "excessive collisions\n");
#endif
				if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 16);
			}
			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		} else {
			if (tmd1 & LE_T1_ONE)
				if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 1);
			else if (tmd1 & LE_T1_MORE)
				/* Real number is unknown. */
				if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 2);
			if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
		}

		if (++bix == sc->sc_ntbuf)
			bix = 0;

		--sc->sc_no_td;
	}

	sc->sc_first_td = bix;

	sc->sc_wdog_timer = sc->sc_no_td > 0 ? 5 : 0;
}