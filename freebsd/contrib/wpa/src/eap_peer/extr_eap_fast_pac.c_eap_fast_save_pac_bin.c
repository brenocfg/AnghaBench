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
struct eap_fast_pac {int pac_opaque_len; int pac_info_len; int pac_type; struct eap_fast_pac* next; int /*<<< orphan*/  pac_info; int /*<<< orphan*/  pac_opaque; int /*<<< orphan*/  pac_key; } ;

/* Variables and functions */
 int EAP_FAST_PAC_BINARY_FORMAT_VERSION ; 
 int /*<<< orphan*/  EAP_FAST_PAC_BINARY_MAGIC ; 
 int EAP_FAST_PAC_KEY_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WPA_PUT_BE32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_fast_write_pac (struct eap_sm*,char const*,char*,size_t) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long,char const*) ; 

int eap_fast_save_pac_bin(struct eap_sm *sm, struct eap_fast_pac *pac_root,
			  const char *pac_file)
{
	size_t len, count = 0;
	struct eap_fast_pac *pac;
	u8 *buf, *pos;

	len = 6;
	pac = pac_root;
	while (pac) {
		if (pac->pac_opaque_len > 65535 ||
		    pac->pac_info_len > 65535)
			return -1;
		len += 2 + EAP_FAST_PAC_KEY_LEN + 2 + pac->pac_opaque_len +
			2 + pac->pac_info_len;
		pac = pac->next;
	}

	buf = os_malloc(len);
	if (buf == NULL)
		return -1;

	pos = buf;
	WPA_PUT_BE32(pos, EAP_FAST_PAC_BINARY_MAGIC);
	pos += 4;
	WPA_PUT_BE16(pos, EAP_FAST_PAC_BINARY_FORMAT_VERSION);
	pos += 2;

	pac = pac_root;
	while (pac) {
		WPA_PUT_BE16(pos, pac->pac_type);
		pos += 2;
		os_memcpy(pos, pac->pac_key, EAP_FAST_PAC_KEY_LEN);
		pos += EAP_FAST_PAC_KEY_LEN;
		WPA_PUT_BE16(pos, pac->pac_opaque_len);
		pos += 2;
		os_memcpy(pos, pac->pac_opaque, pac->pac_opaque_len);
		pos += pac->pac_opaque_len;
		WPA_PUT_BE16(pos, pac->pac_info_len);
		pos += 2;
		os_memcpy(pos, pac->pac_info, pac->pac_info_len);
		pos += pac->pac_info_len;

		pac = pac->next;
		count++;
	}

	if (eap_fast_write_pac(sm, pac_file, (char *) buf, len)) {
		os_free(buf);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "EAP-FAST: Wrote %lu PAC entries into '%s' "
		   "(bin)", (unsigned long) count, pac_file);

	return 0;
}