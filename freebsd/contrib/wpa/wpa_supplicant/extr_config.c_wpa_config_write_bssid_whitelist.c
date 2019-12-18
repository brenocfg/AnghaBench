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
struct wpa_ssid {int /*<<< orphan*/  num_bssid_whitelist; int /*<<< orphan*/  bssid_whitelist; } ;
struct parse_data {int dummy; } ;

/* Variables and functions */
 char* wpa_config_write_addr_list (struct parse_data const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char * wpa_config_write_bssid_whitelist(const struct parse_data *data,
					       struct wpa_ssid *ssid)
{
	return wpa_config_write_addr_list(data, ssid->bssid_whitelist,
					  ssid->num_bssid_whitelist,
					  "bssid_whitelist");
}