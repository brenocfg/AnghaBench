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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
struct rum_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
#define  IEEE80211_CIPHER_AES_CCM 130 
#define  IEEE80211_CIPHER_TKIP 129 
#define  IEEE80211_CIPHER_WEP 128 
 int /*<<< orphan*/  RT2573_MODE_AES_CCMP ; 
 int /*<<< orphan*/  RT2573_MODE_TKIP ; 
 int /*<<< orphan*/  RT2573_MODE_WEP104 ; 
 int /*<<< orphan*/  RT2573_MODE_WEP40 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static uint8_t
rum_crypto_mode(struct rum_softc *sc, u_int cipher, int keylen)
{
	switch (cipher) {
	case IEEE80211_CIPHER_WEP:
		return (keylen < 8 ? RT2573_MODE_WEP40 : RT2573_MODE_WEP104);
	case IEEE80211_CIPHER_TKIP:
		return RT2573_MODE_TKIP;
	case IEEE80211_CIPHER_AES_CCM:
		return RT2573_MODE_AES_CCMP;
	default:
		device_printf(sc->sc_dev, "unknown cipher %d\n", cipher);
		return 0;
	}
}