#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_key_usage ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* hdb_master_key ;
struct TYPE_3__ {int /*<<< orphan*/  crypto; } ;

/* Variables and functions */
 int krb5_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *) ; 

int
_hdb_mkey_decrypt(krb5_context context, hdb_master_key key,
		  krb5_key_usage usage,
		  void *ptr, size_t size, krb5_data *res)
{
    return krb5_decrypt(context, key->crypto, usage,
			ptr, size, res);
}