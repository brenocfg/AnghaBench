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

/* Variables and functions */
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct vm_radix_node*) ; 
 int /*<<< orphan*/  vm_radix_node_zone ; 

__attribute__((used)) static __inline void
vm_radix_node_put(struct vm_radix_node *rnode)
{

	uma_zfree(vm_radix_node_zone, rnode);
}