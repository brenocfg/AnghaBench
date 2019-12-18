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
 int WPA_CIPHER_CCMP ; 
 int WPA_CIPHER_CCMP_256 ; 
 int WPA_CIPHER_GCMP ; 
 int WPA_CIPHER_GCMP_256 ; 
 int WPA_CIPHER_TKIP ; 

int wpa_cipher_valid_pairwise(int cipher)
{
	return cipher == WPA_CIPHER_CCMP_256 ||
		cipher == WPA_CIPHER_GCMP_256 ||
		cipher == WPA_CIPHER_CCMP ||
		cipher == WPA_CIPHER_GCMP ||
		cipher == WPA_CIPHER_TKIP;
}