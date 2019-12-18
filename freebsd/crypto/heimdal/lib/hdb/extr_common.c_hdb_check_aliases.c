#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_18__ {int /*<<< orphan*/  principal; } ;
struct TYPE_14__ {TYPE_8__ entry; } ;
typedef  TYPE_2__ hdb_entry_ex ;
struct TYPE_15__ {int /*<<< orphan*/  principal; } ;
typedef  TYPE_3__ hdb_entry_alias ;
struct TYPE_17__ {int (* hdb__get ) (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_13__ {size_t len; int /*<<< orphan*/ * val; } ;
struct TYPE_16__ {TYPE_1__ aliases; } ;
typedef  TYPE_4__ HDB_Ext_Aliases ;
typedef  TYPE_5__ HDB ;

/* Variables and functions */
 int ASN1_BAD_ID ; 
 int HDB_ERR_EXISTS ; 
 int HDB_ERR_NOENTRY ; 
 int /*<<< orphan*/  free_hdb_entry_alias (TYPE_3__*) ; 
 int hdb_entry_get_aliases (TYPE_8__*,TYPE_4__ const**) ; 
 int /*<<< orphan*/  hdb_principal2key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hdb_value2entry_alias (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 
 int krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
hdb_check_aliases(krb5_context context, HDB *db, hdb_entry_ex *entry)
{
    const HDB_Ext_Aliases *aliases;
    int code;
    size_t i;

    /* check if new aliases already is used */

    code = hdb_entry_get_aliases(&entry->entry, &aliases);
    if (code)
	return code;

    for (i = 0; aliases && i < aliases->aliases.len; i++) {
	hdb_entry_alias alias;
	krb5_data akey, value;

	hdb_principal2key(context, &aliases->aliases.val[i], &akey);
	code = db->hdb__get(context, db, akey, &value);
	krb5_data_free(&akey);
	if (code == HDB_ERR_NOENTRY)
	    continue;
	else if (code)
	    return code;

	code = hdb_value2entry_alias(context, &value, &alias);
	krb5_data_free(&value);

	if (code == ASN1_BAD_ID)
	    return HDB_ERR_EXISTS;
	else if (code)
	    return code;

	code = krb5_principal_compare(context, alias.principal,
				      entry->entry.principal);
	free_hdb_entry_alias(&alias);
	if (code == 0)
	    return HDB_ERR_EXISTS;
    }
    return 0;
}