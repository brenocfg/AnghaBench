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
struct list_options {int timestamp_flag; } ;
typedef  int /*<<< orphan*/  kt ;
typedef  int /*<<< orphan*/  krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 scalar_t__ do_list (struct list_options*,char*) ; 
 char* keytab_string ; 
 int /*<<< orphan*/  krb5_kt_default_name (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ verbose_flag ; 

int
kt_list(struct list_options *opt, int argc, char **argv)
{
    krb5_error_code ret;
    char kt[1024];

    if(verbose_flag)
	opt->timestamp_flag = 1;

    if (keytab_string == NULL) {
	if((ret = krb5_kt_default_name(context, kt, sizeof(kt))) != 0) {
	    krb5_warn(context, ret, "getting default keytab name");
	    return 1;
	}
	keytab_string = kt;
    }
    return do_list(opt, keytab_string) != 0;
}