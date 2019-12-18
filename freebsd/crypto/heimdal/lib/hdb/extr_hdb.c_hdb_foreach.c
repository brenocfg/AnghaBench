#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ (* hdb_foreach_func_t ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  hdb_entry_ex ;
struct TYPE_8__ {scalar_t__ (* hdb_firstkey ) (int /*<<< orphan*/ ,TYPE_1__*,unsigned int,int /*<<< orphan*/ *) ;scalar_t__ (* hdb_nextkey ) (int /*<<< orphan*/ ,TYPE_1__*,unsigned int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ HDB ;

/* Variables and functions */
 scalar_t__ HDB_ERR_NOENTRY ; 
 int /*<<< orphan*/  hdb_free_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_1__*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,TYPE_1__*,unsigned int,int /*<<< orphan*/ *) ; 

krb5_error_code
hdb_foreach(krb5_context context,
	    HDB *db,
	    unsigned flags,
	    hdb_foreach_func_t func,
	    void *data)
{
    krb5_error_code ret;
    hdb_entry_ex entry;
    ret = db->hdb_firstkey(context, db, flags, &entry);
    if (ret == 0)
	krb5_clear_error_message(context);
    while(ret == 0){
	ret = (*func)(context, db, &entry, data);
	hdb_free_entry(context, &entry);
	if(ret == 0)
	    ret = db->hdb_nextkey(context, db, flags, &entry);
    }
    if(ret == HDB_ERR_NOENTRY)
	ret = 0;
    return ret;
}