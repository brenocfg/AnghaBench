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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_address ;
typedef  int /*<<< orphan*/  b_str ;
typedef  int /*<<< orphan*/  a_str ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5KRB_AP_ERR_BADADDR ; 
 scalar_t__ krb5_address_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_print_address (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,char*,char*) ; 

__attribute__((used)) static krb5_error_code
compare_addrs(krb5_context context,
	      krb5_address *a,
	      krb5_address *b,
	      const char *message)
{
    char a_str[64], b_str[64];
    size_t len;

    if(krb5_address_compare (context, a, b))
	return 0;

    krb5_print_address (a, a_str, sizeof(a_str), &len);
    krb5_print_address (b, b_str, sizeof(b_str), &len);
    krb5_set_error_message(context, KRB5KRB_AP_ERR_BADADDR,
			   "%s: %s != %s", message, b_str, a_str);
    return KRB5KRB_AP_ERR_BADADDR;
}