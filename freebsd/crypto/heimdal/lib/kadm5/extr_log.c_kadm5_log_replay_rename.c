#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  target_ent ;
typedef  size_t off_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;
struct TYPE_14__ {int /*<<< orphan*/  context; TYPE_4__* db; } ;
typedef  TYPE_2__ kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;
struct TYPE_15__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_3__ hdb_entry_ex ;
struct TYPE_16__ {scalar_t__ (* hdb_remove ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ;scalar_t__ (* hdb_store ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  hdb_free_entry (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ hdb_value2entry (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_data_alloc (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_ret_principal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*,long) ; 
 int /*<<< orphan*/  krb5_storage_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t krb5_storage_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kadm5_ret_t
kadm5_log_replay_rename (kadm5_server_context *context,
			 uint32_t ver,
			 uint32_t len,
			 krb5_storage *sp)
{
    krb5_error_code ret;
    krb5_principal source;
    hdb_entry_ex target_ent;
    krb5_data value;
    off_t off;
    size_t princ_len, data_len;

    memset(&target_ent, 0, sizeof(target_ent));

    off = krb5_storage_seek(sp, 0, SEEK_CUR);
    ret = krb5_ret_principal (sp, &source);
    if (ret) {
	krb5_set_error_message(context->context, ret, "Failed to read renamed "
			       "principal in log, version: %ld", (long)ver);
	return ret;
    }
    princ_len = krb5_storage_seek(sp, 0, SEEK_CUR) - off;
    data_len = len - princ_len;
    ret = krb5_data_alloc (&value, data_len);
    if (ret) {
	krb5_free_principal (context->context, source);
	return ret;
    }
    krb5_storage_read (sp, value.data, data_len);
    ret = hdb_value2entry (context->context, &value, &target_ent.entry);
    krb5_data_free(&value);
    if (ret) {
	krb5_free_principal (context->context, source);
	return ret;
    }
    ret = context->db->hdb_store (context->context, context->db,
				  0, &target_ent);
    hdb_free_entry (context->context, &target_ent);
    if (ret) {
	krb5_free_principal (context->context, source);
	return ret;
    }
    ret = context->db->hdb_remove (context->context, context->db, source);
    krb5_free_principal (context->context, source);
    return ret;
}