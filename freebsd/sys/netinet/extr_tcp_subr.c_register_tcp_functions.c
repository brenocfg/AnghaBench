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
struct tcp_function_block {int dummy; } ;

/* Variables and functions */
 int register_tcp_functions_as_name (struct tcp_function_block*,int /*<<< orphan*/ *,int) ; 

int
register_tcp_functions(struct tcp_function_block *blk, int wait)
{

	return (register_tcp_functions_as_name(blk, NULL, wait));
}