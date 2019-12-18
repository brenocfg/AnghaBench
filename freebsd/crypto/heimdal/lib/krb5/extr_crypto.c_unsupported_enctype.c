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
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 scalar_t__ KRB5_PROG_ETYPE_NOSUPP ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ krb5_enctype_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static krb5_error_code
unsupported_enctype(krb5_context context, krb5_enctype etype)
{
    krb5_error_code ret;
    char *name;

    ret = krb5_enctype_to_string(context, etype, &name);
    if (ret)
	return ret;

    krb5_set_error_message(context, KRB5_PROG_ETYPE_NOSUPP,
			   N_("Encryption type %s not supported", ""),
			   name);
    free(name);
    return KRB5_PROG_ETYPE_NOSUPP;
}