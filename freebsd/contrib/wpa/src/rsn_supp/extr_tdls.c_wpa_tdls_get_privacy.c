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
struct wpa_sm {scalar_t__ pairwise_cipher; } ;

/* Variables and functions */
 scalar_t__ WPA_CIPHER_NONE ; 

__attribute__((used)) static int wpa_tdls_get_privacy(struct wpa_sm *sm)
{
	/*
	 * Get info needed from supplicant to check if the current BSS supports
	 * security. Other than OPEN mode, rest are considered secured
	 * WEP/WPA/WPA2 hence TDLS frames are processed for TPK handshake.
	 */
	return sm->pairwise_cipher != WPA_CIPHER_NONE;
}