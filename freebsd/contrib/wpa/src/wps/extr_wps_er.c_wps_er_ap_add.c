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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct wps_er_ap {int /*<<< orphan*/ * location; int /*<<< orphan*/  http; TYPE_1__ addr; int /*<<< orphan*/  uuid; int /*<<< orphan*/  list; scalar_t__ id; struct wps_er* er; int /*<<< orphan*/  sta; } ;
struct wps_er {int /*<<< orphan*/  ap; scalar_t__ next_ap_id; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_UUID_LEN ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wps_er*,struct wps_er_ap*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wps_er*,struct wps_er_ap*) ; 
 int /*<<< orphan*/  http_client_url (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct wps_er_ap*) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_1__) ; 
 int /*<<< orphan*/  os_free (struct wps_er_ap*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * os_strdup (char const*) ; 
 struct wps_er_ap* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wps_er_ap* wps_er_ap_get (struct wps_er*,struct in_addr*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wps_er_ap_timeout ; 
 int /*<<< orphan*/  wps_er_http_dev_desc_cb ; 

void wps_er_ap_add(struct wps_er *er, const u8 *uuid, struct in_addr *addr,
		   const char *location, int max_age)
{
	struct wps_er_ap *ap;

	ap = wps_er_ap_get(er, addr, uuid, NULL);
	if (ap) {
		/* Update advertisement timeout */
		eloop_cancel_timeout(wps_er_ap_timeout, er, ap);
		eloop_register_timeout(max_age, 0, wps_er_ap_timeout, er, ap);
		return;
	}

	ap = os_zalloc(sizeof(*ap));
	if (ap == NULL)
		return;
	dl_list_init(&ap->sta);
	ap->er = er;
	ap->id = ++er->next_ap_id;
	ap->location = os_strdup(location);
	if (ap->location == NULL) {
		os_free(ap);
		return;
	}
	dl_list_add(&er->ap, &ap->list);

	ap->addr.s_addr = addr->s_addr;
	os_memcpy(ap->uuid, uuid, WPS_UUID_LEN);
	eloop_register_timeout(max_age, 0, wps_er_ap_timeout, er, ap);

	wpa_printf(MSG_DEBUG, "WPS ER: Added AP entry for %s (%s)",
		   inet_ntoa(ap->addr), ap->location);

	/* Fetch device description */
	ap->http = http_client_url(ap->location, NULL, 10000,
				   wps_er_http_dev_desc_cb, ap);
}