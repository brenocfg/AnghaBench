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
typedef  int /*<<< orphan*/  u8 ;
struct wps_registrar {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* pin_needed_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wps_device_data const*) ;} ;
struct wps_device_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wps_device_data const*) ; 

__attribute__((used)) static void wps_cb_pin_needed(struct wps_registrar *reg, const u8 *uuid_e,
			      const struct wps_device_data *dev)
{
	if (reg->pin_needed_cb == NULL)
		return;

	reg->pin_needed_cb(reg->cb_ctx, uuid_e, dev);
}