#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int vm_pgoff; void* vm_page_prot; } ;
struct TYPE_6__ {int pfn; } ;
struct mlx4_ib_ucontext {TYPE_4__* hw_bar_info; TYPE_1__ uar; } ;
struct mlx4_ib_dev {TYPE_5__* dev; } ;
struct mlx4_clock_params {int offset; int /*<<< orphan*/  bar; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;
struct TYPE_7__ {scalar_t__ bf_reg_size; int num_uars; } ;
struct TYPE_10__ {TYPE_3__* persist; TYPE_2__ caps; } ;
struct TYPE_9__ {scalar_t__ vma; } ;
struct TYPE_8__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 size_t HW_BAR_BF ; 
 size_t HW_BAR_CLOCK ; 
 size_t HW_BAR_DB ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ io_remap_pfn_range (struct vm_area_struct*,scalar_t__,int,scalar_t__,void*) ; 
 int mlx4_get_internal_clock_params (TYPE_5__*,struct mlx4_clock_params*) ; 
 int /*<<< orphan*/  mlx4_ib_set_vma_data (struct vm_area_struct*,TYPE_4__*) ; 
 int pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* pgprot_noncached (void*) ; 
 void* pgprot_writecombine (void*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_ucontext* to_mucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int mlx4_ib_mmap(struct ib_ucontext *context, struct vm_area_struct *vma)
{
	struct mlx4_ib_dev *dev = to_mdev(context->device);
	struct mlx4_ib_ucontext *mucontext = to_mucontext(context);

	if (vma->vm_end - vma->vm_start != PAGE_SIZE)
		return -EINVAL;

	if (vma->vm_pgoff == 0) {
		/* We prevent double mmaping on same context */
		if (mucontext->hw_bar_info[HW_BAR_DB].vma)
			return -EINVAL;

		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

		if (io_remap_pfn_range(vma, vma->vm_start,
				       to_mucontext(context)->uar.pfn,
				       PAGE_SIZE, vma->vm_page_prot))
			return -EAGAIN;

		mlx4_ib_set_vma_data(vma, &mucontext->hw_bar_info[HW_BAR_DB]);

	} else if (vma->vm_pgoff == 1 && dev->dev->caps.bf_reg_size != 0) {
		/* We prevent double mmaping on same context */
		if (mucontext->hw_bar_info[HW_BAR_BF].vma)
			return -EINVAL;

		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

		if (io_remap_pfn_range(vma, vma->vm_start,
				       to_mucontext(context)->uar.pfn +
				       dev->dev->caps.num_uars,
				       PAGE_SIZE, vma->vm_page_prot))
			return -EAGAIN;

		mlx4_ib_set_vma_data(vma, &mucontext->hw_bar_info[HW_BAR_BF]);

	} else if (vma->vm_pgoff == 3) {
		struct mlx4_clock_params params;
		int ret;

		/* We prevent double mmaping on same context */
		if (mucontext->hw_bar_info[HW_BAR_CLOCK].vma)
			return -EINVAL;

		ret = mlx4_get_internal_clock_params(dev->dev, &params);

		if (ret)
			return ret;

		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
		if (io_remap_pfn_range(vma, vma->vm_start,
				       (pci_resource_start(dev->dev->persist->pdev,
							   params.bar) +
					params.offset)
				       >> PAGE_SHIFT,
				       PAGE_SIZE, vma->vm_page_prot))
			return -EAGAIN;

		mlx4_ib_set_vma_data(vma,
				     &mucontext->hw_bar_info[HW_BAR_CLOCK]);
	} else {
		return -EINVAL;
	}

	return 0;
}