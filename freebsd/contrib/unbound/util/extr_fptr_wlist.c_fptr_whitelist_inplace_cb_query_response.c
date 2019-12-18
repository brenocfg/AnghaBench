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
typedef  int /*<<< orphan*/  inplace_cb_query_response_func_type ;

/* Variables and functions */
 int /*<<< orphan*/  ecs_query_response ; 

int fptr_whitelist_inplace_cb_query_response(
	inplace_cb_query_response_func_type* fptr)
{
#ifdef CLIENT_SUBNET
	if(fptr == &ecs_query_response)
		return 1;
#else
	(void)fptr;
#endif
	return 0;
}