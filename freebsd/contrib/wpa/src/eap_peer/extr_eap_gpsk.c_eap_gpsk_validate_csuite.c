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
struct eap_gpsk_data {int vendor; int specifier; } ;
struct eap_gpsk_csuite {int /*<<< orphan*/  specifier; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_GET_BE16 (int /*<<< orphan*/ ) ; 
 int WPA_GET_BE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static const u8 * eap_gpsk_validate_csuite(struct eap_gpsk_data *data,
					   const u8 *pos, const u8 *end)
{
	int vendor, specifier;
	const struct eap_gpsk_csuite *csuite;

	if (pos == NULL)
		return NULL;

	if (end - pos < (int) sizeof(*csuite)) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Message too short for "
			   "CSuite_Sel");
		return NULL;
	}
	csuite = (const struct eap_gpsk_csuite *) pos;
	vendor = WPA_GET_BE32(csuite->vendor);
	specifier = WPA_GET_BE16(csuite->specifier);
	pos += sizeof(*csuite);
	if (vendor != data->vendor || specifier != data->specifier) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: CSuite_Sel (%d:%d) does not "
			   "match with the one sent in GPSK-2 (%d:%d)",
			   vendor, specifier, data->vendor, data->specifier);
		return NULL;
	}

	return pos;
}