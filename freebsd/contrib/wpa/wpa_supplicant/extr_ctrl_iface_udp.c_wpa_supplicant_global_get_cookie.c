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
struct ctrl_iface_global_priv {int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int COOKIE_LEN ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
wpa_supplicant_global_get_cookie(struct ctrl_iface_global_priv *priv,
				 size_t *reply_len)
{
	char *reply;
	reply = os_malloc(7 + 2 * COOKIE_LEN + 1);
	if (reply == NULL) {
		*reply_len = 1;
		return NULL;
	}

	os_memcpy(reply, "COOKIE=", 7);
	wpa_snprintf_hex(reply + 7, 2 * COOKIE_LEN + 1,
			 priv->cookie, COOKIE_LEN);

	*reply_len = 7 + 2 * COOKIE_LEN;
	return reply;
}