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
typedef  int /*<<< orphan*/ * krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_have_content (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static krb5_error_code
validate_keytab(krb5_context context, const char *name, krb5_keytab *id)
{
    krb5_error_code ret;

    ret = krb5_kt_resolve(context, name, id);
    if (ret)
	return ret;

    ret = krb5_kt_have_content(context, *id);
    if (ret) {
	krb5_kt_close(context, *id);
	*id = NULL;
    }

    return ret;
}