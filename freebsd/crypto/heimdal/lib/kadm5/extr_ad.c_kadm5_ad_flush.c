#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kadm5_ret_t ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ kadm5_ad_context ;

/* Variables and functions */
 int /*<<< orphan*/  KADM5_RPC_ERROR ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static kadm5_ret_t
kadm5_ad_flush(void *server_handle)
{
    kadm5_ad_context *context = server_handle;
    krb5_set_error_message(context->context, KADM5_RPC_ERROR, "Function not implemented");
    return KADM5_RPC_ERROR;
}