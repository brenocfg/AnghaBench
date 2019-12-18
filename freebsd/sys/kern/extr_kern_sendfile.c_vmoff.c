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
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  trunc_page (scalar_t__) ; 

__attribute__((used)) static inline vm_ooffset_t
vmoff(int i, off_t off)
{

	if (i == 0)
		return ((vm_ooffset_t)off);

	return (trunc_page(off + i * PAGE_SIZE));
}