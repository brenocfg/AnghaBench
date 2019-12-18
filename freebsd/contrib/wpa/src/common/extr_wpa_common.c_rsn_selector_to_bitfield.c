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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ RSN_CIPHER_SUITE_AES_128_CMAC ; 
 scalar_t__ RSN_CIPHER_SUITE_BIP_CMAC_256 ; 
 scalar_t__ RSN_CIPHER_SUITE_BIP_GMAC_128 ; 
 scalar_t__ RSN_CIPHER_SUITE_BIP_GMAC_256 ; 
 scalar_t__ RSN_CIPHER_SUITE_CCMP ; 
 scalar_t__ RSN_CIPHER_SUITE_CCMP_256 ; 
 scalar_t__ RSN_CIPHER_SUITE_GCMP ; 
 scalar_t__ RSN_CIPHER_SUITE_GCMP_256 ; 
 scalar_t__ RSN_CIPHER_SUITE_NONE ; 
 scalar_t__ RSN_CIPHER_SUITE_NO_GROUP_ADDRESSED ; 
 scalar_t__ RSN_CIPHER_SUITE_TKIP ; 
 scalar_t__ RSN_SELECTOR_GET (int /*<<< orphan*/  const*) ; 
 int WPA_CIPHER_AES_128_CMAC ; 
 int WPA_CIPHER_BIP_CMAC_256 ; 
 int WPA_CIPHER_BIP_GMAC_128 ; 
 int WPA_CIPHER_BIP_GMAC_256 ; 
 int WPA_CIPHER_CCMP ; 
 int WPA_CIPHER_CCMP_256 ; 
 int WPA_CIPHER_GCMP ; 
 int WPA_CIPHER_GCMP_256 ; 
 int WPA_CIPHER_GTK_NOT_USED ; 
 int WPA_CIPHER_NONE ; 
 int WPA_CIPHER_TKIP ; 

__attribute__((used)) static int rsn_selector_to_bitfield(const u8 *s)
{
	if (RSN_SELECTOR_GET(s) == RSN_CIPHER_SUITE_NONE)
		return WPA_CIPHER_NONE;
	if (RSN_SELECTOR_GET(s) == RSN_CIPHER_SUITE_TKIP)
		return WPA_CIPHER_TKIP;
	if (RSN_SELECTOR_GET(s) == RSN_CIPHER_SUITE_CCMP)
		return WPA_CIPHER_CCMP;
#ifdef CONFIG_IEEE80211W
	if (RSN_SELECTOR_GET(s) == RSN_CIPHER_SUITE_AES_128_CMAC)
		return WPA_CIPHER_AES_128_CMAC;
#endif /* CONFIG_IEEE80211W */
	if (RSN_SELECTOR_GET(s) == RSN_CIPHER_SUITE_GCMP)
		return WPA_CIPHER_GCMP;
	if (RSN_SELECTOR_GET(s) == RSN_CIPHER_SUITE_CCMP_256)
		return WPA_CIPHER_CCMP_256;
	if (RSN_SELECTOR_GET(s) == RSN_CIPHER_SUITE_GCMP_256)
		return WPA_CIPHER_GCMP_256;
	if (RSN_SELECTOR_GET(s) == RSN_CIPHER_SUITE_BIP_GMAC_128)
		return WPA_CIPHER_BIP_GMAC_128;
	if (RSN_SELECTOR_GET(s) == RSN_CIPHER_SUITE_BIP_GMAC_256)
		return WPA_CIPHER_BIP_GMAC_256;
	if (RSN_SELECTOR_GET(s) == RSN_CIPHER_SUITE_BIP_CMAC_256)
		return WPA_CIPHER_BIP_CMAC_256;
	if (RSN_SELECTOR_GET(s) == RSN_CIPHER_SUITE_NO_GROUP_ADDRESSED)
		return WPA_CIPHER_GTK_NOT_USED;
	return 0;
}