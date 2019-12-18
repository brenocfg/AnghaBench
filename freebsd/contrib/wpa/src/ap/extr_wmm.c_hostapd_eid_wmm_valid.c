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
struct wmm_information_element {scalar_t__ oui_subtype; scalar_t__ version; int /*<<< orphan*/  qos_info; int /*<<< orphan*/  oui_type; int /*<<< orphan*/ * oui; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ WMM_OUI_SUBTYPE_INFORMATION_ELEMENT ; 
 scalar_t__ WMM_VERSION ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int hostapd_eid_wmm_valid(struct hostapd_data *hapd, const u8 *eid, size_t len)
{
	struct wmm_information_element *wmm;

	wpa_hexdump(MSG_MSGDUMP, "WMM IE", eid, len);

	if (len < sizeof(struct wmm_information_element)) {
		wpa_printf(MSG_DEBUG, "Too short WMM IE (len=%lu)",
			   (unsigned long) len);
		return 0;
	}

	wmm = (struct wmm_information_element *) eid;
	wpa_printf(MSG_DEBUG, "Validating WMM IE: OUI %02x:%02x:%02x  "
		   "OUI type %d  OUI sub-type %d  version %d  QoS info 0x%x",
		   wmm->oui[0], wmm->oui[1], wmm->oui[2], wmm->oui_type,
		   wmm->oui_subtype, wmm->version, wmm->qos_info);
	if (wmm->oui_subtype != WMM_OUI_SUBTYPE_INFORMATION_ELEMENT ||
	    wmm->version != WMM_VERSION) {
		wpa_printf(MSG_DEBUG, "Unsupported WMM IE Subtype/Version");
		return 0;
	}

	return 1;
}