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
struct ext_keytab_options {int /*<<< orphan*/ * keytab_string; } ;
struct ext_keytab_data {int /*<<< orphan*/  keytab; } ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  do_ext_keytab ; 
 scalar_t__ foreach_principal (char*,int /*<<< orphan*/ ,char*,struct ext_keytab_data*) ; 
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_kt_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 

int
ext_keytab(struct ext_keytab_options *opt, int argc, char **argv)
{
    krb5_error_code ret;
    int i;
    struct ext_keytab_data data;

    if (opt->keytab_string == NULL)
	ret = krb5_kt_default(context, &data.keytab);
    else
	ret = krb5_kt_resolve(context, opt->keytab_string, &data.keytab);

    if(ret){
	krb5_warn(context, ret, "krb5_kt_resolve");
	return 1;
    }

    for(i = 0; i < argc; i++) {
	ret = foreach_principal(argv[i], do_ext_keytab, "ext", &data);
	if (ret)
	    break;
    }

    krb5_kt_close(context, data.keytab);

    return ret != 0;
}