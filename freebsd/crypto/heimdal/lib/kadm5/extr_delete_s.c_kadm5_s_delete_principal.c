#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
struct TYPE_16__ {TYPE_4__* db; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;
struct TYPE_15__ {scalar_t__ immutable; } ;
struct TYPE_14__ {TYPE_1__ flags; } ;
struct TYPE_17__ {TYPE_12__ entry; } ;
typedef  TYPE_3__ hdb_entry_ex ;
typedef  int /*<<< orphan*/  ent ;
struct TYPE_18__ {scalar_t__ (* hdb_open ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* hdb_fetch_kvno ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_3__*) ;scalar_t__ (* hdb_remove ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* hdb_close ) (int /*<<< orphan*/ ,TYPE_4__*) ;} ;

/* Variables and functions */
 scalar_t__ HDB_ERR_NOENTRY ; 
 int HDB_F_ADMIN_DATA ; 
 int HDB_F_DECRYPT ; 
 int HDB_F_GET_ANY ; 
 scalar_t__ KADM5_PROTECT_PRINCIPAL ; 
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ _kadm5_error_code (scalar_t__) ; 
 int /*<<< orphan*/  hdb_free_entry (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ hdb_seal_keys (int /*<<< orphan*/ ,TYPE_4__*,TYPE_12__*) ; 
 int /*<<< orphan*/  kadm5_log_delete (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,TYPE_4__*) ; 

kadm5_ret_t
kadm5_s_delete_principal(void *server_handle, krb5_principal princ)
{
    kadm5_server_context *context = server_handle;
    kadm5_ret_t ret;
    hdb_entry_ex ent;

    memset(&ent, 0, sizeof(ent));
    ret = context->db->hdb_open(context->context, context->db, O_RDWR, 0);
    if(ret) {
	krb5_warn(context->context, ret, "opening database");
	return ret;
    }
    ret = context->db->hdb_fetch_kvno(context->context, context->db, princ,
				      HDB_F_DECRYPT|HDB_F_GET_ANY|HDB_F_ADMIN_DATA, 0, &ent);
    if(ret == HDB_ERR_NOENTRY)
	goto out;
    if(ent.entry.flags.immutable) {
	ret = KADM5_PROTECT_PRINCIPAL;
	goto out2;
    }

    ret = hdb_seal_keys(context->context, context->db, &ent.entry);
    if (ret)
	goto out2;

    ret = context->db->hdb_remove(context->context, context->db, princ);
    if (ret)
	goto out2;

    kadm5_log_delete (context, princ);

out2:
    hdb_free_entry(context->context, &ent);
out:
    context->db->hdb_close(context->context, context->db);
    return _kadm5_error_code(ret);
}