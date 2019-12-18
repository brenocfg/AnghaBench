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
struct TYPE_2__ {int /*<<< orphan*/  ies_len; int /*<<< orphan*/  ies; int /*<<< orphan*/  status_code; int /*<<< orphan*/  auth_transaction; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  bssid; int /*<<< orphan*/  peer; } ;
union wpa_event_data {TYPE_1__ auth; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wpa_priv_interface {int dummy; } ;
struct privsep_event_auth {int /*<<< orphan*/  ies_len; int /*<<< orphan*/  status_code; int /*<<< orphan*/  auth_transaction; int /*<<< orphan*/  auth_type; int /*<<< orphan*/ * bssid; int /*<<< orphan*/ * peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  PRIVSEP_EVENT_AUTH ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * os_zalloc (size_t) ; 
 int /*<<< orphan*/  wpa_priv_send_event (struct wpa_priv_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void wpa_priv_send_auth(struct wpa_priv_interface *iface,
			       union wpa_event_data *data)
{
	size_t buflen = sizeof(struct privsep_event_auth) + data->auth.ies_len;
	struct privsep_event_auth *auth;
	u8 *buf, *pos;

	buf = os_zalloc(buflen);
	if (buf == NULL)
		return;

	auth = (struct privsep_event_auth *) buf;
	pos = (u8 *) (auth + 1);

	os_memcpy(auth->peer, data->auth.peer, ETH_ALEN);
	os_memcpy(auth->bssid, data->auth.bssid, ETH_ALEN);
	auth->auth_type = data->auth.auth_type;
	auth->auth_transaction = data->auth.auth_transaction;
	auth->status_code = data->auth.status_code;
	if (data->auth.ies) {
		os_memcpy(pos, data->auth.ies, data->auth.ies_len);
		auth->ies_len = data->auth.ies_len;
	}

	wpa_priv_send_event(iface, PRIVSEP_EVENT_AUTH, buf, buflen);

	os_free(buf);
}