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
struct TYPE_5__ {int /*<<< orphan*/  original; int /*<<< orphan*/  baton; int /*<<< orphan*/  (* freefunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ simple_context_t ;
struct TYPE_6__ {TYPE_1__* data; } ;
typedef  TYPE_2__ serf_bucket_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_default_destroy_and_data (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serf_simple_destroy(serf_bucket_t *bucket)
{
    simple_context_t *ctx = bucket->data;

    if (ctx->freefunc)
        (*ctx->freefunc)(ctx->baton, ctx->original);

    serf_default_destroy_and_data(bucket);
}