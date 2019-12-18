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
struct vm_radix_node {int dummy; } ;
struct vm_radix {uintptr_t rt_root; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
vm_radix_setroot(struct vm_radix *rtree, struct vm_radix_node *rnode)
{

	rtree->rt_root = (uintptr_t)rnode;
}