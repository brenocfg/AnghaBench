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
typedef  int /*<<< orphan*/  title ;

/* Variables and functions */
 size_t MAX_WEP_KEY_LEN ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,char*,size_t) ; 
 int os_snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  os_snprintf_error (int,int) ; 
 int /*<<< orphan*/  str_clear_free (char*) ; 
 char* wpa_config_parse_string (char const*,size_t*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,unsigned int,...) ; 

__attribute__((used)) static int wpa_config_parse_wep_key(u8 *key, size_t *len, int line,
				    const char *value, int idx)
{
	char *buf, title[20];
	int res;

	buf = wpa_config_parse_string(value, len);
	if (buf == NULL) {
		wpa_printf(MSG_ERROR, "Line %d: Invalid WEP key %d '%s'.",
			   line, idx, value);
		return -1;
	}
	if (*len > MAX_WEP_KEY_LEN) {
		wpa_printf(MSG_ERROR, "Line %d: Too long WEP key %d '%s'.",
			   line, idx, value);
		os_free(buf);
		return -1;
	}
	if (*len && *len != 5 && *len != 13 && *len != 16) {
		wpa_printf(MSG_ERROR, "Line %d: Invalid WEP key length %u - "
			   "this network block will be ignored",
			   line, (unsigned int) *len);
	}
	os_memcpy(key, buf, *len);
	str_clear_free(buf);
	res = os_snprintf(title, sizeof(title), "wep_key%d", idx);
	if (!os_snprintf_error(sizeof(title), res))
		wpa_hexdump_key(MSG_MSGDUMP, title, key, *len);
	return 0;
}