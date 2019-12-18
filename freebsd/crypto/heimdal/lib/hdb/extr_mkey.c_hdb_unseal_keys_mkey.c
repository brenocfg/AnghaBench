#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  hdb_master_key ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/ * val; } ;
struct TYPE_5__ {TYPE_1__ keys; } ;
typedef  TYPE_2__ hdb_entry ;

/* Variables and functions */
 scalar_t__ hdb_unseal_key_mkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

krb5_error_code
hdb_unseal_keys_mkey(krb5_context context, hdb_entry *ent, hdb_master_key mkey)
{
    size_t i;

    for(i = 0; i < ent->keys.len; i++){
	krb5_error_code ret;

	ret = hdb_unseal_key_mkey(context, &ent->keys.val[i], mkey);
	if (ret)
	    return ret;
    }
    return 0;
}