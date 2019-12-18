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
typedef  int /*<<< orphan*/  range_tree_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ range_tree_space (int /*<<< orphan*/ *) ; 

boolean_t
range_tree_is_empty(range_tree_t *rt)
{
	ASSERT(rt != NULL);
	return (range_tree_space(rt) == 0);
}