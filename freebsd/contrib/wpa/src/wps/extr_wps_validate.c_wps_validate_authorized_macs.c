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

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wps_validate_authorized_macs(const u8 *authorized_macs, size_t len,
					int mandatory)
{
	if (authorized_macs == NULL) {
		if (mandatory) {
			wpa_printf(MSG_INFO, "WPS-STRICT: Authorized MACs "
				   "attribute missing");
			return -1;
		}
		return 0;
	}
	if (len > 30 && (len % ETH_ALEN) != 0) {
		wpa_hexdump(MSG_INFO, "WPS-STRICT: Invalid Authorized "
			    "MACs attribute value", authorized_macs, len);
		return -1;
	}
	return 0;
}