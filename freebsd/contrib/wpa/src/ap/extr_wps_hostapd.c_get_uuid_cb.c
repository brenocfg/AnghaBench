#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_iface {size_t num_bss; struct hostapd_data** bss; } ;
struct hostapd_data {TYPE_2__* wps; TYPE_1__* conf; } ;
struct TYPE_4__ {int /*<<< orphan*/ * uuid; } ;
struct TYPE_3__ {int /*<<< orphan*/  wps_independent; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_nil_uuid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_uuid_cb(struct hostapd_iface *iface, void *ctx)
{
	const u8 **uuid = ctx;
	size_t j;

	if (iface == NULL)
		return 0;
	for (j = 0; j < iface->num_bss; j++) {
		struct hostapd_data *hapd = iface->bss[j];
		if (hapd->wps && !hapd->conf->wps_independent &&
		    !is_nil_uuid(hapd->wps->uuid)) {
			*uuid = hapd->wps->uuid;
			return 1;
		}
	}

	return 0;
}