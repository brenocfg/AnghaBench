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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove_mapping ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ iommu_avail ; 
 TYPE_1__* ops ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline uint64_t
IOMMU_REMOVE_MAPPING(void *domain, vm_paddr_t gpa, uint64_t len)
{

	if (ops != NULL && iommu_avail)
		return ((*ops->remove_mapping)(domain, gpa, len));
	else
		return (len);		/* XXX */
}