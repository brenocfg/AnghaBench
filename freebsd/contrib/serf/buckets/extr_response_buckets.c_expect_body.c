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
struct TYPE_4__ {int code; } ;
struct TYPE_5__ {TYPE_1__ sl; scalar_t__ head_req; } ;
typedef  TYPE_2__ response_context_t ;

/* Variables and functions */

__attribute__((used)) static int expect_body(response_context_t *ctx)
{
    if (ctx->head_req)
        return 0;

    /* 100 Continue and 101 Switching Protocols */
    if (ctx->sl.code >= 100 && ctx->sl.code < 200)
        return 0;

    /* 204 No Content */
    if (ctx->sl.code == 204)
        return 0;

    /* 205? */

    /* 304 Not Modified */
    if (ctx->sl.code == 304)
        return 0;

    return 1;
}