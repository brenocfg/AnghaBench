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
struct http_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char const*,char const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,char*) ; 

__attribute__((used)) static void debug_dump(struct http_ctx *ctx, const char *title,
		       const char *buf, size_t len)
{
	char *txt;
	size_t i;

	for (i = 0; i < len; i++) {
		if (buf[i] < 32 && buf[i] != '\t' && buf[i] != '\n' &&
		    buf[i] != '\r') {
			wpa_hexdump_ascii(MSG_MSGDUMP, title, buf, len);
			return;
		}
	}

	txt = os_malloc(len + 1);
	if (txt == NULL)
		return;
	os_memcpy(txt, buf, len);
	txt[len] = '\0';
	while (len > 0) {
		len--;
		if (txt[len] == '\n' || txt[len] == '\r')
			txt[len] = '\0';
		else
			break;
	}
	wpa_printf(MSG_MSGDUMP, "%s[%s]", title, txt);
	os_free(txt);
}