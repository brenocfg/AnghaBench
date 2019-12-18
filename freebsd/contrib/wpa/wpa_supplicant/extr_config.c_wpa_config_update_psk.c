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
struct wpa_ssid {int psk_set; int /*<<< orphan*/  psk; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  passphrase; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  PMK_LEN ; 
 int /*<<< orphan*/  pbkdf2_sha1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wpa_config_update_psk(struct wpa_ssid *ssid)
{
#ifndef CONFIG_NO_PBKDF2
	pbkdf2_sha1(ssid->passphrase, ssid->ssid, ssid->ssid_len, 4096,
		    ssid->psk, PMK_LEN);
	wpa_hexdump_key(MSG_MSGDUMP, "PSK (from passphrase)",
			ssid->psk, PMK_LEN);
	ssid->psk_set = 1;
#endif /* CONFIG_NO_PBKDF2 */
}