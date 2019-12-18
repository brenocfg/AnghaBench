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
typedef  int boolean_t ;

/* Variables and functions */
 uintptr_t VM_RADIX_ISLEAF ; 

__attribute__((used)) static __inline boolean_t
vm_radix_isleaf(struct vm_radix_node *rnode)
{

	return (((uintptr_t)rnode & VM_RADIX_ISLEAF) != 0);
}