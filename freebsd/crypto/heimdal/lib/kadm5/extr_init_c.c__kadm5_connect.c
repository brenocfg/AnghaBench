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
typedef  int /*<<< orphan*/  kadm5_ret_t ;
struct TYPE_3__ {int sock; } ;
typedef  TYPE_1__ kadm5_client_context ;

/* Variables and functions */
 int /*<<< orphan*/  kadm_connect (TYPE_1__*) ; 

kadm5_ret_t
_kadm5_connect(void *handle)
{
    kadm5_client_context *ctx = handle;
    if(ctx->sock == -1)
	return kadm_connect(ctx);
    return 0;
}