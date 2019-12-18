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
struct eap_sm {int /*<<< orphan*/  ext_pw_buf; } ;
struct eap_peer_config {int flags; size_t password_len; int /*<<< orphan*/  const* password; } ;

/* Variables and functions */
 int EAP_CONFIG_FLAGS_EXT_PASSWORD ; 
 struct eap_peer_config* eap_get_config (struct eap_sm*) ; 
 scalar_t__ eap_get_ext_password (struct eap_sm*,struct eap_peer_config*) ; 
 int /*<<< orphan*/  const* wpabuf_head (int /*<<< orphan*/ ) ; 
 size_t wpabuf_len (int /*<<< orphan*/ ) ; 

const u8 * eap_get_config_password(struct eap_sm *sm, size_t *len)
{
	struct eap_peer_config *config = eap_get_config(sm);
	if (config == NULL)
		return NULL;

	if (config->flags & EAP_CONFIG_FLAGS_EXT_PASSWORD) {
		if (eap_get_ext_password(sm, config) < 0)
			return NULL;
		*len = wpabuf_len(sm->ext_pw_buf);
		return wpabuf_head(sm->ext_pw_buf);
	}

	*len = config->password_len;
	return config->password;
}