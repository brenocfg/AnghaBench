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
struct TYPE_2__ {size_t ies_len; int /*<<< orphan*/ * ies; int /*<<< orphan*/  status_code; int /*<<< orphan*/  auth_transaction; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  bssid; int /*<<< orphan*/  peer; } ;
union wpa_event_data {TYPE_1__ auth; } ;
typedef  int /*<<< orphan*/  u8 ;
struct privsep_event_auth {int ies_len; int /*<<< orphan*/  status_code; int /*<<< orphan*/  auth_transaction; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  bssid; int /*<<< orphan*/  peer; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  EVENT_AUTH ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_supplicant_event (void*,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static void wpa_driver_privsep_event_auth(void *ctx, u8 *buf, size_t len)
{
	union wpa_event_data data;
	struct privsep_event_auth *auth;

	os_memset(&data, 0, sizeof(data));
	if (len < sizeof(*auth))
		return;
	auth = (struct privsep_event_auth *) buf;
	if (len < sizeof(*auth) + auth->ies_len)
		return;

	os_memcpy(data.auth.peer, auth->peer, ETH_ALEN);
	os_memcpy(data.auth.bssid, auth->bssid, ETH_ALEN);
	data.auth.auth_type = auth->auth_type;
	data.auth.auth_transaction = auth->auth_transaction;
	data.auth.status_code = auth->status_code;
	if (auth->ies_len) {
		data.auth.ies = (u8 *) (auth + 1);
		data.auth.ies_len = auth->ies_len;
	}

	wpa_supplicant_event(ctx, EVENT_AUTH, &data);
}