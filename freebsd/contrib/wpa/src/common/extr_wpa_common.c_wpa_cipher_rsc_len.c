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

/* Variables and functions */
#define  WPA_CIPHER_CCMP 132 
#define  WPA_CIPHER_CCMP_256 131 
#define  WPA_CIPHER_GCMP 130 
#define  WPA_CIPHER_GCMP_256 129 
#define  WPA_CIPHER_TKIP 128 

int wpa_cipher_rsc_len(int cipher)
{
	switch (cipher) {
	case WPA_CIPHER_CCMP_256:
	case WPA_CIPHER_GCMP_256:
	case WPA_CIPHER_CCMP:
	case WPA_CIPHER_GCMP:
	case WPA_CIPHER_TKIP:
		return 6;
	}

	return 0;
}