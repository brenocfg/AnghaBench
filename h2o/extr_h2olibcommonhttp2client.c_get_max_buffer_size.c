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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {size_t max_buffer_size; } ;
typedef  TYPE_1__ h2o_httpclient_ctx_t ;

/* Variables and functions */
 size_t INT32_MAX ; 

__attribute__((used)) static uint32_t get_max_buffer_size(h2o_httpclient_ctx_t *ctx)
{
    size_t sz = ctx->max_buffer_size;
    if (sz > INT32_MAX)
        sz = INT32_MAX;
    return (uint32_t)sz;
}