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

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_EID_NEIGHBOR_REPORT ; 
 int /*<<< orphan*/  WPA_PUT_LE32 (int*,long) ; 
 void* atoi (char const*) ; 
 scalar_t__ hexstr2bin (char const*,int*,size_t) ; 
 scalar_t__ hwaddr_aton (char const*,int*) ; 
 void* os_strchr (char const*,char) ; 
 size_t os_strlen (char const*) ; 
 char* os_strstr (char const*,char*) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int ieee802_11_parse_candidate_list(const char *pos, u8 *nei_rep,
				    size_t nei_rep_len)
{
	u8 *nei_pos = nei_rep;
	const char *end;

	/*
	 * BSS Transition Candidate List Entries - Neighbor Report elements
	 * neighbor=<BSSID>,<BSSID Information>,<Operating Class>,
	 * <Channel Number>,<PHY Type>[,<hexdump of Optional Subelements>]
	 */
	while (pos) {
		u8 *nei_start;
		long int val;
		char *endptr, *tmp;

		pos = os_strstr(pos, " neighbor=");
		if (!pos)
			break;
		if (nei_pos + 15 > nei_rep + nei_rep_len) {
			wpa_printf(MSG_DEBUG,
				   "Not enough room for additional neighbor");
			return -1;
		}
		pos += 10;

		nei_start = nei_pos;
		*nei_pos++ = WLAN_EID_NEIGHBOR_REPORT;
		nei_pos++; /* length to be filled in */

		if (hwaddr_aton(pos, nei_pos)) {
			wpa_printf(MSG_DEBUG, "Invalid BSSID");
			return -1;
		}
		nei_pos += ETH_ALEN;
		pos += 17;
		if (*pos != ',') {
			wpa_printf(MSG_DEBUG, "Missing BSSID Information");
			return -1;
		}
		pos++;

		val = strtol(pos, &endptr, 0);
		WPA_PUT_LE32(nei_pos, val);
		nei_pos += 4;
		if (*endptr != ',') {
			wpa_printf(MSG_DEBUG, "Missing Operating Class");
			return -1;
		}
		pos = endptr + 1;

		*nei_pos++ = atoi(pos); /* Operating Class */
		pos = os_strchr(pos, ',');
		if (pos == NULL) {
			wpa_printf(MSG_DEBUG, "Missing Channel Number");
			return -1;
		}
		pos++;

		*nei_pos++ = atoi(pos); /* Channel Number */
		pos = os_strchr(pos, ',');
		if (pos == NULL) {
			wpa_printf(MSG_DEBUG, "Missing PHY Type");
			return -1;
		}
		pos++;

		*nei_pos++ = atoi(pos); /* PHY Type */
		end = os_strchr(pos, ' ');
		tmp = os_strchr(pos, ',');
		if (tmp && (!end || tmp < end)) {
			/* Optional Subelements (hexdump) */
			size_t len;

			pos = tmp + 1;
			end = os_strchr(pos, ' ');
			if (end)
				len = end - pos;
			else
				len = os_strlen(pos);
			if (nei_pos + len / 2 > nei_rep + nei_rep_len) {
				wpa_printf(MSG_DEBUG,
					   "Not enough room for neighbor subelements");
				return -1;
			}
			if (len & 0x01 ||
			    hexstr2bin(pos, nei_pos, len / 2) < 0) {
				wpa_printf(MSG_DEBUG,
					   "Invalid neighbor subelement info");
				return -1;
			}
			nei_pos += len / 2;
			pos = end;
		}

		nei_start[1] = nei_pos - nei_start - 2;
	}

	return nei_pos - nei_rep;
}