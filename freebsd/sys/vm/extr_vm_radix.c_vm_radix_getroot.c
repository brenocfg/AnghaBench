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
struct vm_radix {scalar_t__ rt_root; } ;

/* Variables and functions */

__attribute__((used)) static __inline struct vm_radix_node *
vm_radix_getroot(struct vm_radix *rtree)
{

	return ((struct vm_radix_node *)rtree->rt_root);
}