#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  HDB ;

/* Variables and functions */
 int /*<<< orphan*/  HDB_ERR_CANT_LOCK_DB ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static krb5_error_code
hdb_sqlite_unlock(krb5_context context, HDB *db)
{
    krb5_set_error_message(context, HDB_ERR_CANT_LOCK_DB,
			  "unlock not implemented");
    return HDB_ERR_CANT_LOCK_DB;
}