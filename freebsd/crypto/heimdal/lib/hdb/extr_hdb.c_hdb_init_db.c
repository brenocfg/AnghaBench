#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ver ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_10__ {char* data; void* length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_11__ {scalar_t__ (* hdb_lock ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ;scalar_t__ (* hdb__put ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__,TYPE_1__) ;scalar_t__ (* hdb_unlock ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_2__ HDB ;

/* Variables and functions */
 int HDB_DB_FORMAT ; 
 scalar_t__ HDB_DB_FORMAT_ENTRY ; 
 scalar_t__ HDB_ERR_NOENTRY ; 
 int /*<<< orphan*/  HDB_WLOCK ; 
 scalar_t__ hdb_check_db_format (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 void* strlen (char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__,TYPE_1__) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,TYPE_2__*) ; 

krb5_error_code
hdb_init_db(krb5_context context, HDB *db)
{
    krb5_error_code ret, ret2;
    krb5_data tag;
    krb5_data version;
    char ver[32];

    ret = hdb_check_db_format(context, db);
    if(ret != HDB_ERR_NOENTRY)
	return ret;

    ret = db->hdb_lock(context, db, HDB_WLOCK);
    if (ret)
	return ret;

    tag.data = (void *)(intptr_t)HDB_DB_FORMAT_ENTRY;
    tag.length = strlen(tag.data);
    snprintf(ver, sizeof(ver), "%u", HDB_DB_FORMAT);
    version.data = ver;
    version.length = strlen(version.data) + 1; /* zero terminated */
    ret = (*db->hdb__put)(context, db, 0, tag, version);
    ret2 = db->hdb_unlock(context, db);
    if (ret) {
	if (ret2)
	    krb5_clear_error_message(context);
	return ret;
    }
    return ret2;
}