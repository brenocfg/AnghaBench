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
struct TYPE_2__ {int req_ies_len; int resp_ies_len; int beacon_ies_len; int* req_ies; int* resp_ies; int* beacon_ies; } ;
union wpa_event_data {TYPE_1__ assoc_info; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wpa_priv_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  wpa_priv_send_event (struct wpa_priv_interface*,int,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void wpa_priv_send_assoc(struct wpa_priv_interface *iface, int event,
				union wpa_event_data *data)
{
	size_t buflen = 3 * sizeof(int);
	u8 *buf, *pos;
	int len;

	if (data) {
		buflen += data->assoc_info.req_ies_len +
			data->assoc_info.resp_ies_len +
			data->assoc_info.beacon_ies_len;
	}

	buf = os_malloc(buflen);
	if (buf == NULL)
		return;

	pos = buf;

	if (data && data->assoc_info.req_ies) {
		len = data->assoc_info.req_ies_len;
		os_memcpy(pos, &len, sizeof(int));
		pos += sizeof(int);
		os_memcpy(pos, data->assoc_info.req_ies, len);
		pos += len;
	} else {
		len = 0;
		os_memcpy(pos, &len, sizeof(int));
		pos += sizeof(int);
	}

	if (data && data->assoc_info.resp_ies) {
		len = data->assoc_info.resp_ies_len;
		os_memcpy(pos, &len, sizeof(int));
		pos += sizeof(int);
		os_memcpy(pos, data->assoc_info.resp_ies, len);
		pos += len;
	} else {
		len = 0;
		os_memcpy(pos, &len, sizeof(int));
		pos += sizeof(int);
	}

	if (data && data->assoc_info.beacon_ies) {
		len = data->assoc_info.beacon_ies_len;
		os_memcpy(pos, &len, sizeof(int));
		pos += sizeof(int);
		os_memcpy(pos, data->assoc_info.beacon_ies, len);
		pos += len;
	} else {
		len = 0;
		os_memcpy(pos, &len, sizeof(int));
		pos += sizeof(int);
	}

	wpa_priv_send_event(iface, event, buf, buflen);

	os_free(buf);
}