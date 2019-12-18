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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  RSN_CIPHER_SUITE_AES_128_CMAC ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_BIP_CMAC_256 ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_BIP_GMAC_128 ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_BIP_GMAC_256 ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_CCMP ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_CCMP_256 ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_GCMP ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_GCMP_256 ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_NONE ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_NO_GROUP_ADDRESSED ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_TKIP ; 
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
 int /*<<< orphan*/  WPA_CIPHER_SUITE_CCMP ; 
 int /*<<< orphan*/  WPA_CIPHER_SUITE_NONE ; 
 int /*<<< orphan*/  WPA_CIPHER_SUITE_TKIP ; 
 int WPA_CIPHER_TKIP ; 
 int WPA_PROTO_RSN ; 

u32 wpa_cipher_to_suite(int proto, int cipher)
{
	if (cipher & WPA_CIPHER_CCMP_256)
		return RSN_CIPHER_SUITE_CCMP_256;
	if (cipher & WPA_CIPHER_GCMP_256)
		return RSN_CIPHER_SUITE_GCMP_256;
	if (cipher & WPA_CIPHER_CCMP)
		return (proto == WPA_PROTO_RSN ?
			RSN_CIPHER_SUITE_CCMP : WPA_CIPHER_SUITE_CCMP);
	if (cipher & WPA_CIPHER_GCMP)
		return RSN_CIPHER_SUITE_GCMP;
	if (cipher & WPA_CIPHER_TKIP)
		return (proto == WPA_PROTO_RSN ?
			RSN_CIPHER_SUITE_TKIP : WPA_CIPHER_SUITE_TKIP);
	if (cipher & WPA_CIPHER_NONE)
		return (proto == WPA_PROTO_RSN ?
			RSN_CIPHER_SUITE_NONE : WPA_CIPHER_SUITE_NONE);
	if (cipher & WPA_CIPHER_GTK_NOT_USED)
		return RSN_CIPHER_SUITE_NO_GROUP_ADDRESSED;
	if (cipher & WPA_CIPHER_AES_128_CMAC)
		return RSN_CIPHER_SUITE_AES_128_CMAC;
	if (cipher & WPA_CIPHER_BIP_GMAC_128)
		return RSN_CIPHER_SUITE_BIP_GMAC_128;
	if (cipher & WPA_CIPHER_BIP_GMAC_256)
		return RSN_CIPHER_SUITE_BIP_GMAC_256;
	if (cipher & WPA_CIPHER_BIP_CMAC_256)
		return RSN_CIPHER_SUITE_BIP_CMAC_256;
	return 0;
}