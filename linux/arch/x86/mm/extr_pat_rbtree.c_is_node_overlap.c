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
typedef  scalar_t__ u64 ;
struct memtype {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */

__attribute__((used)) static int is_node_overlap(struct memtype *node, u64 start, u64 end)
{
	if (node->start >= end || node->end <= start)
		return 0;

	return 1;
}