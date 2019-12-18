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
typedef  int off_t ;

/* Variables and functions */
 int MLX5_IB_MMAP_CMD_SHIFT ; 

__attribute__((used)) static inline void set_command(int command, off_t *offset)
{
	*offset |= (command << MLX5_IB_MMAP_CMD_SHIFT);
}