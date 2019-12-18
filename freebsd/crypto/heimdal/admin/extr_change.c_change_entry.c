#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_kvno ;
struct TYPE_6__ {int /*<<< orphan*/  keyblock; scalar_t__ vno; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  principal; } ;
typedef  TYPE_1__ krb5_keytab_entry ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_7__ {char* realm; char* admin_server; int /*<<< orphan*/  mask; int /*<<< orphan*/  kadmind_port; } ;
typedef  TYPE_2__ kadm5_config_params ;
typedef  int /*<<< orphan*/  conf ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  KADM5_ADMIN_SERVICE ; 
 int /*<<< orphan*/  KADM5_CONFIG_ADMIN_SERVER ; 
 int /*<<< orphan*/  KADM5_CONFIG_KADMIND_PORT ; 
 int /*<<< orphan*/  KADM5_CONFIG_REALM ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  kadm5_destroy (void*) ; 
 scalar_t__ kadm5_init_with_skey_ctx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ kadm5_randkey_principal (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  keytab_string ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_add_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* krb5_principal_get_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
change_entry (krb5_keytab keytab,
	      krb5_principal principal, krb5_kvno kvno,
	      const char *realm, const char *admin_server, int server_port)
{
    krb5_error_code ret;
    kadm5_config_params conf;
    void *kadm_handle;
    char *client_name;
    krb5_keyblock *keys;
    int num_keys;
    int i;

    ret = krb5_unparse_name (context, principal, &client_name);
    if (ret) {
	krb5_warn (context, ret, "krb5_unparse_name");
	return ret;
    }

    memset (&conf, 0, sizeof(conf));

    if(realm == NULL)
	realm = krb5_principal_get_realm(context, principal);
    conf.realm = strdup(realm);
    if (conf.realm == NULL) {
	free (client_name);
	krb5_set_error_message(context, ENOMEM, "malloc failed");
	return ENOMEM;
    }
    conf.mask |= KADM5_CONFIG_REALM;

    if (admin_server) {
	conf.admin_server = strdup(admin_server);
	if (conf.admin_server == NULL) {
	    free(client_name);
	    free(conf.realm);
	    krb5_set_error_message(context, ENOMEM, "malloc failed");
	    return ENOMEM;
	}
	conf.mask |= KADM5_CONFIG_ADMIN_SERVER;
    }

    if (server_port) {
	conf.kadmind_port = htons(server_port);
	conf.mask |= KADM5_CONFIG_KADMIND_PORT;
    }

    ret = kadm5_init_with_skey_ctx (context,
				    client_name,
				    keytab_string,
				    KADM5_ADMIN_SERVICE,
				    &conf, 0, 0,
				    &kadm_handle);
    free(conf.admin_server);
    free(conf.realm);
    if (ret) {
	krb5_warn (context, ret,
		   "kadm5_c_init_with_skey_ctx: %s:", client_name);
	free (client_name);
	return ret;
    }
    ret = kadm5_randkey_principal (kadm_handle, principal, &keys, &num_keys);
    kadm5_destroy (kadm_handle);
    if (ret) {
	krb5_warn(context, ret, "kadm5_randkey_principal: %s:", client_name);
	free (client_name);
	return ret;
    }
    free (client_name);
    for (i = 0; i < num_keys; ++i) {
	krb5_keytab_entry new_entry;

	new_entry.principal = principal;
	new_entry.timestamp = time (NULL);
	new_entry.vno = kvno + 1;
	new_entry.keyblock  = keys[i];

	ret = krb5_kt_add_entry (context, keytab, &new_entry);
	if (ret)
	    krb5_warn (context, ret, "krb5_kt_add_entry");
	krb5_free_keyblock_contents (context, &keys[i]);
    }
    return ret;
}