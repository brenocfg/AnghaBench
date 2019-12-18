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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int EAP_TLV_VENDOR_SPECIFIC_TLV ; 
 scalar_t__ EAP_VENDOR_MICROSOFT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ WPA_GET_BE32 (int /*<<< orphan*/  const*) ; 
 struct wpabuf* tncc_build_soh (int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

struct wpabuf * tncc_process_soh_request(int ver, const u8 *data, size_t len)
{
	const u8 *pos;

	wpa_hexdump(MSG_DEBUG, "TNC: SoH Request", data, len);

	if (len < 12)
		return NULL;

	/* SoH Request */
	pos = data;

	/* TLV Type */
	if (WPA_GET_BE16(pos) != EAP_TLV_VENDOR_SPECIFIC_TLV)
		return NULL;
	pos += 2;

	/* Length */
	if (WPA_GET_BE16(pos) < 8)
		return NULL;
	pos += 2;

	/* Vendor_Id */
	if (WPA_GET_BE32(pos) != EAP_VENDOR_MICROSOFT)
		return NULL;
	pos += 4;

	/* TLV Type */
	if (WPA_GET_BE16(pos) != 0x02 /* SoH request TLV */)
		return NULL;

	wpa_printf(MSG_DEBUG, "TNC: SoH Request TLV received");

	return tncc_build_soh(2);
}