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
typedef  scalar_t__ uint32_t ;
struct ieee80211com {int ic_cryptocaps; } ;
struct ndis_softc {struct ieee80211com ndis_ic; } ;
typedef  int /*<<< orphan*/  save ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int ENODEV ; 
 int ENOTSUP ; 
 int IEEE80211_CRYPTO_AES_CCM ; 
 int IEEE80211_CRYPTO_TKIP ; 
 int IEEE80211_CRYPTO_WEP ; 
 scalar_t__ NDIS_80211_WEPSTAT_ENC1ENABLED ; 
 scalar_t__ NDIS_80211_WEPSTAT_ENC2ENABLED ; 
 scalar_t__ NDIS_80211_WEPSTAT_ENC3ENABLED ; 
 int /*<<< orphan*/  OID_802_11_ENCRYPTION_STATUS ; 
 int WPA_CSE_CCMP ; 
 int WPA_CSE_TKIP ; 
 int WPA_CSE_WEP104 ; 
 int WPA_CSE_WEP40 ; 
 int ndis_get_info (struct ndis_softc*,int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int ndis_set_info (struct ndis_softc*,int /*<<< orphan*/ ,scalar_t__*,int*) ; 

__attribute__((used)) static int
ndis_set_cipher(struct ndis_softc *sc, int cipher)
{
	struct ieee80211com	*ic = &sc->ndis_ic;
	int			rval = 0, len;
	uint32_t		arg, save;

	len = sizeof(arg);

	if (cipher == WPA_CSE_WEP40 || cipher == WPA_CSE_WEP104) {
		if (!(ic->ic_cryptocaps & IEEE80211_CRYPTO_WEP))
			return (ENOTSUP);
		arg = NDIS_80211_WEPSTAT_ENC1ENABLED;
	}

	if (cipher == WPA_CSE_TKIP) {
		if (!(ic->ic_cryptocaps & IEEE80211_CRYPTO_TKIP))
			return (ENOTSUP);
		arg = NDIS_80211_WEPSTAT_ENC2ENABLED;
	}

	if (cipher == WPA_CSE_CCMP) {
		if (!(ic->ic_cryptocaps & IEEE80211_CRYPTO_AES_CCM))
			return (ENOTSUP);
		arg = NDIS_80211_WEPSTAT_ENC3ENABLED;
	}

	DPRINTF(("Setting cipher to %d\n", arg));
	save = arg;
	rval = ndis_set_info(sc, OID_802_11_ENCRYPTION_STATUS, &arg, &len);

	if (rval)
		return (rval);

	/* Check that the cipher was set correctly. */

	len = sizeof(save);
	rval = ndis_get_info(sc, OID_802_11_ENCRYPTION_STATUS, &arg, &len);

	if (rval != 0 || arg != save)
		return (ENODEV);

	return (0);
}