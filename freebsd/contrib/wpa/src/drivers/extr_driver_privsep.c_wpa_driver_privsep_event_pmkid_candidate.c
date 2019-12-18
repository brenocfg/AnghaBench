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
union wpa_event_data {int /*<<< orphan*/  pmkid_candidate; } ;
typedef  int /*<<< orphan*/  u8 ;
struct pmkid_candidate {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_PMKID_CANDIDATE ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_supplicant_event (void*,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static void wpa_driver_privsep_event_pmkid_candidate(void *ctx, u8 *buf,
						     size_t len)
{
	union wpa_event_data data;

	if (len != sizeof(struct pmkid_candidate))
		return;

	os_memset(&data, 0, sizeof(data));
	os_memcpy(&data.pmkid_candidate, buf, len);
	wpa_supplicant_event(ctx, EVENT_PMKID_CANDIDATE, &data);
}