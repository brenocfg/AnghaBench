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
typedef  int const u8 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_memcpy (char*,int const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int p2p_sd_dns_uncompress_label(char **upos, char *uend, u8 *start,
				       u8 **spos, const u8 *end)
{
	while (*spos < end) {
		u8 val = ((*spos)[0] & 0xc0) >> 6;
		int len;

		if (val == 1 || val == 2) {
			/* These are reserved values in RFC 1035 */
			wpa_printf(MSG_DEBUG, "P2P: Invalid domain name "
				   "sequence starting with 0x%x", val);
			return -1;
		}

		if (val == 3) {
			u16 offset;
			u8 *spos_tmp;

			/* Offset */
			if (end - *spos < 2) {
				wpa_printf(MSG_DEBUG, "P2P: No room for full "
					   "DNS offset field");
				return -1;
			}

			offset = (((*spos)[0] & 0x3f) << 8) | (*spos)[1];
			if (offset >= *spos - start) {
				wpa_printf(MSG_DEBUG, "P2P: Invalid DNS "
					   "pointer offset %u", offset);
				return -1;
			}

			(*spos) += 2;
			spos_tmp = start + offset;
			return p2p_sd_dns_uncompress_label(upos, uend, start,
							   &spos_tmp,
							   *spos - 2);
		}

		/* Label */
		len = (*spos)[0] & 0x3f;
		if (len == 0)
			return 0;

		(*spos)++;
		if (len > end - *spos) {
			wpa_printf(MSG_DEBUG, "P2P: Invalid domain name "
				   "sequence - no room for label with length "
				   "%u", len);
			return -1;
		}

		if (len + 2 > uend - *upos)
			return -2;

		os_memcpy(*upos, *spos, len);
		*spos += len;
		*upos += len;
		(*upos)[0] = '.';
		(*upos)++;
		(*upos)[0] = '\0';
	}

	return 0;
}