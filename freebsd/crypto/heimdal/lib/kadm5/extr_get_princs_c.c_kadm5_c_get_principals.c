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
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  scalar_t__ kadm5_ret_t ;
typedef  int /*<<< orphan*/  kadm5_client_context ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ _kadm5_client_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ _kadm5_client_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ _kadm5_connect (void*) ; 
 char** calloc (int,int) ; 
 int /*<<< orphan*/  kadm_get_princs ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_ret_int32 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  krb5_ret_string (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_mem (unsigned char*,int) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_store_string (int /*<<< orphan*/ *,char const*) ; 

kadm5_ret_t
kadm5_c_get_principals(void *server_handle,
		       const char *expression,
		       char ***princs,
		       int *count)
{
    kadm5_client_context *context = server_handle;
    kadm5_ret_t ret;
    krb5_storage *sp;
    unsigned char buf[1024];
    int32_t tmp;
    krb5_data reply;

    ret = _kadm5_connect(server_handle);
    if(ret)
	return ret;

    sp = krb5_storage_from_mem(buf, sizeof(buf));
    if (sp == NULL)
	return ENOMEM;
    krb5_store_int32(sp, kadm_get_princs);
    krb5_store_int32(sp, expression != NULL);
    if(expression)
	krb5_store_string(sp, expression);
    ret = _kadm5_client_send(context, sp);
    krb5_storage_free(sp);
    if (ret)
	return ret;
    ret = _kadm5_client_recv(context, &reply);
    if(ret)
	return ret;
    sp = krb5_storage_from_data (&reply);
    if (sp == NULL) {
	krb5_data_free (&reply);
	return ENOMEM;
    }
    krb5_ret_int32(sp, &tmp);
    ret = tmp;
    if(ret == 0) {
	int i;
	krb5_ret_int32(sp, &tmp);
	*princs = calloc(tmp + 1, sizeof(**princs));
	if (*princs == NULL) {
	    ret = ENOMEM;
	    goto out;
	}
	for(i = 0; i < tmp; i++)
	    krb5_ret_string(sp, &(*princs)[i]);
	*count = tmp;
    }
out:
    krb5_storage_free(sp);
    krb5_data_free (&reply);
    return ret;
}