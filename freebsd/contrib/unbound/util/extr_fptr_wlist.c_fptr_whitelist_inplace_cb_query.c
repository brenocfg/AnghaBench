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
typedef  int /*<<< orphan*/  inplace_cb_query_func_type ;

/* Variables and functions */
 int /*<<< orphan*/  ecs_whitelist_check ; 
 int /*<<< orphan*/  python_inplace_cb_query_generic ; 

int fptr_whitelist_inplace_cb_query(inplace_cb_query_func_type* fptr)
{
#ifdef CLIENT_SUBNET
	if(fptr == &ecs_whitelist_check)
		return 1;
#endif
#ifdef WITH_PYTHONMODULE
        if(fptr == &python_inplace_cb_query_generic)
                return 1;
#endif
	(void)fptr;
	return 0;
}