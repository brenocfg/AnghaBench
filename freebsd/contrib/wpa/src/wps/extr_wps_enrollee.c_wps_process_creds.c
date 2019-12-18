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
typedef  int /*<<< orphan*/  u16 ;
struct wps_data {TYPE_1__* wps; } ;
struct TYPE_2__ {scalar_t__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int wps_process_cred_e (struct wps_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wps_process_creds(struct wps_data *wps, const u8 *cred[],
			     u16 cred_len[], unsigned int num_cred, int wps2)
{
	size_t i;
	int ok = 0;

	if (wps->wps->ap)
		return 0;

	if (num_cred == 0) {
		wpa_printf(MSG_DEBUG, "WPS: No Credential attributes "
			   "received");
		return -1;
	}

	for (i = 0; i < num_cred; i++) {
		int res;
		res = wps_process_cred_e(wps, cred[i], cred_len[i], wps2);
		if (res == 0)
			ok++;
		else if (res == -2)
			wpa_printf(MSG_DEBUG, "WPS: WEP credential skipped");
		else
			return -1;
	}

	if (ok == 0) {
		wpa_printf(MSG_DEBUG, "WPS: No valid Credential attribute "
			   "received");
		return -1;
	}

	return 0;
}