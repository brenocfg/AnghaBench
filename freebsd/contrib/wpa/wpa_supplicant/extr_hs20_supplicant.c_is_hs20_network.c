#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {TYPE_1__* conf; } ;
struct wpa_ssid {int key_mgmt; int pairwise_cipher; scalar_t__ proto; scalar_t__ parent_cred; } ;
struct wpa_bss {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hs20; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS20_IE_VENDOR_TYPE ; 
 int WPA_CIPHER_CCMP ; 
 int WPA_KEY_MGMT_IEEE8021X ; 
 scalar_t__ WPA_PROTO_RSN ; 
 int /*<<< orphan*/  wpa_bss_get_vendor_ie (struct wpa_bss*,int /*<<< orphan*/ ) ; 

int is_hs20_network(struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid,
		    struct wpa_bss *bss)
{
	if (!wpa_s->conf->hs20 || !ssid)
		return 0;

	if (ssid->parent_cred)
		return 1;

	if (bss && !wpa_bss_get_vendor_ie(bss, HS20_IE_VENDOR_TYPE))
		return 0;

	/*
	 * This may catch some non-Hotspot 2.0 cases, but it is safer to do that
	 * than cause Hotspot 2.0 connections without indication element getting
	 * added. Non-Hotspot 2.0 APs should ignore the unknown vendor element.
	 */

	if (!(ssid->key_mgmt & WPA_KEY_MGMT_IEEE8021X))
		return 0;
	if (!(ssid->pairwise_cipher & WPA_CIPHER_CCMP))
		return 0;
	if (ssid->proto != WPA_PROTO_RSN)
		return 0;

	return 1;
}