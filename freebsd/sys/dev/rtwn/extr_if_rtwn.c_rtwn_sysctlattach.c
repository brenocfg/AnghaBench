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
struct rtwn_softc {scalar_t__ sc_ht40; scalar_t__ sc_hwcrypto; scalar_t__ sc_ratectl_sysctl; scalar_t__ sc_ratectl; int /*<<< orphan*/  sc_debug; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RDTUN ; 
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int /*<<< orphan*/  OID_AUTO ; 
 scalar_t__ RTWN_CRYPTO_FULL ; 
 scalar_t__ RTWN_CRYPTO_MAX ; 
 scalar_t__ RTWN_CRYPTO_PAIR ; 
 scalar_t__ RTWN_RATECTL_FW ; 
 scalar_t__ RTWN_RATECTL_MAX ; 
 scalar_t__ RTWN_RATECTL_NET80211 ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U32 (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

void
rtwn_sysctlattach(struct rtwn_softc *sc)
{
	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(sc->sc_dev);
	struct sysctl_oid *tree = device_get_sysctl_tree(sc->sc_dev);

#if 1
	sc->sc_ht40 = 0;
	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "ht40", CTLFLAG_RDTUN, &sc->sc_ht40,
	    sc->sc_ht40, "Enable 40 MHz mode support");
#endif

#ifdef RTWN_DEBUG
	SYSCTL_ADD_U32(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "debug", CTLFLAG_RWTUN, &sc->sc_debug, sc->sc_debug,
	    "Control debugging printfs");
#endif

	sc->sc_hwcrypto = RTWN_CRYPTO_PAIR;
	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "hwcrypto", CTLFLAG_RDTUN, &sc->sc_hwcrypto,
	    sc->sc_hwcrypto, "Enable h/w crypto: "
	    "0 - disable, 1 - pairwise keys, 2 - all keys");
	if (sc->sc_hwcrypto >= RTWN_CRYPTO_MAX)
		sc->sc_hwcrypto = RTWN_CRYPTO_FULL;

	sc->sc_ratectl_sysctl = RTWN_RATECTL_NET80211;
	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "ratectl", CTLFLAG_RDTUN, &sc->sc_ratectl_sysctl,
	    sc->sc_ratectl_sysctl, "Select rate control mechanism: "
	    "0 - disabled, 1 - via net80211, 2 - via firmware");
	if (sc->sc_ratectl_sysctl >= RTWN_RATECTL_MAX)
		sc->sc_ratectl_sysctl = RTWN_RATECTL_FW;

	sc->sc_ratectl = sc->sc_ratectl_sysctl;
	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "ratectl_selected", CTLFLAG_RD, &sc->sc_ratectl,
	    sc->sc_ratectl,
	    "Currently selected rate control mechanism (by the driver)");
}