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
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  gss_cred_id_t ;
typedef  TYPE_2__* gss_buffer_set_t ;
struct TYPE_7__ {int count; TYPE_1__* elements; } ;
struct TYPE_6__ {scalar_t__ value; scalar_t__ length; } ;
typedef  int OM_uint32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 TYPE_2__* GSS_C_NO_BUFFER_SET ; 
 int /*<<< orphan*/  GSS_KRB5_COPY_CCACHE_X ; 
 int GSS_S_FAILURE ; 
 int asprintf (char**,char*,int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int gss_inquire_cred_by_oid (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  gss_release_buffer_set (int*,TYPE_2__**) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int krb5_cc_copy_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int krb5_cc_resolve (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 int krb5_init_context (int /*<<< orphan*/ *) ; 

OM_uint32
gss_krb5_copy_ccache(OM_uint32 *minor_status,
		     gss_cred_id_t cred,
		     krb5_ccache out)
{
    gss_buffer_set_t data_set = GSS_C_NO_BUFFER_SET;
    krb5_context context;
    krb5_error_code kret;
    krb5_ccache id;
    OM_uint32 ret;
    char *str;

    ret = gss_inquire_cred_by_oid(minor_status,
				  cred,
				  GSS_KRB5_COPY_CCACHE_X,
				  &data_set);
    if (ret)
	return ret;

    if (data_set == GSS_C_NO_BUFFER_SET || data_set->count != 1) {
	gss_release_buffer_set(minor_status, &data_set);
	*minor_status = EINVAL;
	return GSS_S_FAILURE;
    }

    kret = krb5_init_context(&context);
    if (kret) {
	*minor_status = kret;
	gss_release_buffer_set(minor_status, &data_set);
	return GSS_S_FAILURE;
    }

    kret = asprintf(&str, "%.*s", (int)data_set->elements[0].length,
		    (char *)data_set->elements[0].value);
    gss_release_buffer_set(minor_status, &data_set);
    if (kret == -1) {
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    kret = krb5_cc_resolve(context, str, &id);
    free(str);
    if (kret) {
	*minor_status = kret;
	return GSS_S_FAILURE;
    }

    kret = krb5_cc_copy_cache(context, id, out);
    krb5_cc_close(context, id);
    krb5_free_context(context);
    if (kret) {
	*minor_status = kret;
	return GSS_S_FAILURE;
    }

    return ret;
}