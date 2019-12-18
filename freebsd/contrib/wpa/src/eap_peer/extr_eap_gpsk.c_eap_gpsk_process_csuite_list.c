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
struct eap_sm {int dummy; } ;
struct eap_gpsk_data {int dummy; } ;
struct eap_gpsk_csuite {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ eap_gpsk_select_csuite (struct eap_sm*,struct eap_gpsk_data*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static const u8 * eap_gpsk_process_csuite_list(struct eap_sm *sm,
					       struct eap_gpsk_data *data,
					       const u8 **list,
					       size_t *list_len,
					       const u8 *pos, const u8 *end)
{
	size_t len;

	if (pos == NULL)
		return NULL;

	if (end - pos < 2) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short GPSK-1 packet");
		return NULL;
	}
	len = WPA_GET_BE16(pos);
	pos += 2;
	if (len > (size_t) (end - pos)) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: CSuite_List overflow");
		return NULL;
	}
	if (len == 0 || (len % sizeof(struct eap_gpsk_csuite))) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Invalid CSuite_List len %lu",
			   (unsigned long) len);
		return NULL;
	}

	if (eap_gpsk_select_csuite(sm, data, pos, len) < 0)
		return NULL;

	*list = pos;
	*list_len = len;
	pos += len;

	return pos;
}