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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {TYPE_1__* global; } ;
struct p2p_srv_upnp {int /*<<< orphan*/  list; int /*<<< orphan*/ * service; int /*<<< orphan*/  version; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p_srv_upnp; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct p2p_srv_upnp*) ; 
 int /*<<< orphan*/ * os_strdup (char const*) ; 
 struct p2p_srv_upnp* os_zalloc (int) ; 
 int /*<<< orphan*/  wpas_p2p_sd_service_update (struct wpa_supplicant*) ; 
 scalar_t__ wpas_p2p_service_get_upnp (struct wpa_supplicant*,int /*<<< orphan*/ ,char const*) ; 

int wpas_p2p_service_add_upnp(struct wpa_supplicant *wpa_s, u8 version,
			      const char *service)
{
	struct p2p_srv_upnp *usrv;

	if (wpas_p2p_service_get_upnp(wpa_s, version, service))
		return 0; /* Already listed */
	usrv = os_zalloc(sizeof(*usrv));
	if (usrv == NULL)
		return -1;
	usrv->version = version;
	usrv->service = os_strdup(service);
	if (usrv->service == NULL) {
		os_free(usrv);
		return -1;
	}
	dl_list_add(&wpa_s->global->p2p_srv_upnp, &usrv->list);

	wpas_p2p_sd_service_update(wpa_s);
	return 0;
}