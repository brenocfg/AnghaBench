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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct vio_dev {TYPE_1__ dev; } ;
struct iommu_table {unsigned long it_page_shift; unsigned long it_size; unsigned long it_offset; int it_blocksize; int /*<<< orphan*/ * it_ops; int /*<<< orphan*/  it_type; scalar_t__ it_busno; int /*<<< orphan*/  it_index; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_LPAR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long IOMMU_PAGE_SHIFT_4K ; 
 int /*<<< orphan*/  TCE_VB ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 struct iommu_table* iommu_init_table (struct iommu_table*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_table_lpar_multi_ops ; 
 int /*<<< orphan*/  iommu_table_pseries_ops ; 
 struct iommu_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_parse_dma_window (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned long*,unsigned long*) ; 

__attribute__((used)) static struct iommu_table *vio_build_iommu_table(struct vio_dev *dev)
{
	const __be32 *dma_window;
	struct iommu_table *tbl;
	unsigned long offset, size;

	dma_window = of_get_property(dev->dev.of_node,
				  "ibm,my-dma-window", NULL);
	if (!dma_window)
		return NULL;

	tbl = kzalloc(sizeof(*tbl), GFP_KERNEL);
	if (tbl == NULL)
		return NULL;

	of_parse_dma_window(dev->dev.of_node, dma_window,
			    &tbl->it_index, &offset, &size);

	/* TCE table size - measured in tce entries */
	tbl->it_page_shift = IOMMU_PAGE_SHIFT_4K;
	tbl->it_size = size >> tbl->it_page_shift;
	/* offset for VIO should always be 0 */
	tbl->it_offset = offset >> tbl->it_page_shift;
	tbl->it_busno = 0;
	tbl->it_type = TCE_VB;
	tbl->it_blocksize = 16;

	if (firmware_has_feature(FW_FEATURE_LPAR))
		tbl->it_ops = &iommu_table_lpar_multi_ops;
	else
		tbl->it_ops = &iommu_table_pseries_ops;

	return iommu_init_table(tbl, -1, 0, 0);
}