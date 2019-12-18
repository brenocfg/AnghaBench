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
struct vmbus_xact_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmbus_xact_ctx_free (struct vmbus_xact_ctx*) ; 
 int /*<<< orphan*/  vmbus_xact_ctx_orphan (struct vmbus_xact_ctx*) ; 

void
vmbus_xact_ctx_destroy(struct vmbus_xact_ctx *ctx)
{

	vmbus_xact_ctx_orphan(ctx);
	vmbus_xact_ctx_free(ctx);
}