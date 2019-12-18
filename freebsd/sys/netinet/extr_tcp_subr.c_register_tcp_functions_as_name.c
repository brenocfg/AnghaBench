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
struct tcp_function_block {char* tfb_tcp_block_name; } ;

/* Variables and functions */
 int register_tcp_functions_as_names (struct tcp_function_block*,int,char const**,int*) ; 

int
register_tcp_functions_as_name(struct tcp_function_block *blk, const char *name,
    int wait)
{
	const char *name_list[1];
	int num_names, rv;

	num_names = 1;
	if (name != NULL)
		name_list[0] = name;
	else
		name_list[0] = blk->tfb_tcp_block_name;
	rv = register_tcp_functions_as_names(blk, wait, name_list, &num_names);
	return (rv);
}