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
struct tracer_context {void** arr; size_t len; size_t n; } ;

/* Variables and functions */
 int /*<<< orphan*/  _Unwind_Backtrace (int /*<<< orphan*/ ,struct tracer_context*) ; 
 int /*<<< orphan*/  tracer ; 

size_t
backtrace(void **arr, size_t len)
{
	struct tracer_context ctx;

	ctx.arr = arr;
	ctx.len = len;
	ctx.n = (size_t)~0;

	_Unwind_Backtrace(tracer, &ctx);
	if (ctx.n != (size_t)~0 && ctx.n > 0)
		ctx.arr[--ctx.n] = NULL;	/* Skip frame below __start */

	return ctx.n;
}