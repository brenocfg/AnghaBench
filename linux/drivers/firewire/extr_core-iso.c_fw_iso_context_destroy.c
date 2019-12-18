#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fw_iso_context {TYPE_2__* card; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free_iso_context ) (struct fw_iso_context*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct fw_iso_context*) ; 

void fw_iso_context_destroy(struct fw_iso_context *ctx)
{
	ctx->card->driver->free_iso_context(ctx);
}