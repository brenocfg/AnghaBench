#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  TYPE_1__* hx509_validate_ctx ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* vprint_func ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
validate_vprint(void *c, const char *fmt, va_list va)
{
    hx509_validate_ctx ctx = c;
    if (ctx->vprint_func == NULL)
	return;
    (ctx->vprint_func)(ctx->ctx, fmt, va);
}