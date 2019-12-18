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

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 char** blk_op_name ; 

inline const char *blk_op_str(unsigned int op)
{
	const char *op_str = "UNKNOWN";

	if (op < ARRAY_SIZE(blk_op_name) && blk_op_name[op])
		op_str = blk_op_name[op];

	return op_str;
}