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
struct eap_sm {int /*<<< orphan*/ * ext_pw_buf; int /*<<< orphan*/  ext_pw; } ;
struct eap_peer_config {int /*<<< orphan*/  password_len; int /*<<< orphan*/ * password; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext_password_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ext_password_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memcpy (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* os_zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_get_ext_password(struct eap_sm *sm,
				struct eap_peer_config *config)
{
	char *name;

	if (config->password == NULL)
		return -1;

	name = os_zalloc(config->password_len + 1);
	if (name == NULL)
		return -1;
	os_memcpy(name, config->password, config->password_len);

	ext_password_free(sm->ext_pw_buf);
	sm->ext_pw_buf = ext_password_get(sm->ext_pw, name);
	os_free(name);

	return sm->ext_pw_buf == NULL ? -1 : 0;
}