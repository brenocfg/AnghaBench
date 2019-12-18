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
struct TYPE_2__ {int ievent; char* ifname; } ;
union wpa_event_data {TYPE_1__ interface_status; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wpa_priv_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIVSEP_EVENT_INTERFACE_STATUS ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  wpa_priv_send_event (struct wpa_priv_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void wpa_priv_send_interface_status(struct wpa_priv_interface *iface,
					   union wpa_event_data *data)
{
	int ievent;
	size_t len, maxlen;
	u8 *buf;
	char *ifname;

	if (data == NULL)
		return;

	ievent = data->interface_status.ievent;
	maxlen = sizeof(data->interface_status.ifname);
	ifname = data->interface_status.ifname;
	for (len = 0; len < maxlen && ifname[len]; len++)
		;

	buf = os_malloc(sizeof(int) + len);
	if (buf == NULL)
		return;

	os_memcpy(buf, &ievent, sizeof(int));
	os_memcpy(buf + sizeof(int), ifname, len);

	wpa_priv_send_event(iface, PRIVSEP_EVENT_INTERFACE_STATUS,
			    buf, sizeof(int) + len);

	os_free(buf);

}