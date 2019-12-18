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
struct TYPE_2__ {void (* std_func ) () ;} ;
struct atexit_fn {int /*<<< orphan*/ * fn_dso; int /*<<< orphan*/ * fn_arg; TYPE_1__ fn_ptr; int /*<<< orphan*/  fn_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATEXIT_FN_STD ; 
 int atexit_register (struct atexit_fn*) ; 

int
atexit(void (*func)(void))
{
	struct atexit_fn fn;
	int error;

	fn.fn_type = ATEXIT_FN_STD;
	fn.fn_ptr.std_func = func;
	fn.fn_arg = NULL;
	fn.fn_dso = NULL;

	error = atexit_register(&fn);
	return (error);
}