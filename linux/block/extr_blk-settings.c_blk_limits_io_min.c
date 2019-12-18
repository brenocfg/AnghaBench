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
struct queue_limits {unsigned int io_min; unsigned int logical_block_size; unsigned int physical_block_size; } ;

/* Variables and functions */

void blk_limits_io_min(struct queue_limits *limits, unsigned int min)
{
	limits->io_min = min;

	if (limits->io_min < limits->logical_block_size)
		limits->io_min = limits->logical_block_size;

	if (limits->io_min < limits->physical_block_size)
		limits->io_min = limits->physical_block_size;
}