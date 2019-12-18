#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_17__ {int /*<<< orphan*/  principal; } ;
struct TYPE_13__ {TYPE_7__ entry; } ;
typedef  TYPE_2__ hdb_entry_ex ;
struct TYPE_14__ {int /*<<< orphan*/  principal; } ;
typedef  TYPE_3__ hdb_entry_alias ;
struct TYPE_16__ {scalar_t__ (* hdb__put ) (int /*<<< orphan*/ ,TYPE_5__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {size_t len; int /*<<< orphan*/ * val; } ;
struct TYPE_15__ {TYPE_1__ aliases; } ;
typedef  TYPE_4__ HDB_Ext_Aliases ;
typedef  TYPE_5__ HDB ;

/* Variables and functions */
 scalar_t__ hdb_entry_alias2value (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ hdb_entry_get_aliases (TYPE_7__*,TYPE_4__ const**) ; 
 int /*<<< orphan*/  hdb_principal2key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_5__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
hdb_add_aliases(krb5_context context, HDB *db,
		unsigned flags, hdb_entry_ex *entry)
{
    const HDB_Ext_Aliases *aliases;
    krb5_error_code code;
    krb5_data key, value;
    size_t i;

    code = hdb_entry_get_aliases(&entry->entry, &aliases);
    if (code || aliases == NULL)
	return code;

    for (i = 0; i < aliases->aliases.len; i++) {
	hdb_entry_alias entryalias;
	entryalias.principal = entry->entry.principal;

	hdb_principal2key(context, &aliases->aliases.val[i], &key);
	code = hdb_entry_alias2value(context, &entryalias, &value);
	if (code) {
	    krb5_data_free(&key);
	    return code;
	}
	code = db->hdb__put(context, db, flags, key, value);
	krb5_data_free(&key);
	krb5_data_free(&value);
	if (code)
	    return code;
    }
    return 0;
}