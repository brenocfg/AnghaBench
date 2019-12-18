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
typedef  scalar_t__ krb5_error_code ;
struct TYPE_10__ {void* data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_11__ {scalar_t__ (* hdb_unlock ) (int /*<<< orphan*/ ,TYPE_2__*) ;scalar_t__ (* hdb__get ) (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__,TYPE_1__*) ;scalar_t__ (* hdb_lock ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ HDB ;

/* Variables and functions */
 unsigned int HDB_DB_FORMAT ; 
 scalar_t__ HDB_DB_FORMAT_ENTRY ; 
 scalar_t__ HDB_ERR_BADVERSION ; 
 int /*<<< orphan*/  HDB_RLOCK ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int sscanf (void*,char*,unsigned int*) ; 
 int /*<<< orphan*/  strlen (void*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__,TYPE_1__*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,TYPE_2__*) ; 

krb5_error_code
hdb_check_db_format(krb5_context context, HDB *db)
{
    krb5_data tag;
    krb5_data version;
    krb5_error_code ret, ret2;
    unsigned ver;
    int foo;

    ret = db->hdb_lock(context, db, HDB_RLOCK);
    if (ret)
	return ret;

    tag.data = (void *)(intptr_t)HDB_DB_FORMAT_ENTRY;
    tag.length = strlen(tag.data);
    ret = (*db->hdb__get)(context, db, tag, &version);
    ret2 = db->hdb_unlock(context, db);
    if(ret)
	return ret;
    if (ret2)
	return ret2;
    foo = sscanf(version.data, "%u", &ver);
    krb5_data_free (&version);
    if (foo != 1)
	return HDB_ERR_BADVERSION;
    if(ver != HDB_DB_FORMAT)
	return HDB_ERR_BADVERSION;
    return 0;
}