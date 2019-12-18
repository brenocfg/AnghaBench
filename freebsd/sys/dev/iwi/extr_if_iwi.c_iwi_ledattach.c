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
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct iwi_softc {int sc_ledstate; int sc_ledidle; int sc_ledpin; int sc_nictype; int sc_softled; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ledtimer; scalar_t__ sc_blinking; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  IWI_EEPROM_NIC ; 
 int IWI_RST_LED_ACTIVITY ; 
 int IWI_RST_LED_ASSOCIATED ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct iwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int hz ; 
 int iwi_read_prom_word (struct iwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwi_sysctl_softled ; 

__attribute__((used)) static void
iwi_ledattach(struct iwi_softc *sc)
{
	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(sc->sc_dev);
	struct sysctl_oid *tree = device_get_sysctl_tree(sc->sc_dev);

	sc->sc_blinking = 0;
	sc->sc_ledstate = 1;
	sc->sc_ledidle = (2700*hz)/1000;	/* 2.7sec */
	callout_init_mtx(&sc->sc_ledtimer, &sc->sc_mtx, 0);

	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		"softled", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
		iwi_sysctl_softled, "I", "enable/disable software LED support");
	SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		"ledpin", CTLFLAG_RW, &sc->sc_ledpin, 0,
		"pin setting to turn activity LED on");
	SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		"ledidle", CTLFLAG_RW, &sc->sc_ledidle, 0,
		"idle time for inactivity LED (ticks)");
	/* XXX for debugging */
	SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		"nictype", CTLFLAG_RD, &sc->sc_nictype, 0,
		"NIC type from EEPROM");

	sc->sc_ledpin = IWI_RST_LED_ACTIVITY;
	sc->sc_softled = 1;

	sc->sc_nictype = (iwi_read_prom_word(sc, IWI_EEPROM_NIC) >> 8) & 0xff;
	if (sc->sc_nictype == 1) {
		/*
		 * NB: led's are reversed.
		 */
		sc->sc_ledpin = IWI_RST_LED_ASSOCIATED;
	}
}