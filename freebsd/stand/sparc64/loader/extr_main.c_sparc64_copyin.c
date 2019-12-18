#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* mmu_mapin ) (scalar_t__,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 TYPE_1__* mmu_ops ; 
 int /*<<< orphan*/  stub1 (scalar_t__,size_t) ; 

__attribute__((used)) static ssize_t
sparc64_copyin(const void *src, vm_offset_t dest, size_t len)
{

	mmu_ops->mmu_mapin(dest, len);
	memcpy((void *)dest, src, len);
	return (len);
}