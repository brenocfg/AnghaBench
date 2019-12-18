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
struct wpa_supplicant {int drv_flags; TYPE_1__* conf; } ;
struct TYPE_2__ {scalar_t__ key_mgmt_offload; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_ALG_PMK ; 
 int WPA_DRIVER_FLAGS_KEY_MGMT_OFFLOAD ; 
 int wpa_drv_set_key (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int wpa_supplicant_key_mgmt_set_pmk(void *ctx, const u8 *pmk,
					   size_t pmk_len)
{
	struct wpa_supplicant *wpa_s = ctx;

	if (wpa_s->conf->key_mgmt_offload &&
	    (wpa_s->drv_flags & WPA_DRIVER_FLAGS_KEY_MGMT_OFFLOAD))
		return wpa_drv_set_key(wpa_s, WPA_ALG_PMK, NULL, 0, 0,
				       NULL, 0, pmk, pmk_len);
	else
		return 0;
}