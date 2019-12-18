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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {TYPE_1__* global; } ;
struct p2p_srv_bonjour {int /*<<< orphan*/  list; struct wpabuf* resp; struct wpabuf* query; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p_srv_bonjour; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct p2p_srv_bonjour* os_zalloc (int) ; 
 int /*<<< orphan*/  wpas_p2p_sd_service_update (struct wpa_supplicant*) ; 

int wpas_p2p_service_add_bonjour(struct wpa_supplicant *wpa_s,
				 struct wpabuf *query, struct wpabuf *resp)
{
	struct p2p_srv_bonjour *bsrv;

	bsrv = os_zalloc(sizeof(*bsrv));
	if (bsrv == NULL)
		return -1;
	bsrv->query = query;
	bsrv->resp = resp;
	dl_list_add(&wpa_s->global->p2p_srv_bonjour, &bsrv->list);

	wpas_p2p_sd_service_update(wpa_s);
	return 0;
}