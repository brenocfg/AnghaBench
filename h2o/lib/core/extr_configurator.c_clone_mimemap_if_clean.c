#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* mimemap; TYPE_1__* parent; } ;
typedef  TYPE_2__ h2o_configurator_context_t ;
struct TYPE_4__ {scalar_t__* mimemap; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_mem_release_shared (scalar_t__) ; 
 scalar_t__ h2o_mimemap_clone (scalar_t__) ; 

__attribute__((used)) static void clone_mimemap_if_clean(h2o_configurator_context_t *ctx)
{
    if (ctx->parent == NULL)
        return;
    if (*ctx->mimemap != *ctx->parent->mimemap)
        return;
    h2o_mem_release_shared(*ctx->mimemap);
    /* even after release, ctx->mimemap is still retained by the parent and therefore we can use it as the argument to clone */
    *ctx->mimemap = h2o_mimemap_clone(*ctx->mimemap);
}