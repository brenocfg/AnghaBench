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
typedef  enum wpa_alg { ____Placeholder_wpa_alg } wpa_alg ;

/* Variables and functions */
 int WPA_ALG_BIP_CMAC_256 ; 
 int WPA_ALG_BIP_GMAC_128 ; 
 int WPA_ALG_BIP_GMAC_256 ; 
 int WPA_ALG_CCMP ; 
 int WPA_ALG_CCMP_256 ; 
 int WPA_ALG_GCMP ; 
 int WPA_ALG_GCMP_256 ; 
 int WPA_ALG_IGTK ; 
 int WPA_ALG_NONE ; 
 int WPA_ALG_TKIP ; 
#define  WPA_CIPHER_AES_128_CMAC 136 
#define  WPA_CIPHER_BIP_CMAC_256 135 
#define  WPA_CIPHER_BIP_GMAC_128 134 
#define  WPA_CIPHER_BIP_GMAC_256 133 
#define  WPA_CIPHER_CCMP 132 
#define  WPA_CIPHER_CCMP_256 131 
#define  WPA_CIPHER_GCMP 130 
#define  WPA_CIPHER_GCMP_256 129 
#define  WPA_CIPHER_TKIP 128 

enum wpa_alg wpa_cipher_to_alg(int cipher)
{
	switch (cipher) {
	case WPA_CIPHER_CCMP_256:
		return WPA_ALG_CCMP_256;
	case WPA_CIPHER_GCMP_256:
		return WPA_ALG_GCMP_256;
	case WPA_CIPHER_CCMP:
		return WPA_ALG_CCMP;
	case WPA_CIPHER_GCMP:
		return WPA_ALG_GCMP;
	case WPA_CIPHER_TKIP:
		return WPA_ALG_TKIP;
	case WPA_CIPHER_AES_128_CMAC:
		return WPA_ALG_IGTK;
	case WPA_CIPHER_BIP_GMAC_128:
		return WPA_ALG_BIP_GMAC_128;
	case WPA_CIPHER_BIP_GMAC_256:
		return WPA_ALG_BIP_GMAC_256;
	case WPA_CIPHER_BIP_CMAC_256:
		return WPA_ALG_BIP_CMAC_256;
	}
	return WPA_ALG_NONE;
}