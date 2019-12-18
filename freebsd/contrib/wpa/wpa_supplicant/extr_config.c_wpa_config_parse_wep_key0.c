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
struct wpa_ssid {int /*<<< orphan*/ * wep_key_len; int /*<<< orphan*/ * wep_key; } ;
struct parse_data {int dummy; } ;

/* Variables and functions */
 int wpa_config_parse_wep_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_config_parse_wep_key0(const struct parse_data *data,
				     struct wpa_ssid *ssid, int line,
				     const char *value)
{
	return wpa_config_parse_wep_key(ssid->wep_key[0],
					&ssid->wep_key_len[0], line,
					value, 0);
}