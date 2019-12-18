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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ _gsskrb5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _gsskrb5_keytab ; 
 scalar_t__ asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gssapi_keytab_mutex ; 
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_default (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ validate_keytab (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 

OM_uint32
_gsskrb5_register_acceptor_identity(OM_uint32 *min_stat, const char *identity)
{
    krb5_context context;
    krb5_error_code ret;

    *min_stat = 0;

    ret = _gsskrb5_init(&context);
    if(ret)
	return GSS_S_FAILURE;

    HEIMDAL_MUTEX_lock(&gssapi_keytab_mutex);

    if(_gsskrb5_keytab != NULL) {
	krb5_kt_close(context, _gsskrb5_keytab);
	_gsskrb5_keytab = NULL;
    }
    if (identity == NULL) {
	ret = krb5_kt_default(context, &_gsskrb5_keytab);
    } else {
	/*
	 * First check if we can the keytab as is and if it has content...
	 */
	ret = validate_keytab(context, identity, &_gsskrb5_keytab);
	/*
	 * if it doesn't, lets prepend FILE: and try again
	 */
	if (ret) {
	    char *p = NULL;
	    ret = asprintf(&p, "FILE:%s", identity);
	    if(ret < 0 || p == NULL) {
		HEIMDAL_MUTEX_unlock(&gssapi_keytab_mutex);
		return GSS_S_FAILURE;
	    }
	    ret = validate_keytab(context, p, &_gsskrb5_keytab);
	    free(p);
	}
    }
    HEIMDAL_MUTEX_unlock(&gssapi_keytab_mutex);
    if(ret) {
	*min_stat = ret;
	return GSS_S_FAILURE;
    }
    return GSS_S_COMPLETE;
}