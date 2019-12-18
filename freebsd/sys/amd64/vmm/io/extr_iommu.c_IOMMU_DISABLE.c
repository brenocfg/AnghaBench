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
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) () ;} ;

/* Variables and functions */
 scalar_t__ iommu_avail ; 
 TYPE_1__* ops ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static __inline void
IOMMU_DISABLE(void)
{

	if (ops != NULL && iommu_avail)
		(*ops->disable)();
}