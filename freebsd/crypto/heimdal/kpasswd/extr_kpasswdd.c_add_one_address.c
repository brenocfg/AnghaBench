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
typedef  int /*<<< orphan*/  krb5_addresses ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  explicit_addresses ; 
 int /*<<< orphan*/  krb5_append_addresses (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_copy_addresses (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,char const*) ; 
 int /*<<< orphan*/  krb5_free_addresses (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_parse_address (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
add_one_address (const char *str, int first)
{
    krb5_error_code ret;
    krb5_addresses tmp;

    ret = krb5_parse_address (context, str, &tmp);
    if (ret)
	krb5_err (context, 1, ret, "parse_address `%s'", str);
    if (first)
	krb5_copy_addresses(context, &tmp, &explicit_addresses);
    else
	krb5_append_addresses(context, &explicit_addresses, &tmp);
    krb5_free_addresses (context, &tmp);
}