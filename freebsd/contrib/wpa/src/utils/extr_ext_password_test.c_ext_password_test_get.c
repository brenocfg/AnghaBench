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
struct wpabuf {int dummy; } ;
struct ext_password_test_data {char* params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* ext_password_alloc (int) ; 
 char* os_strchr (char*,char) ; 
 size_t os_strlen (char const*) ; 
 scalar_t__ os_strncmp (char*,char const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char*,int) ; 

__attribute__((used)) static struct wpabuf * ext_password_test_get(void *ctx, const char *name)
{
	struct ext_password_test_data *data = ctx;
	char *pos, *pos2;
	size_t nlen;

	wpa_printf(MSG_DEBUG, "EXT PW TEST: get(%s)", name);

	pos = data->params;
	if (pos == NULL)
		return NULL;
	nlen = os_strlen(name);

	while (pos && *pos) {
		if (os_strncmp(pos, name, nlen) == 0 && pos[nlen] == '=') {
			struct wpabuf *buf;
			pos += nlen + 1;
			pos2 = pos;
			while (*pos2 != '|' && *pos2 != '\0')
				pos2++;
			buf = ext_password_alloc(pos2 - pos);
			if (buf == NULL)
				return NULL;
			wpabuf_put_data(buf, pos, pos2 - pos);
			wpa_hexdump_ascii_key(MSG_DEBUG, "EXT PW TEST: value",
					      wpabuf_head(buf),
					      wpabuf_len(buf));
			return buf;
		}

		pos = os_strchr(pos + 1, '|');
		if (pos)
			pos++;
	}

	wpa_printf(MSG_DEBUG, "EXT PW TEST: get(%s) - not found", name);

	return NULL;
}