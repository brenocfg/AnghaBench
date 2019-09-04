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
struct argv_array {scalar_t__ alloc; scalar_t__ argc; int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  empty_argv ; 

void argv_array_init(struct argv_array *array)
{
	array->argv = empty_argv;
	array->argc = 0;
	array->alloc = 0;
}