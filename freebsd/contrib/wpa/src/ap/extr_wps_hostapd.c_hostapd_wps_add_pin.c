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
struct wps_add_pin_data {int timeout; scalar_t__ added; int /*<<< orphan*/ * uuid; int /*<<< orphan*/  pin_len; int /*<<< orphan*/  const* pin; int /*<<< orphan*/  const* addr; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int UUID_LEN ; 
 scalar_t__ hostapd_wps_for_each (struct hostapd_data*,int /*<<< orphan*/ ,struct wps_add_pin_data*) ; 
 scalar_t__ os_strcmp (char const*,char*) ; 
 int /*<<< orphan*/  os_strlen (char const*) ; 
 scalar_t__ uuid_str2bin (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wps_add_pin ; 

int hostapd_wps_add_pin(struct hostapd_data *hapd, const u8 *addr,
			const char *uuid, const char *pin, int timeout)
{
	u8 u[UUID_LEN];
	struct wps_add_pin_data data;

	data.addr = addr;
	data.uuid = u;
	data.pin = (const u8 *) pin;
	data.pin_len = os_strlen(pin);
	data.timeout = timeout;
	data.added = 0;

	if (os_strcmp(uuid, "any") == 0)
		data.uuid = NULL;
	else {
		if (uuid_str2bin(uuid, u))
			return -1;
		data.uuid = u;
	}
	if (hostapd_wps_for_each(hapd, wps_add_pin, &data) < 0)
		return -1;
	return data.added ? 0 : -1;
}