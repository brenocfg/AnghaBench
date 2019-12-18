#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_4__ {int len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ krb5_addresses ;

/* Variables and functions */
 scalar_t__ krb5_address_order (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_addresses (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_parse_address (int /*<<< orphan*/ ,char const*,TYPE_1__*) ; 

__attribute__((used)) static void
match_addr(krb5_context context, const char *range_addr,
	   const char *one_addr, int match)
{
    krb5_addresses range, one;
    krb5_error_code ret;

    ret = krb5_parse_address(context, range_addr, &range);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_address");

    if (range.len != 1)
	krb5_err(context, 1, ret, "wrong num of addresses");

    ret = krb5_parse_address(context, one_addr, &one);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_address");

    if (one.len != 1)
	krb5_err(context, 1, ret, "wrong num of addresses");

    if (krb5_address_order(context, &range.val[0], &one.val[0]) == 0) {
	if (!match)
	    krb5_errx(context, 1, "match when one shouldn't be");
    } else {
	if (match)
	    krb5_errx(context, 1, "no match when one should be");
    }

    krb5_free_addresses(context, &range);
    krb5_free_addresses(context, &one);
}