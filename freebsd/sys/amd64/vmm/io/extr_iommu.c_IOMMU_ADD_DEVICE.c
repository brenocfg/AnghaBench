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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* add_device ) (void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ iommu_avail ; 
 TYPE_1__* ops ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
IOMMU_ADD_DEVICE(void *domain, uint16_t rid)
{

	if (ops != NULL && iommu_avail)
		(*ops->add_device)(domain, rid);
}