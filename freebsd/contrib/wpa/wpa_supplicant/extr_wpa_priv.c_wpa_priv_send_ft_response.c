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
struct TYPE_2__ {int ies_len; int /*<<< orphan*/ * ies; int /*<<< orphan*/ * target_ap; int /*<<< orphan*/  ft_action; } ;
union wpa_event_data {TYPE_1__ ft_ies; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wpa_priv_interface {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  PRIVSEP_EVENT_FT_RESPONSE ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_priv_send_event (struct wpa_priv_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void wpa_priv_send_ft_response(struct wpa_priv_interface *iface,
				      union wpa_event_data *data)
{
	size_t len;
	u8 *buf, *pos;

	if (data == NULL || data->ft_ies.ies == NULL)
		return;

	len = sizeof(int) + ETH_ALEN + data->ft_ies.ies_len;
	buf = os_malloc(len);
	if (buf == NULL)
		return;

	pos = buf;
	os_memcpy(pos, &data->ft_ies.ft_action, sizeof(int));
	pos += sizeof(int);
	os_memcpy(pos, data->ft_ies.target_ap, ETH_ALEN);
	pos += ETH_ALEN;
	os_memcpy(pos, data->ft_ies.ies, data->ft_ies.ies_len);

	wpa_priv_send_event(iface, PRIVSEP_EVENT_FT_RESPONSE, buf, len);

	os_free(buf);

}