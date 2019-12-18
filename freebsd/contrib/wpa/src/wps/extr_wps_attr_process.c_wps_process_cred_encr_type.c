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
struct wps_credential {int /*<<< orphan*/  encr_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_process_cred_encr_type(struct wps_credential *cred,
				      const u8 *encr_type)
{
	if (encr_type == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: Credential did not include "
			   "Encryption Type");
		return -1;
	}

	cred->encr_type = WPA_GET_BE16(encr_type);
	wpa_printf(MSG_DEBUG, "WPS: Encryption Type: 0x%x",
		   cred->encr_type);

	return 0;
}