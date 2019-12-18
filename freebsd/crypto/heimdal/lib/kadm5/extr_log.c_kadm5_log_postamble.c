#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;
struct TYPE_3__ {int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ kadm5_log_context ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kadm5_ret_t
kadm5_log_postamble (kadm5_log_context *context,
		     krb5_storage *sp)
{
    krb5_store_int32 (sp, context->version);
    return 0;
}