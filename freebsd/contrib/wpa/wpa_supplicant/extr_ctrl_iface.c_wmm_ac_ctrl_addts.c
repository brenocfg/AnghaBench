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
struct wpa_supplicant {int dummy; } ;
struct wmm_ac_ts_setup_params {int tsid; int direction; int user_priority; int nominal_msdu_size; int mean_data_rate; int minimum_phy_rate; int surplus_bandwidth_allowance; int fixed_nominal_msdu; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WMM_TSPEC_DIRECTION_BI_DIRECTIONAL ; 
 int WMM_TSPEC_DIRECTION_DOWNLINK ; 
 int WMM_TSPEC_DIRECTION_UPLINK ; 
 scalar_t__ os_strcasecmp (char*,char*) ; 
 int sscanf (char*,char*,int*) ; 
 char* str_token (char*,char*,char**) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int wpas_wmm_ac_addts (struct wpa_supplicant*,struct wmm_ac_ts_setup_params*) ; 

__attribute__((used)) static int wmm_ac_ctrl_addts(struct wpa_supplicant *wpa_s, char *cmd)
{
	char *token, *context = NULL;
	struct wmm_ac_ts_setup_params params = {
		.tsid = 0xff,
		.direction = 0xff,
	};

	while ((token = str_token(cmd, " ", &context))) {
		if (sscanf(token, "tsid=%i", &params.tsid) == 1 ||
		    sscanf(token, "up=%i", &params.user_priority) == 1 ||
		    sscanf(token, "nominal_msdu_size=%i",
			   &params.nominal_msdu_size) == 1 ||
		    sscanf(token, "mean_data_rate=%i",
			   &params.mean_data_rate) == 1 ||
		    sscanf(token, "min_phy_rate=%i",
			   &params.minimum_phy_rate) == 1 ||
		    sscanf(token, "sba=%i",
			   &params.surplus_bandwidth_allowance) == 1)
			continue;

		if (os_strcasecmp(token, "downlink") == 0) {
			params.direction = WMM_TSPEC_DIRECTION_DOWNLINK;
		} else if (os_strcasecmp(token, "uplink") == 0) {
			params.direction = WMM_TSPEC_DIRECTION_UPLINK;
		} else if (os_strcasecmp(token, "bidi") == 0) {
			params.direction = WMM_TSPEC_DIRECTION_BI_DIRECTIONAL;
		} else if (os_strcasecmp(token, "fixed_nominal_msdu") == 0) {
			params.fixed_nominal_msdu = 1;
		} else {
			wpa_printf(MSG_DEBUG,
				   "CTRL: Invalid WMM_AC_ADDTS parameter: '%s'",
				   token);
			return -1;
		}

	}

	return wpas_wmm_ac_addts(wpa_s, &params);
}