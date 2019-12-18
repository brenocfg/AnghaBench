#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_4__ {int /*<<< orphan*/  log_context; } ;
typedef  TYPE_1__ kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;
typedef  int /*<<< orphan*/  kadm5_log_context ;

/* Variables and functions */
 scalar_t__ kadm5_log_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kadm5_log_postamble (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kadm5_log_preamble (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kadm_nop ; 
 int /*<<< orphan*/ * krb5_storage_emem () ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kadm5_ret_t
kadm5_log_nop (kadm5_server_context *context)
{
    krb5_storage *sp;
    kadm5_ret_t ret;
    kadm5_log_context *log_context = &context->log_context;

    sp = krb5_storage_emem();
    ret = kadm5_log_preamble (context, sp, kadm_nop);
    if (ret) {
	krb5_storage_free (sp);
	return ret;
    }
    krb5_store_int32 (sp, 0);
    krb5_store_int32 (sp, 0);
    ret = kadm5_log_postamble (log_context, sp);
    if (ret) {
	krb5_storage_free (sp);
	return ret;
    }
    ret = kadm5_log_flush (log_context, sp);
    krb5_storage_free (sp);

    return ret;
}