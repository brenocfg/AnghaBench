#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  hdb_entry ;
struct TYPE_10__ {scalar_t__ (* hdb__get ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* hdb__del ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {size_t len; int /*<<< orphan*/ * val; } ;
struct TYPE_9__ {TYPE_1__ aliases; } ;
typedef  TYPE_2__ HDB_Ext_Aliases ;
typedef  TYPE_3__ HDB ;

/* Variables and functions */
 scalar_t__ HDB_ERR_NOENTRY ; 
 int /*<<< orphan*/  free_hdb_entry (int /*<<< orphan*/ *) ; 
 scalar_t__ hdb_entry_get_aliases (int /*<<< orphan*/ *,TYPE_2__ const**) ; 
 int /*<<< orphan*/  hdb_principal2key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hdb_value2entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
hdb_remove_aliases(krb5_context context, HDB *db, krb5_data *key)
{
    const HDB_Ext_Aliases *aliases;
    krb5_error_code code;
    hdb_entry oldentry;
    krb5_data value;
    size_t i;

    code = db->hdb__get(context, db, *key, &value);
    if (code == HDB_ERR_NOENTRY)
	return 0;
    else if (code)
	return code;

    code = hdb_value2entry(context, &value, &oldentry);
    krb5_data_free(&value);
    if (code)
	return code;

    code = hdb_entry_get_aliases(&oldentry, &aliases);
    if (code || aliases == NULL) {
	free_hdb_entry(&oldentry);
	return code;
    }
    for (i = 0; i < aliases->aliases.len; i++) {
	krb5_data akey;

	hdb_principal2key(context, &aliases->aliases.val[i], &akey);
	code = db->hdb__del(context, db, akey);
	krb5_data_free(&akey);
	if (code) {
	    free_hdb_entry(&oldentry);
	    return code;
	}
    }
    free_hdb_entry(&oldentry);
    return 0;
}