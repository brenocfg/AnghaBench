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
typedef  int /*<<< orphan*/  linker_function_nameval_callback_t ;
typedef  int /*<<< orphan*/  linker_file_t ;

/* Variables and functions */
 int LINKER_EACH_FUNCTION_NAMEVAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int
linker_file_function_listall(linker_file_t lf,
    linker_function_nameval_callback_t callback_func, void *arg)
{
	return (LINKER_EACH_FUNCTION_NAMEVAL(lf, callback_func, arg));
}