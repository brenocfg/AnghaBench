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
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_pgoff; } ;
struct mlx5_uuar_info {unsigned long num_uars; TYPE_1__* uars; } ;
struct mlx5_ib_ucontext {struct mlx5_uuar_info uuari; } ;
struct mlx5_ib_dev {int dummy; } ;
typedef  int phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  enum mlx5_ib_mmap_cmd { ____Placeholder_mlx5_ib_mmap_cmd } mlx5_ib_mmap_cmd ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EPERM ; 
#define  MLX5_IB_MMAP_NC_PAGE 130 
#define  MLX5_IB_MMAP_REGULAR_PAGE 129 
#define  MLX5_IB_MMAP_WC_PAGE 128 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long get_index (int /*<<< orphan*/ ) ; 
 int io_remap_pfn_range (struct vm_area_struct*,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*,int,unsigned long long,int*,int /*<<< orphan*/ ) ; 
 int mlx5_ib_set_vma_data (struct vm_area_struct*,struct mlx5_ib_ucontext*) ; 
 int /*<<< orphan*/  mmap_cmd2str (int) ; 
 int /*<<< orphan*/  pat_enabled () ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int uar_index2pfn (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uar_mmap(struct mlx5_ib_dev *dev, enum mlx5_ib_mmap_cmd cmd,
		    struct vm_area_struct *vma,
		    struct mlx5_ib_ucontext *context)
{
	struct mlx5_uuar_info *uuari = &context->uuari;
	int err;
	unsigned long idx;
	phys_addr_t pfn, pa;
	pgprot_t prot;

	switch (cmd) {
	case MLX5_IB_MMAP_WC_PAGE:
/* Some architectures don't support WC memory */
#if defined(CONFIG_X86)
		if (!pat_enabled())
			return -EPERM;
#elif !(defined(CONFIG_PPC) || (defined(CONFIG_ARM) && defined(CONFIG_MMU)))
			return -EPERM;
#endif
	/* fall through */
	case MLX5_IB_MMAP_REGULAR_PAGE:
		/* For MLX5_IB_MMAP_REGULAR_PAGE do the best effort to get WC */
		prot = pgprot_writecombine(vma->vm_page_prot);
		break;
	case MLX5_IB_MMAP_NC_PAGE:
		prot = pgprot_noncached(vma->vm_page_prot);
		break;
	default:
		return -EINVAL;
	}

	if (vma->vm_end - vma->vm_start != PAGE_SIZE)
		return -EINVAL;

	idx = get_index(vma->vm_pgoff);
	if (idx >= uuari->num_uars)
		return -EINVAL;

	pfn = uar_index2pfn(dev, uuari->uars[idx].index);
	mlx5_ib_dbg(dev, "uar idx 0x%lx, pfn %pa\n", idx, &pfn);

	vma->vm_page_prot = prot;
	err = io_remap_pfn_range(vma, vma->vm_start, pfn,
				 PAGE_SIZE, vma->vm_page_prot);
	if (err) {
		mlx5_ib_err(dev, "io_remap_pfn_range failed with error=%d, vm_start=0x%llx, pfn=%pa, mmap_cmd=%s\n",
			    err, (unsigned long long)vma->vm_start, &pfn, mmap_cmd2str(cmd));
		return -EAGAIN;
	}

	pa = pfn << PAGE_SHIFT;
	mlx5_ib_dbg(dev, "mapped %s at 0x%llx, PA %pa\n", mmap_cmd2str(cmd),
		    (unsigned long long)vma->vm_start, &pa);

	return mlx5_ib_set_vma_data(vma, context);
}