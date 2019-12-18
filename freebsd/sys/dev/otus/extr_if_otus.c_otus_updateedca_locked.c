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
struct wmeParams {int wmep_txopLimit; int /*<<< orphan*/  wmep_aifsn; int /*<<< orphan*/  wmep_logcwmin; int /*<<< orphan*/  wmep_logcwmax; } ;
struct ieee80211com {int dummy; } ;
struct otus_softc {struct ieee80211com sc_ic; } ;
struct chanAccParams {struct wmeParams* cap_wmeParams; } ;

/* Variables and functions */
 int AIFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_MAC_REG_AC0_CW ; 
 int /*<<< orphan*/  AR_MAC_REG_AC1_AC0_AIFS ; 
 int /*<<< orphan*/  AR_MAC_REG_AC1_AC0_TXOP ; 
 int /*<<< orphan*/  AR_MAC_REG_AC1_CW ; 
 int /*<<< orphan*/  AR_MAC_REG_AC2_CW ; 
 int /*<<< orphan*/  AR_MAC_REG_AC3_AC2_AIFS ; 
 int /*<<< orphan*/  AR_MAC_REG_AC3_AC2_TXOP ; 
 int /*<<< orphan*/  AR_MAC_REG_AC3_CW ; 
 int /*<<< orphan*/  AR_MAC_REG_AC4_CW ; 
 int EXP2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTUS_LOCK_ASSERT (struct otus_softc*) ; 
 size_t WME_AC_BE ; 
 size_t WME_AC_BK ; 
 size_t WME_AC_VI ; 
 size_t WME_AC_VO ; 
 int /*<<< orphan*/  ieee80211_wme_ic_getparams (struct ieee80211com*,struct chanAccParams*) ; 
 int /*<<< orphan*/  otus_write (struct otus_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  otus_write_barrier (struct otus_softc*) ; 

__attribute__((used)) static void
otus_updateedca_locked(struct otus_softc *sc)
{
#define EXP2(val)	((1 << (val)) - 1)
#define AIFS(val)	((val) * 9 + 10)
	struct chanAccParams chp;
	struct ieee80211com *ic = &sc->sc_ic;
	const struct wmeParams *edca;

	ieee80211_wme_ic_getparams(ic, &chp);

	OTUS_LOCK_ASSERT(sc);

	edca = chp.cap_wmeParams;

	/* Set CWmin/CWmax values. */
	otus_write(sc, AR_MAC_REG_AC0_CW,
	    EXP2(edca[WME_AC_BE].wmep_logcwmax) << 16 |
	    EXP2(edca[WME_AC_BE].wmep_logcwmin));
	otus_write(sc, AR_MAC_REG_AC1_CW,
	    EXP2(edca[WME_AC_BK].wmep_logcwmax) << 16 |
	    EXP2(edca[WME_AC_BK].wmep_logcwmin));
	otus_write(sc, AR_MAC_REG_AC2_CW,
	    EXP2(edca[WME_AC_VI].wmep_logcwmax) << 16 |
	    EXP2(edca[WME_AC_VI].wmep_logcwmin));
	otus_write(sc, AR_MAC_REG_AC3_CW,
	    EXP2(edca[WME_AC_VO].wmep_logcwmax) << 16 |
	    EXP2(edca[WME_AC_VO].wmep_logcwmin));
	otus_write(sc, AR_MAC_REG_AC4_CW,		/* Special TXQ. */
	    EXP2(edca[WME_AC_VO].wmep_logcwmax) << 16 |
	    EXP2(edca[WME_AC_VO].wmep_logcwmin));

	/* Set AIFSN values. */
	otus_write(sc, AR_MAC_REG_AC1_AC0_AIFS,
	    AIFS(edca[WME_AC_VI].wmep_aifsn) << 24 |
	    AIFS(edca[WME_AC_BK].wmep_aifsn) << 12 |
	    AIFS(edca[WME_AC_BE].wmep_aifsn));
	otus_write(sc, AR_MAC_REG_AC3_AC2_AIFS,
	    AIFS(edca[WME_AC_VO].wmep_aifsn) << 16 |	/* Special TXQ. */
	    AIFS(edca[WME_AC_VO].wmep_aifsn) <<  4 |
	    AIFS(edca[WME_AC_VI].wmep_aifsn) >>  8);

	/* Set TXOP limit. */
	otus_write(sc, AR_MAC_REG_AC1_AC0_TXOP,
	    edca[WME_AC_BK].wmep_txopLimit << 16 |
	    edca[WME_AC_BE].wmep_txopLimit);
	otus_write(sc, AR_MAC_REG_AC3_AC2_TXOP,
	    edca[WME_AC_VO].wmep_txopLimit << 16 |
	    edca[WME_AC_VI].wmep_txopLimit);

	/* XXX ACK policy? */

	(void)otus_write_barrier(sc);

#undef AIFS
#undef EXP2
}