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
struct TYPE_4__ {size_t count; int includes_g; size_t offset1; size_t offset2; int /*<<< orphan*/ * scalars; int /*<<< orphan*/ * output; int /*<<< orphan*/  scratch; TYPE_1__* ctx; int /*<<< orphan*/  (* ecmult_multi ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t) ;} ;
typedef  TYPE_2__ bench_data ;
struct TYPE_3__ {int /*<<< orphan*/  ecmult_ctx; int /*<<< orphan*/  error_callback; } ;

/* Variables and functions */
 size_t ITERS ; 
 size_t POINTS ; 
 int /*<<< orphan*/  bench_callback ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static void bench_ecmult(void* arg) {
    bench_data* data = (bench_data*)arg;

    size_t count = data->count;
    int includes_g = data->includes_g;
    size_t iters = 1 + ITERS / count;
    size_t iter;

    for (iter = 0; iter < iters; ++iter) {
        data->ecmult_multi(&data->ctx->error_callback, &data->ctx->ecmult_ctx, data->scratch, &data->output[iter], data->includes_g ? &data->scalars[data->offset1] : NULL, bench_callback, arg, count - includes_g);
        data->offset1 = (data->offset1 + count) % POINTS;
        data->offset2 = (data->offset2 + count - 1) % POINTS;
    }
}