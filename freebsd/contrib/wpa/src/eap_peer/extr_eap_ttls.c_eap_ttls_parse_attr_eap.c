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
struct ttls_parse_avp {size_t eap_len; int /*<<< orphan*/ * eapdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/ * os_realloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_ttls_parse_attr_eap(const u8 *dpos, size_t dlen,
				   struct ttls_parse_avp *parse)
{
	wpa_printf(MSG_DEBUG, "EAP-TTLS: AVP - EAP Message");
	if (parse->eapdata == NULL) {
		parse->eapdata = os_memdup(dpos, dlen);
		if (parse->eapdata == NULL) {
			wpa_printf(MSG_WARNING, "EAP-TTLS: Failed to allocate "
				   "memory for Phase 2 EAP data");
			return -1;
		}
		parse->eap_len = dlen;
	} else {
		u8 *neweap = os_realloc(parse->eapdata, parse->eap_len + dlen);
		if (neweap == NULL) {
			wpa_printf(MSG_WARNING, "EAP-TTLS: Failed to allocate "
				   "memory for Phase 2 EAP data");
			return -1;
		}
		os_memcpy(neweap + parse->eap_len, dpos, dlen);
		parse->eapdata = neweap;
		parse->eap_len += dlen;
	}

	return 0;
}