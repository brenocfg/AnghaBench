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
struct wps_stop_reg_data {int /*<<< orphan*/  dev_pw_len; int /*<<< orphan*/  dev_pw; int /*<<< orphan*/  uuid_e; struct hostapd_data* current_hapd; } ;
struct hostapd_data {TYPE_1__* wps; } ;
struct TYPE_2__ {int /*<<< orphan*/  registrar; } ;

/* Variables and functions */
 int /*<<< orphan*/  wps_registrar_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_stop_registrar(struct hostapd_data *hapd, void *ctx)
{
	struct wps_stop_reg_data *data = ctx;
	if (hapd != data->current_hapd && hapd->wps != NULL)
		wps_registrar_complete(hapd->wps->registrar, data->uuid_e,
				       data->dev_pw, data->dev_pw_len);
	return 0;
}