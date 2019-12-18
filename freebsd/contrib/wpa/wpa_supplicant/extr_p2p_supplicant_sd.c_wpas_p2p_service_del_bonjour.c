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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {int dummy; } ;
struct p2p_srv_bonjour {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_p2p_sd_service_update (struct wpa_supplicant*) ; 
 struct p2p_srv_bonjour* wpas_p2p_service_get_bonjour (struct wpa_supplicant*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpas_p2p_srv_bonjour_free (struct p2p_srv_bonjour*) ; 

int wpas_p2p_service_del_bonjour(struct wpa_supplicant *wpa_s,
				 const struct wpabuf *query)
{
	struct p2p_srv_bonjour *bsrv;

	bsrv = wpas_p2p_service_get_bonjour(wpa_s, query);
	if (bsrv == NULL)
		return -1;
	wpas_p2p_srv_bonjour_free(bsrv);
	wpas_p2p_sd_service_update(wpa_s);
	return 0;
}