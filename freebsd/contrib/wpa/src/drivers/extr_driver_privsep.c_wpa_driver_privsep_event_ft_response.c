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
struct TYPE_2__ {size_t ies_len; int /*<<< orphan*/ * ies; int /*<<< orphan*/ * target_ap; int /*<<< orphan*/  ft_action; } ;
union wpa_event_data {TYPE_1__ ft_ies; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  EVENT_FT_RESPONSE ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_supplicant_event (void*,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static void wpa_driver_privsep_event_ft_response(void *ctx, u8 *buf,
						 size_t len)
{
	union wpa_event_data data;

	if (len < sizeof(int) + ETH_ALEN)
		return;

	os_memset(&data, 0, sizeof(data));
	os_memcpy(&data.ft_ies.ft_action, buf, sizeof(int));
	os_memcpy(data.ft_ies.target_ap, buf + sizeof(int), ETH_ALEN);
	data.ft_ies.ies = buf + sizeof(int) + ETH_ALEN;
	data.ft_ies.ies_len = len - sizeof(int) - ETH_ALEN;
	wpa_supplicant_event(ctx, EVENT_FT_RESPONSE, &data);
}