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
typedef  int u16 ;
struct wpa_config_blob {size_t len; int /*<<< orphan*/ * data; } ;
struct eap_sm {int dummy; } ;
struct eap_fast_pac {int pac_opaque_len; int pac_info_len; struct eap_fast_pac* next; int /*<<< orphan*/ * pac_info; int /*<<< orphan*/ * pac_opaque; int /*<<< orphan*/  pac_key; void* pac_type; } ;

/* Variables and functions */
 void* EAP_FAST_PAC_BINARY_FORMAT_VERSION ; 
 scalar_t__ EAP_FAST_PAC_BINARY_MAGIC ; 
 int EAP_FAST_PAC_KEY_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 void* WPA_GET_BE16 (int /*<<< orphan*/ *) ; 
 scalar_t__ WPA_GET_BE32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_fast_free_pac (struct eap_fast_pac*) ; 
 int /*<<< orphan*/  eap_fast_pac_get_a_id (struct eap_fast_pac*) ; 
 struct wpa_config_blob* eap_get_config_blob (struct eap_sm*,char const*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* os_memdup (int /*<<< orphan*/ *,int) ; 
 scalar_t__ os_readfile (char const*,size_t*) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 struct eap_fast_pac* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int eap_fast_load_pac_bin(struct eap_sm *sm, struct eap_fast_pac **pac_root,
			  const char *pac_file)
{
	const struct wpa_config_blob *blob = NULL;
	u8 *buf, *end, *pos;
	size_t len, count = 0;
	struct eap_fast_pac *pac, *prev;

	*pac_root = NULL;

	if (pac_file == NULL)
		return -1;

	if (os_strncmp(pac_file, "blob://", 7) == 0) {
		blob = eap_get_config_blob(sm, pac_file + 7);
		if (blob == NULL) {
			wpa_printf(MSG_INFO, "EAP-FAST: No PAC blob '%s' - "
				   "assume no PAC entries have been "
				   "provisioned", pac_file + 7);
			return 0;
		}
		buf = blob->data;
		len = blob->len;
	} else {
		buf = (u8 *) os_readfile(pac_file, &len);
		if (buf == NULL) {
			wpa_printf(MSG_INFO, "EAP-FAST: No PAC file '%s' - "
				   "assume no PAC entries have been "
				   "provisioned", pac_file);
			return 0;
		}
	}

	if (len == 0) {
		if (blob == NULL)
			os_free(buf);
		return 0;
	}

	if (len < 6 || WPA_GET_BE32(buf) != EAP_FAST_PAC_BINARY_MAGIC ||
	    WPA_GET_BE16(buf + 4) != EAP_FAST_PAC_BINARY_FORMAT_VERSION) {
		wpa_printf(MSG_INFO, "EAP-FAST: Invalid PAC file '%s' (bin)",
			   pac_file);
		if (blob == NULL)
			os_free(buf);
		return -1;
	}

	pac = prev = NULL;
	pos = buf + 6;
	end = buf + len;
	while (pos < end) {
		u16 val;

		if (end - pos < 2 + EAP_FAST_PAC_KEY_LEN + 2 + 2) {
			pac = NULL;
			goto parse_fail;
		}

		pac = os_zalloc(sizeof(*pac));
		if (pac == NULL)
			goto parse_fail;

		pac->pac_type = WPA_GET_BE16(pos);
		pos += 2;
		os_memcpy(pac->pac_key, pos, EAP_FAST_PAC_KEY_LEN);
		pos += EAP_FAST_PAC_KEY_LEN;
		val = WPA_GET_BE16(pos);
		pos += 2;
		if (val > end - pos)
			goto parse_fail;
		pac->pac_opaque_len = val;
		pac->pac_opaque = os_memdup(pos, pac->pac_opaque_len);
		if (pac->pac_opaque == NULL)
			goto parse_fail;
		pos += pac->pac_opaque_len;
		if (2 > end - pos)
			goto parse_fail;
		val = WPA_GET_BE16(pos);
		pos += 2;
		if (val > end - pos)
			goto parse_fail;
		pac->pac_info_len = val;
		pac->pac_info = os_memdup(pos, pac->pac_info_len);
		if (pac->pac_info == NULL)
			goto parse_fail;
		pos += pac->pac_info_len;
		eap_fast_pac_get_a_id(pac);

		count++;
		if (prev)
			prev->next = pac;
		else
			*pac_root = pac;
		prev = pac;
	}

	if (blob == NULL)
		os_free(buf);

	wpa_printf(MSG_DEBUG, "EAP-FAST: Read %lu PAC entries from '%s' (bin)",
		   (unsigned long) count, pac_file);

	return 0;

parse_fail:
	wpa_printf(MSG_INFO, "EAP-FAST: Failed to parse PAC file '%s' (bin)",
		   pac_file);
	if (blob == NULL)
		os_free(buf);
	if (pac)
		eap_fast_free_pac(pac);
	return -1;
}