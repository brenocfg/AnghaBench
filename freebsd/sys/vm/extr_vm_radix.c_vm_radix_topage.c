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
typedef  int /*<<< orphan*/  vm_page_t ;
struct vm_radix_node {int dummy; } ;

/* Variables and functions */
 uintptr_t VM_RADIX_FLAGS ; 

__attribute__((used)) static __inline vm_page_t
vm_radix_topage(struct vm_radix_node *rnode)
{

	return ((vm_page_t)((uintptr_t)rnode & ~VM_RADIX_FLAGS));
}