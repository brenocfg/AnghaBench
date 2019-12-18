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
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _gsskrb5_keytab ; 
 int /*<<< orphan*/  gssapi_keytab_mutex ; 
 scalar_t__ krb5_kt_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_get_full_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_xfree (char*) ; 

__attribute__((used)) static krb5_error_code
get_keytab(krb5_context context, krb5_keytab *keytab)
{
    krb5_error_code kret;

    HEIMDAL_MUTEX_lock(&gssapi_keytab_mutex);

    if (_gsskrb5_keytab != NULL) {
	char *name = NULL;

	kret = krb5_kt_get_full_name(context, _gsskrb5_keytab, &name);
	if (kret == 0) {
	    kret = krb5_kt_resolve(context, name, keytab);
	    krb5_xfree(name);
	}
    } else
	kret = krb5_kt_default(context, keytab);

    HEIMDAL_MUTEX_unlock(&gssapi_keytab_mutex);

    return (kret);
}