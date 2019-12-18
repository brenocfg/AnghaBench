#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int it_size; unsigned long it_base; int it_blocksize; int /*<<< orphan*/  it_map; int /*<<< orphan*/ * it_ops; scalar_t__ it_index; int /*<<< orphan*/  it_page_shift; scalar_t__ it_offset; scalar_t__ it_busno; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_PAGE_SHIFT_4K ; 
 scalar_t__ dart_tablebase ; 
 int dart_tablesize ; 
 int /*<<< orphan*/  iommu_dart_ops ; 
 int /*<<< orphan*/  iommu_init_table (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ iommu_table_dart ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iommu_table_dart_setup(void)
{
	iommu_table_dart.it_busno = 0;
	iommu_table_dart.it_offset = 0;
	/* it_size is in number of entries */
	iommu_table_dart.it_size = dart_tablesize / sizeof(u32);
	iommu_table_dart.it_page_shift = IOMMU_PAGE_SHIFT_4K;

	/* Initialize the common IOMMU code */
	iommu_table_dart.it_base = (unsigned long)dart_tablebase;
	iommu_table_dart.it_index = 0;
	iommu_table_dart.it_blocksize = 1;
	iommu_table_dart.it_ops = &iommu_dart_ops;
	iommu_init_table(&iommu_table_dart, -1, 0, 0);

	/* Reserve the last page of the DART to avoid possible prefetch
	 * past the DART mapped area
	 */
	set_bit(iommu_table_dart.it_size - 1, iommu_table_dart.it_map);
}