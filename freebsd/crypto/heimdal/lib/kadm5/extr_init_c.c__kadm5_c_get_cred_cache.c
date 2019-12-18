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
typedef  int /*<<< orphan*/  krb5_prompter_fct ;
typedef  int /*<<< orphan*/ * krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/ * krb5_ccache ;

/* Variables and functions */
 char* KADM5_ADMIN_SERVICE ; 
 scalar_t__ KADM5_FAILURE ; 
 scalar_t__ get_cache_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 char* get_default_username () ; 
 scalar_t__ get_kadm_ticket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ get_new_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*) ; 

krb5_error_code
_kadm5_c_get_cred_cache(krb5_context context,
			const char *client_name,
			const char *server_name,
			const char *password,
			krb5_prompter_fct prompter,
			const char *keytab,
			krb5_ccache ccache,
			krb5_ccache *ret_cache)
{
    krb5_error_code ret;
    krb5_ccache id = NULL;
    krb5_principal default_client = NULL, client = NULL;

    /* treat empty password as NULL */
    if(password && *password == '\0')
	password = NULL;
    if(server_name == NULL)
	server_name = KADM5_ADMIN_SERVICE;

    if(client_name != NULL) {
	ret = krb5_parse_name(context, client_name, &client);
	if(ret)
	    return ret;
    }

    if(ccache != NULL) {
	id = ccache;
	ret = krb5_cc_get_principal(context, id, &client);
	if(ret)
	    return ret;
    } else {
	/* get principal from default cache, ok if this doesn't work */

	ret = get_cache_principal(context, &id, &default_client);
	if (ret) {
	    /*
	     * No client was specified by the caller and we cannot
	     * determine the client from a credentials cache.
	     */
	    const char *user;

	    user = get_default_username ();

	    if(user == NULL) {
		krb5_set_error_message(context, KADM5_FAILURE, "Unable to find local user name");
		return KADM5_FAILURE;
	    }
	    ret = krb5_make_principal(context, &default_client,
				      NULL, user, "admin", NULL);
	    if(ret)
		return ret;
	}
    }


    /*
     * No client was specified by the caller, but we have a client
     * from the default credentials cache.
     */
    if (client == NULL && default_client != NULL)
	client = default_client;


    if(id && client && (default_client == NULL ||
	      krb5_principal_compare(context, client, default_client) != 0)) {
	ret = get_kadm_ticket(context, id, client, server_name);
	if(ret == 0) {
	    *ret_cache = id;
	    krb5_free_principal(context, default_client);
	    if (default_client != client)
		krb5_free_principal(context, client);
	    return 0;
	}
	if(ccache != NULL)
	    /* couldn't get ticket from cache */
	    return -1;
    }
    /* get creds via AS request */
    if(id && (id != ccache))
	krb5_cc_close(context, id);
    if (client != default_client)
	krb5_free_principal(context, default_client);

    ret = get_new_cache(context, client, password, prompter, keytab,
			server_name, ret_cache);
    krb5_free_principal(context, client);
    return ret;
}