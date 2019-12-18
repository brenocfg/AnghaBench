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
typedef  int u32 ;
typedef  int u16 ;
struct os_time {int /*<<< orphan*/  sec; } ;
struct eap_fast_pac {size_t a_id_len; size_t i_id_len; size_t a_id_info_len; int pac_type; int /*<<< orphan*/ * a_id_info; int /*<<< orphan*/ * i_id; int /*<<< orphan*/ * a_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
#define  PAC_TYPE_A_ID 132 
#define  PAC_TYPE_A_ID_INFO 131 
#define  PAC_TYPE_CRED_LIFETIME 130 
#define  PAC_TYPE_I_ID 129 
 int PAC_TYPE_MACHINE_AUTHENTICATION ; 
#define  PAC_TYPE_PAC_TYPE 128 
 int PAC_TYPE_TUNNEL_PAC ; 
 int PAC_TYPE_USER_AUTHORIZATION ; 
 int WPA_GET_BE16 (int /*<<< orphan*/ *) ; 
 int WPA_GET_BE32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_get_time (struct os_time*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int eap_fast_parse_pac_info(struct eap_fast_pac *entry, int type,
				   u8 *pos, size_t len)
{
	u16 pac_type;
	u32 lifetime;
	struct os_time now;

	switch (type & 0x7fff) {
	case PAC_TYPE_CRED_LIFETIME:
		if (len != 4) {
			wpa_hexdump(MSG_DEBUG, "EAP-FAST: PAC-Info - "
				    "Invalid CRED_LIFETIME length - ignored",
				    pos, len);
			return 0;
		}

		/*
		 * This is not currently saved separately in PAC files since
		 * the server can automatically initiate PAC update when
		 * needed. Anyway, the information is available from PAC-Info
		 * dump if it is needed for something in the future.
		 */
		lifetime = WPA_GET_BE32(pos);
		os_get_time(&now);
		wpa_printf(MSG_DEBUG, "EAP-FAST: PAC-Info - CRED_LIFETIME %d "
			   "(%d days)",
			   lifetime, (lifetime - (u32) now.sec) / 86400);
		break;
	case PAC_TYPE_A_ID:
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-FAST: PAC-Info - A-ID",
				  pos, len);
		entry->a_id = pos;
		entry->a_id_len = len;
		break;
	case PAC_TYPE_I_ID:
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-FAST: PAC-Info - I-ID",
				  pos, len);
		entry->i_id = pos;
		entry->i_id_len = len;
		break;
	case PAC_TYPE_A_ID_INFO:
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-FAST: PAC-Info - A-ID-Info",
				  pos, len);
		entry->a_id_info = pos;
		entry->a_id_info_len = len;
		break;
	case PAC_TYPE_PAC_TYPE:
		/* RFC 5422, Section 4.2.6 - PAC-Type TLV */
		if (len != 2) {
			wpa_printf(MSG_INFO, "EAP-FAST: Invalid PAC-Type "
				   "length %lu (expected 2)",
				   (unsigned long) len);
			wpa_hexdump_ascii(MSG_DEBUG,
					  "EAP-FAST: PAC-Info - PAC-Type",
					  pos, len);
			return -1;
		}
		pac_type = WPA_GET_BE16(pos);
		if (pac_type != PAC_TYPE_TUNNEL_PAC &&
		    pac_type != PAC_TYPE_USER_AUTHORIZATION &&
		    pac_type != PAC_TYPE_MACHINE_AUTHENTICATION) {
			wpa_printf(MSG_INFO, "EAP-FAST: Unsupported PAC Type "
				   "%d", pac_type);
			return -1;
		}

		wpa_printf(MSG_DEBUG, "EAP-FAST: PAC-Info - PAC-Type %d",
			   pac_type);
		entry->pac_type = pac_type;
		break;
	default:
		wpa_printf(MSG_DEBUG, "EAP-FAST: Ignored unknown PAC-Info "
			   "type %d", type);
		break;
	}

	return 0;
}