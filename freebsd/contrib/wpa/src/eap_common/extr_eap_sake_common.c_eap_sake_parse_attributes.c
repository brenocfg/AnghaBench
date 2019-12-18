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
typedef  int u8 ;
struct eap_sake_parse_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eap_sake_parse_add_attr (struct eap_sake_parse_attr*,int const,int const,int const*) ; 
 int /*<<< orphan*/  os_memset (struct eap_sake_parse_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int eap_sake_parse_attributes(const u8 *buf, size_t len,
			      struct eap_sake_parse_attr *attr)
{
	const u8 *pos = buf, *end = buf + len;

	os_memset(attr, 0, sizeof(*attr));
	while (pos < end) {
		if (end - pos < 2) {
			wpa_printf(MSG_DEBUG, "EAP-SAKE: Too short attribute");
			return -1;
		}

		if (pos[1] < 2) {
			wpa_printf(MSG_DEBUG, "EAP-SAKE: Invalid attribute "
				   "length (%d)", pos[1]);
			return -1;
		}

		if (pos + pos[1] > end) {
			wpa_printf(MSG_DEBUG, "EAP-SAKE: Attribute underflow");
			return -1;
		}

		if (eap_sake_parse_add_attr(attr, pos[0], pos[1] - 2, pos + 2))
			return -1;

		pos += pos[1];
	}

	return 0;
}