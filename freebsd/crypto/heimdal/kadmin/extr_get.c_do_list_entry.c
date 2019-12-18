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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 scalar_t__ krb5_unparse_name_fixed_short (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
do_list_entry(krb5_principal principal, void *data)
{
    char buf[1024];
    krb5_error_code ret;

    ret = krb5_unparse_name_fixed_short(context, principal, buf, sizeof(buf));
    if (ret != 0)
        return ret;
    printf("%s\n", buf);
    return 0;
}