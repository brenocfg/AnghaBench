#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
struct TYPE_4__ {char* admin_server; int /*<<< orphan*/ * realm; int /*<<< orphan*/  mask; int /*<<< orphan*/  kadmind_port; } ;
typedef  TYPE_1__ kadm5_config_params ;
typedef  int /*<<< orphan*/  conf ;

/* Variables and functions */
 int /*<<< orphan*/  KADM5_ADMIN_SERVICE ; 
 int /*<<< orphan*/  KADM5_CONFIG_ADMIN_SERVER ; 
 int /*<<< orphan*/  KADM5_CONFIG_KADMIND_PORT ; 
 int /*<<< orphan*/  KADM5_CONFIG_REALM ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ kadm5_init_with_password_ctx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static void*
open_kadmin_connection(char *principal,
		       const char *realm,
		       char *admin_server,
		       int server_port)
{
    static kadm5_config_params conf;
    krb5_error_code ret;
    void *kadm_handle;
    memset(&conf, 0, sizeof(conf));

    if(realm) {
	conf.realm = strdup(realm);
	if (conf.realm == NULL) {
	    krb5_set_error_message(context, 0, "malloc: out of memory");
	    return NULL;
	}
	conf.mask |= KADM5_CONFIG_REALM;
    }

    if (admin_server) {
	conf.admin_server = admin_server;
	conf.mask |= KADM5_CONFIG_ADMIN_SERVER;
    }

    if (server_port) {
	conf.kadmind_port = htons(server_port);
	conf.mask |= KADM5_CONFIG_KADMIND_PORT;
    }

    /* should get realm from each principal, instead of doing
       everything with the same (local) realm */

    ret = kadm5_init_with_password_ctx(context,
				       principal,
				       NULL,
				       KADM5_ADMIN_SERVICE,
				       &conf, 0, 0,
				       &kadm_handle);
    free(conf.realm);
    if(ret) {
	krb5_warn(context, ret, "kadm5_init_with_password");
	return NULL;
    }
    return kadm_handle;
}