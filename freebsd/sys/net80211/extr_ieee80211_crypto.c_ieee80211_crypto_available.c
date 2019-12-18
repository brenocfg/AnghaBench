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
typedef  size_t u_int ;

/* Variables and functions */
 size_t IEEE80211_CIPHER_MAX ; 
 int /*<<< orphan*/ ** ciphers ; 

int
ieee80211_crypto_available(u_int cipher)
{
	return cipher < IEEE80211_CIPHER_MAX && ciphers[cipher] != NULL;
}