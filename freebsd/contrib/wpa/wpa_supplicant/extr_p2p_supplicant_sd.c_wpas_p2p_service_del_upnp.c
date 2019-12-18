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
struct wpa_supplicant {int dummy; } ;
struct p2p_srv_upnp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_p2p_sd_service_update (struct wpa_supplicant*) ; 
 struct p2p_srv_upnp* wpas_p2p_service_get_upnp (struct wpa_supplicant*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  wpas_p2p_srv_upnp_free (struct p2p_srv_upnp*) ; 

int wpas_p2p_service_del_upnp(struct wpa_supplicant *wpa_s, u8 version,
			      const char *service)
{
	struct p2p_srv_upnp *usrv;

	usrv = wpas_p2p_service_get_upnp(wpa_s, version, service);
	if (usrv == NULL)
		return -1;
	wpas_p2p_srv_upnp_free(usrv);
	wpas_p2p_sd_service_update(wpa_s);
	return 0;
}