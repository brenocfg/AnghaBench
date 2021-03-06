#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;
struct TYPE_9__ {int /*<<< orphan*/  context; int /*<<< orphan*/  log_context; } ;
typedef  TYPE_2__ kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;
typedef  int /*<<< orphan*/  kadm5_log_context ;
typedef  int /*<<< orphan*/  hdb_entry ;

/* Variables and functions */
 scalar_t__ hdb_entry2value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ kadm5_log_end (TYPE_2__*) ; 
 scalar_t__ kadm5_log_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kadm5_log_postamble (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kadm5_log_preamble (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kadm_create ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * krb5_storage_emem () ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kadm5_ret_t
kadm5_log_create (kadm5_server_context *context,
		  hdb_entry *ent)
{
    krb5_storage *sp;
    kadm5_ret_t ret;
    krb5_data value;
    kadm5_log_context *log_context = &context->log_context;

    sp = krb5_storage_emem();
    ret = hdb_entry2value (context->context, ent, &value);
    if (ret) {
	krb5_storage_free(sp);
	return ret;
    }
    ret = kadm5_log_preamble (context, sp, kadm_create);
    if (ret) {
	krb5_data_free (&value);
	krb5_storage_free(sp);
	return ret;
    }
    krb5_store_int32 (sp, value.length);
    krb5_storage_write(sp, value.data, value.length);
    krb5_store_int32 (sp, value.length);
    krb5_data_free (&value);
    ret = kadm5_log_postamble (log_context, sp);
    if (ret) {
	krb5_storage_free (sp);
	return ret;
    }
    ret = kadm5_log_flush (log_context, sp);
    krb5_storage_free (sp);
    if (ret)
	return ret;
    ret = kadm5_log_end (context);
    return ret;
}