#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_5__ {int /*<<< orphan*/ * key_data_contents; int /*<<< orphan*/ * key_data_length; int /*<<< orphan*/ * key_data_type; int /*<<< orphan*/  key_data_kvno; int /*<<< orphan*/  key_data_ver; } ;
typedef  TYPE_1__ krb5_key_data ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_store_data (int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kadm5_ret_t
kadm5_store_key_data(krb5_storage *sp,
		     krb5_key_data *key)
{
    krb5_data c;
    krb5_store_int32(sp, key->key_data_ver);
    krb5_store_int32(sp, key->key_data_kvno);
    krb5_store_int32(sp, key->key_data_type[0]);
    c.length = key->key_data_length[0];
    c.data = key->key_data_contents[0];
    krb5_store_data(sp, c);
    krb5_store_int32(sp, key->key_data_type[1]);
    c.length = key->key_data_length[1];
    c.data = key->key_data_contents[1];
    krb5_store_data(sp, c);
    return 0;
}