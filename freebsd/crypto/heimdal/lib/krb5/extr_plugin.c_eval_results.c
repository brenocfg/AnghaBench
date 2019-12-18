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
struct plug {int /*<<< orphan*/  ctx; int /*<<< orphan*/  dataptr; } ;
struct iter_ctx {scalar_t__ ret; scalar_t__ (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  userctx; int /*<<< orphan*/  context; } ;
typedef  struct plug* heim_object_t ;

/* Variables and functions */
 scalar_t__ KRB5_PLUGIN_NO_HANDLE ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
eval_results(heim_object_t value, void *ctx)
{
    struct plug *pl = value;
    struct iter_ctx *s = ctx;

    if (s->ret != KRB5_PLUGIN_NO_HANDLE)
	return;

    s->ret = s->func(s->context, pl->dataptr, pl->ctx, s->userctx);
}