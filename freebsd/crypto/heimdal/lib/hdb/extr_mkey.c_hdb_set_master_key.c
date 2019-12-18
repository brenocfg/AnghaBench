#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  hdb_master_key ;
struct TYPE_7__ {int hdb_master_key_set; int /*<<< orphan*/  hdb_master_key; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_2__ keyvalue; } ;
typedef  TYPE_3__ HDB ;

/* Variables and functions */
 int /*<<< orphan*/  des_set_random_generator_seed (int /*<<< orphan*/ ) ; 
 scalar_t__ hdb_process_master_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

krb5_error_code
hdb_set_master_key (krb5_context context,
		    HDB *db,
		    krb5_keyblock *key)
{
    krb5_error_code ret;
    hdb_master_key mkey;

    ret = hdb_process_master_key(context, 0, key, 0, &mkey);
    if (ret)
	return ret;
    db->hdb_master_key = mkey;
#if 0 /* XXX - why? */
    des_set_random_generator_seed(key.keyvalue.data);
#endif
    db->hdb_master_key_set = 1;
    return 0;
}