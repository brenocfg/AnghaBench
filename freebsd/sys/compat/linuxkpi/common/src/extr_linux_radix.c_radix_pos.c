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
 long RADIX_TREE_MAP_MASK ; 
 int RADIX_TREE_MAP_SHIFT ; 

__attribute__((used)) static inline int
radix_pos(long id, int height)
{
	return (id >> (RADIX_TREE_MAP_SHIFT * height)) & RADIX_TREE_MAP_MASK;
}