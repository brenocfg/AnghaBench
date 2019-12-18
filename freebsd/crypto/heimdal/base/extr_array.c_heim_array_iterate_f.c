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
typedef  TYPE_1__* heim_array_t ;
typedef  int /*<<< orphan*/  (* heim_array_iterator_f_t ) (int /*<<< orphan*/ ,void*) ;
struct TYPE_3__ {size_t len; int /*<<< orphan*/ * val; } ;

/* Variables and functions */

void
heim_array_iterate_f(heim_array_t array, heim_array_iterator_f_t fn, void *ctx)
{
    size_t n;
    for (n = 0; n < array->len; n++)
	fn(array->val[n], ctx);
}