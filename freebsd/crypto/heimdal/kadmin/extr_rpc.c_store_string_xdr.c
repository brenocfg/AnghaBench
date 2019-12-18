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
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_data_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  rk_UNCONST (char const*) ; 
 int store_data_xdr (int /*<<< orphan*/ *,TYPE_1__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
store_string_xdr(krb5_storage *sp, const char *str)
{
    krb5_data c;
    if (str) {
	c.data = rk_UNCONST(str);
	c.length = strlen(str) + 1;
    } else
	krb5_data_zero(&c);

    return store_data_xdr(sp, c);
}