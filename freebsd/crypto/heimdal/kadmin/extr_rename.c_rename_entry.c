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
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 scalar_t__ kadm5_rename_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kadm_handle ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

int
rename_entry(void *opt, int argc, char **argv)
{
    krb5_error_code ret;
    krb5_principal princ1, princ2;

    ret = krb5_parse_name(context, argv[0], &princ1);
    if(ret){
	krb5_warn(context, ret, "krb5_parse_name(%s)", argv[0]);
	return ret != 0;
    }
    ret = krb5_parse_name(context, argv[1], &princ2);
    if(ret){
	krb5_free_principal(context, princ1);
	krb5_warn(context, ret, "krb5_parse_name(%s)", argv[1]);
	return ret != 0;
    }
    ret = kadm5_rename_principal(kadm_handle, princ1, princ2);
    if(ret)
	krb5_warn(context, ret, "rename");
    krb5_free_principal(context, princ1);
    krb5_free_principal(context, princ2);
    return ret != 0;
}