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
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 scalar_t__ page_pt2off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline vm_paddr_t
page_pt2pa(vm_paddr_t pgpa, u_int pt1_idx)
{

	return (pgpa + page_pt2off(pt1_idx));
}