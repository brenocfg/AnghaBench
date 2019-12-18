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
struct wpa_supplicant {int /*<<< orphan*/  own_addr; } ;
struct wpa_ssid {int dummy; } ;
struct ibss_rsn {struct wpa_supplicant* wpa_s; } ;

/* Variables and functions */
 scalar_t__ ibss_rsn_auth_init_group (struct ibss_rsn*,int /*<<< orphan*/ ,struct wpa_ssid*) ; 
 int /*<<< orphan*/  ibss_rsn_deinit (struct ibss_rsn*) ; 
 struct ibss_rsn* os_zalloc (int) ; 

struct ibss_rsn * ibss_rsn_init(struct wpa_supplicant *wpa_s,
				struct wpa_ssid *ssid)
{
	struct ibss_rsn *ibss_rsn;

	ibss_rsn = os_zalloc(sizeof(*ibss_rsn));
	if (ibss_rsn == NULL)
		return NULL;
	ibss_rsn->wpa_s = wpa_s;

	if (ibss_rsn_auth_init_group(ibss_rsn, wpa_s->own_addr, ssid) < 0) {
		ibss_rsn_deinit(ibss_rsn);
		return NULL;
	}

	return ibss_rsn;
}