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
typedef  int u_long ;
struct iwi_softc {int /*<<< orphan*/  sc_linkqual; } ;
struct iwi_notif_link_quality {int dummy; } ;
struct ifreq {int dummy; } ;
struct ieee80211com {struct iwi_softc* ic_softc; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  IWI_LOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  IWI_LOCK_DECL ; 
 int /*<<< orphan*/  IWI_UNLOCK (struct iwi_softc*) ; 
#define  SIOCGIWISTATS 129 
#define  SIOCZIWISTATS 128 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifr_data_get_ptr (struct ifreq*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwi_ioctl(struct ieee80211com *ic, u_long cmd, void *data)
{
	struct ifreq *ifr = data;
	struct iwi_softc *sc = ic->ic_softc;
	int error;
	IWI_LOCK_DECL;

	IWI_LOCK(sc);
	switch (cmd) {
	case SIOCGIWISTATS:
		/* XXX validate permissions/memory/etc? */
		error = copyout(&sc->sc_linkqual, ifr_data_get_ptr(ifr),
		    sizeof(struct iwi_notif_link_quality));
		break;
	case SIOCZIWISTATS:
		memset(&sc->sc_linkqual, 0,
		    sizeof(struct iwi_notif_link_quality));
		error = 0;
		break;
	default:
		error = ENOTTY;
		break;
	}
	IWI_UNLOCK(sc);

	return (error);
}