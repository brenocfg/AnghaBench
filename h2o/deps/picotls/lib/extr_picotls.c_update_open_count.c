#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_3__* update_open_count; } ;
typedef  TYPE_1__ ptls_context_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* cb ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_open_count(ptls_context_t *ctx, ssize_t delta)
{
    if (ctx->update_open_count != NULL)
        ctx->update_open_count->cb(ctx->update_open_count, delta);
}