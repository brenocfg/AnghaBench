#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ntlm_buf {int /*<<< orphan*/ * data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__* ntlm_name ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int krb5_error_code ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/ * krb5_context ;
typedef  int /*<<< orphan*/ * krb5_ccache ;
struct TYPE_7__ {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KRB5_PRINCIPAL_UNPARSE_NO_REALM ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int krb5_cc_default (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int krb5_cc_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int krb5_cc_get_principal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int krb5_init_context (int /*<<< orphan*/ **) ; 
 int krb5_unparse_name_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_user_ccache(const ntlm_name name, char **username, struct ntlm_buf *key)
{
    krb5_context context = NULL;
    krb5_principal client;
    krb5_ccache id = NULL;
    krb5_error_code ret;
    char *confname;
    krb5_data data;

    *username = NULL;
    krb5_data_zero(&data);
    key->length = 0;
    key->data = NULL;

    ret = krb5_init_context(&context);
    if (ret)
	return ret;

    ret = krb5_cc_default(context, &id);
    if (ret)
	goto out;

    ret = krb5_cc_get_principal(context, id, &client);
    if (ret)
	goto out;

    ret = krb5_unparse_name_flags(context, client,
				  KRB5_PRINCIPAL_UNPARSE_NO_REALM,
				  username);
    krb5_free_principal(context, client);
    if (ret)
	goto out;

    asprintf(&confname, "ntlm-key-%s", name->domain);
    if (confname == NULL) {
	krb5_clear_error_message(context);
	ret = ENOMEM;
	goto out;
    }

    ret = krb5_cc_get_config(context, id, NULL,
			     confname, &data);
    if (ret)
	goto out;

    key->data = malloc(data.length);
    if (key->data == NULL) {
	ret = ENOMEM;
	goto out;
    }
    key->length = data.length;
    memcpy(key->data, data.data, data.length);

 out:
    krb5_data_free(&data);
    if (id)
	krb5_cc_close(context, id);

    krb5_free_context(context);

    return ret;
}