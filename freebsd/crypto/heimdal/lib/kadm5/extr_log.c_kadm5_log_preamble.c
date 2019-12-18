#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_6__ {int version; } ;
struct TYPE_5__ {TYPE_2__ log_context; } ;
typedef  TYPE_1__ kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;
typedef  TYPE_2__ kadm5_log_context ;
typedef  enum kadm_ops { ____Placeholder_kadm_ops } kadm_ops ;

/* Variables and functions */
 scalar_t__ kadm5_log_init (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int) ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static kadm5_ret_t
kadm5_log_preamble (kadm5_server_context *context,
		    krb5_storage *sp,
		    enum kadm_ops op)
{
    kadm5_log_context *log_context = &context->log_context;
    kadm5_ret_t kadm_ret;

    kadm_ret = kadm5_log_init (context);
    if (kadm_ret)
	return kadm_ret;

    krb5_store_int32 (sp, ++log_context->version);
    krb5_store_int32 (sp, time(NULL));
    krb5_store_int32 (sp, op);
    return 0;
}