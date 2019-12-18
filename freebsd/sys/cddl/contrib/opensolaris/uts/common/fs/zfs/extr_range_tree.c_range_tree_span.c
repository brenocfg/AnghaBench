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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  range_tree_t ;

/* Variables and functions */
 scalar_t__ range_tree_max (int /*<<< orphan*/ *) ; 
 scalar_t__ range_tree_min (int /*<<< orphan*/ *) ; 

uint64_t
range_tree_span(range_tree_t *rt)
{
	return (range_tree_max(rt) - range_tree_min(rt));
}