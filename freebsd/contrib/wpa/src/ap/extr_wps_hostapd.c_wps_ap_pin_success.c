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
struct hostapd_data {scalar_t__ ap_pin_failures_consecutive; int /*<<< orphan*/  ap_pin_failures; int /*<<< orphan*/ * wps; TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ap_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int wps_ap_pin_success(struct hostapd_data *hapd, void *ctx)
{
	if (hapd->conf->ap_pin == NULL || hapd->wps == NULL)
		return 0;

	if (hapd->ap_pin_failures_consecutive == 0)
		return 0;

	wpa_printf(MSG_DEBUG, "WPS: Clear consecutive AP PIN failure counter "
		   "- total validation failures %u (%u consecutive)",
		   hapd->ap_pin_failures, hapd->ap_pin_failures_consecutive);
	hapd->ap_pin_failures_consecutive = 0;

	return 0;
}