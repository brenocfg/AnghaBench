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
struct wpa_ssid {scalar_t__* wep_key_len; int /*<<< orphan*/ * wep_key; } ;

/* Variables and functions */
 char* wpa_config_write_string (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static char * wpa_config_write_wep_key(struct wpa_ssid *ssid, int idx)
{
	if (ssid->wep_key_len[idx] == 0)
		return NULL;
	return wpa_config_write_string(ssid->wep_key[idx],
				       ssid->wep_key_len[idx]);
}