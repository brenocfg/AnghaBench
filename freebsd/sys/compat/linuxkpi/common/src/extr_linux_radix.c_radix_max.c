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
struct radix_tree_root {unsigned long height; } ;

/* Variables and functions */
 unsigned long RADIX_TREE_MAP_SHIFT ; 

__attribute__((used)) static inline unsigned long
radix_max(struct radix_tree_root *root)
{
	return ((1UL << (root->height * RADIX_TREE_MAP_SHIFT)) - 1UL);
}