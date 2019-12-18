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
typedef  char u8 ;
struct wpabuf {int dummy; } ;
typedef  int /*<<< orphan*/  correlation_id ;

/* Variables and functions */
 int EAP_TLV_VENDOR_SPECIFIC_TLV ; 
 int EAP_VENDOR_MICROSOFT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SSOH_MS_CORRELATIONID ; 
 int SSOH_MS_MACHINENAME ; 
 int SSOH_MS_MACHINE_INVENTORY ; 
 int SSOH_MS_MACHINE_INVENTORY_EX ; 
 int SSOH_MS_PACKET_INFO ; 
 int SSOH_MS_QUARANTINE_STATE ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (char*,int) ; 
 scalar_t__ os_get_random (char*,int) ; 
 int os_strlen (char*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,char*,int) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 char* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * tncc_build_soh(int ver)
{
	struct wpabuf *buf;
	u8 *tlv_len, *tlv_len2, *outer_len, *inner_len, *ssoh_len, *end;
	u8 correlation_id[24];
	/* TODO: get correct name */
	char *machinename = "wpa_supplicant@w1.fi";

	if (os_get_random(correlation_id, sizeof(correlation_id)))
		return NULL;
	wpa_hexdump(MSG_DEBUG, "TNC: SoH Correlation ID",
		    correlation_id, sizeof(correlation_id));

	buf = wpabuf_alloc(200);
	if (buf == NULL)
		return NULL;

	/* Vendor-Specific TLV (Microsoft) - SoH */
	wpabuf_put_be16(buf, EAP_TLV_VENDOR_SPECIFIC_TLV); /* TLV Type */
	tlv_len = wpabuf_put(buf, 2); /* Length */
	wpabuf_put_be32(buf, EAP_VENDOR_MICROSOFT); /* Vendor_Id */
	wpabuf_put_be16(buf, 0x01); /* TLV Type - SoH TLV */
	tlv_len2 = wpabuf_put(buf, 2); /* Length */

	/* SoH Header */
	wpabuf_put_be16(buf, EAP_TLV_VENDOR_SPECIFIC_TLV); /* Outer Type */
	outer_len = wpabuf_put(buf, 2);
	wpabuf_put_be32(buf, EAP_VENDOR_MICROSOFT); /* IANA SMI Code */
	wpabuf_put_be16(buf, ver); /* Inner Type */
	inner_len = wpabuf_put(buf, 2);

	if (ver == 2) {
		/* SoH Mode Sub-Header */
		/* Outer Type */
		wpabuf_put_be16(buf, EAP_TLV_VENDOR_SPECIFIC_TLV);
		wpabuf_put_be16(buf, 4 + 24 + 1 + 1); /* Length */
		wpabuf_put_be32(buf, EAP_VENDOR_MICROSOFT); /* IANA SMI Code */
		/* Value: */
		wpabuf_put_data(buf, correlation_id, sizeof(correlation_id));
		wpabuf_put_u8(buf, 0x01); /* Intent Flag - Request */
		wpabuf_put_u8(buf, 0x00); /* Content-Type Flag */
	}

	/* SSoH TLV */
	/* System-Health-Id */
	wpabuf_put_be16(buf, 0x0002); /* Type */
	wpabuf_put_be16(buf, 4); /* Length */
	wpabuf_put_be32(buf, 79616);
	/* Vendor-Specific Attribute */
	wpabuf_put_be16(buf, EAP_TLV_VENDOR_SPECIFIC_TLV);
	ssoh_len = wpabuf_put(buf, 2);
	wpabuf_put_be32(buf, EAP_VENDOR_MICROSOFT); /* IANA SMI Code */

	/* MS-Packet-Info */
	wpabuf_put_u8(buf, SSOH_MS_PACKET_INFO);
	/* Note: IF-TNCCS-SOH v1.0 r8 claims this field to be:
	 * Reserved(4 bits) r(1 bit) Vers(3 bits), but Windows XP
	 * SP3 seems to be sending 0x11 for SSoH, i.e., r(request/response) bit
	 * would not be in the specified location.
	 * [MS-SOH] 4.0.2: Reserved(3 bits) r(1 bit) Vers(4 bits)
	 */
	wpabuf_put_u8(buf, 0x11); /* r=request, vers=1 */

	/* MS-Machine-Inventory */
	/* TODO: get correct values; 0 = not applicable for OS */
	wpabuf_put_u8(buf, SSOH_MS_MACHINE_INVENTORY);
	wpabuf_put_be32(buf, 0); /* osVersionMajor */
	wpabuf_put_be32(buf, 0); /* osVersionMinor */
	wpabuf_put_be32(buf, 0); /* osVersionBuild */
	wpabuf_put_be16(buf, 0); /* spVersionMajor */
	wpabuf_put_be16(buf, 0); /* spVersionMinor */
	wpabuf_put_be16(buf, 0); /* procArch */

	/* MS-MachineName */
	wpabuf_put_u8(buf, SSOH_MS_MACHINENAME);
	wpabuf_put_be16(buf, os_strlen(machinename) + 1);
	wpabuf_put_data(buf, machinename, os_strlen(machinename) + 1);

	/* MS-CorrelationId */
	wpabuf_put_u8(buf, SSOH_MS_CORRELATIONID);
	wpabuf_put_data(buf, correlation_id, sizeof(correlation_id));

	/* MS-Quarantine-State */
	wpabuf_put_u8(buf, SSOH_MS_QUARANTINE_STATE);
	wpabuf_put_be16(buf, 1); /* Flags: ExtState=0, f=0, qState=1 */
	wpabuf_put_be32(buf, 0xffffffff); /* ProbTime (hi) */
	wpabuf_put_be32(buf, 0xffffffff); /* ProbTime (lo) */
	wpabuf_put_be16(buf, 1); /* urlLenInBytes */
	wpabuf_put_u8(buf, 0); /* null termination for the url */

	/* MS-Machine-Inventory-Ex */
	wpabuf_put_u8(buf, SSOH_MS_MACHINE_INVENTORY_EX);
	wpabuf_put_be32(buf, 0); /* Reserved
				  * (note: Windows XP SP3 uses 0xdecafbad) */
	wpabuf_put_u8(buf, 1); /* ProductType: Client */

	/* Update SSoH Length */
	end = wpabuf_put(buf, 0);
	WPA_PUT_BE16(ssoh_len, end - ssoh_len - 2);

	/* TODO: SoHReportEntry TLV (zero or more) */

	/* Update length fields */
	end = wpabuf_put(buf, 0);
	WPA_PUT_BE16(tlv_len, end - tlv_len - 2);
	WPA_PUT_BE16(tlv_len2, end - tlv_len2 - 2);
	WPA_PUT_BE16(outer_len, end - outer_len - 2);
	WPA_PUT_BE16(inner_len, end - inner_len - 2);

	return buf;
}