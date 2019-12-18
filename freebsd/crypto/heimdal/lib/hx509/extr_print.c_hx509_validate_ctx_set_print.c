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
typedef  int /*<<< orphan*/  hx509_vprint_func ;
typedef  TYPE_1__* hx509_validate_ctx ;
struct TYPE_3__ {void* ctx; int /*<<< orphan*/  vprint_func; } ;

/* Variables and functions */

void
hx509_validate_ctx_set_print(hx509_validate_ctx ctx,
			     hx509_vprint_func func,
			     void *c)
{
    ctx->vprint_func = func;
    ctx->ctx = c;
}