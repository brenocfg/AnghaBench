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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ os_memcmp (char const*,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ os_strlen (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dpp_pkex_identifier_match(const u8 *attr_id, u16 attr_id_len,
				     const char *identifier)
{
	if (!attr_id && identifier) {
		wpa_printf(MSG_DEBUG,
			   "DPP: No PKEX code identifier received, but expected one");
		return 0;
	}

	if (attr_id && !identifier) {
		wpa_printf(MSG_DEBUG,
			   "DPP: PKEX code identifier received, but not expecting one");
		return 0;
	}

	if (attr_id && identifier &&
	    (os_strlen(identifier) != attr_id_len ||
	     os_memcmp(identifier, attr_id, attr_id_len) != 0)) {
		wpa_printf(MSG_DEBUG, "DPP: PKEX code identifier mismatch");
		return 0;
	}

	return 1;
}