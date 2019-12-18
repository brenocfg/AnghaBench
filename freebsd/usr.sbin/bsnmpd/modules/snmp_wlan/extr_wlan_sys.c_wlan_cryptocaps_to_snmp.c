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

/* Variables and functions */
 int IEEE80211_CRYPTO_AES_CCM ; 
 int IEEE80211_CRYPTO_AES_OCB ; 
 int IEEE80211_CRYPTO_CKIP ; 
 int IEEE80211_CRYPTO_TKIP ; 
 int IEEE80211_CRYPTO_TKIPMIC ; 
 int IEEE80211_CRYPTO_WEP ; 
 int wlanCryptoCaps_aes ; 
 int wlanCryptoCaps_aesCcm ; 
 int wlanCryptoCaps_ckip ; 
 int wlanCryptoCaps_tkip ; 
 int wlanCryptoCaps_tkipMic ; 
 int wlanCryptoCaps_wep ; 

__attribute__((used)) static uint32_t
wlan_cryptocaps_to_snmp(uint32_t ccaps)
{
	uint32_t scaps = 0;

#if NOT_YET
	if ((ccaps & IEEE80211_CRYPTO_WEP) != 0)
		scaps |= (0x1 << wlanCryptoCaps_wep);
	if ((ccaps & IEEE80211_CRYPTO_TKIP) != 0)
		scaps |= (0x1 << wlanCryptoCaps_tkip);
	if ((ccaps & IEEE80211_CRYPTO_AES_OCB) != 0)
		scaps |= (0x1 << wlanCryptoCaps_aes);
	if ((ccaps & IEEE80211_CRYPTO_AES_CCM) != 0)
		scaps |= (0x1 << wlanCryptoCaps_aesCcm);
	if ((ccaps & IEEE80211_CRYPTO_TKIPMIC) != 0)
		scaps |= (0x1 << wlanCryptoCaps_tkipMic);
	if ((ccaps & IEEE80211_CRYPTO_CKIP) != 0)
		scaps |= (0x1 << wlanCryptoCaps_ckip);
#else /* !NOT_YET */
	scaps = ccaps;
#endif
	return (scaps);
}