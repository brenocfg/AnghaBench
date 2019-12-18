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
struct wpa_config {int dummy; } ;
struct global_parse_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int eap_peer_method_load (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wpa_config_process_load_dynamic_eap(
	const struct global_parse_data *data, struct wpa_config *config,
	int line, const char *so)
{
	int ret;
	wpa_printf(MSG_DEBUG, "load_dynamic_eap=%s", so);
	ret = eap_peer_method_load(so);
	if (ret == -2) {
		wpa_printf(MSG_DEBUG, "This EAP type was already loaded - not "
			   "reloading.");
	} else if (ret) {
		wpa_printf(MSG_ERROR, "Line %d: Failed to load dynamic EAP "
			   "method '%s'.", line, so);
		return -1;
	}

	return 0;
}