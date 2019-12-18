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
 int RSN_SELECTOR_LEN ; 
 int /*<<< orphan*/  RSN_SELECTOR_PUT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int WPA_CIPHER_CCMP ; 
 int WPA_CIPHER_NONE ; 
 int /*<<< orphan*/  WPA_CIPHER_SUITE_CCMP ; 
 int /*<<< orphan*/  WPA_CIPHER_SUITE_NONE ; 
 int /*<<< orphan*/  WPA_CIPHER_SUITE_TKIP ; 
 int WPA_CIPHER_TKIP ; 
 int /*<<< orphan*/  WPA_SELECTOR_LEN ; 

int wpa_cipher_put_suites(u8 *start, int ciphers)
{
	u8 *pos = start;

	if (ciphers & WPA_CIPHER_CCMP) {
		RSN_SELECTOR_PUT(pos, WPA_CIPHER_SUITE_CCMP);
		pos += WPA_SELECTOR_LEN;
	}
	if (ciphers & WPA_CIPHER_TKIP) {
		RSN_SELECTOR_PUT(pos, WPA_CIPHER_SUITE_TKIP);
		pos += WPA_SELECTOR_LEN;
	}
	if (ciphers & WPA_CIPHER_NONE) {
		RSN_SELECTOR_PUT(pos, WPA_CIPHER_SUITE_NONE);
		pos += WPA_SELECTOR_LEN;
	}

	return (pos - start) / RSN_SELECTOR_LEN;
}