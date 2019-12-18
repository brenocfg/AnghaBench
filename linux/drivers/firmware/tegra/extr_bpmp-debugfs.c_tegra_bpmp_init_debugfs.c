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
struct tegra_bpmp {int /*<<< orphan*/  dev; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  MRQ_DEBUGFS ; 
 size_t SZ_256K ; 
 int create_debugfs_mirror (struct tegra_bpmp*,void*,size_t,struct dentry*) ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (struct dentry*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,size_t const,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t const,void*,int /*<<< orphan*/ ) ; 
 int mrq_debugfs_dumpdir (struct tegra_bpmp*,int /*<<< orphan*/ ,size_t const,size_t*) ; 
 int /*<<< orphan*/  tegra_bpmp_mrq_is_supported (struct tegra_bpmp*,int /*<<< orphan*/ ) ; 

int tegra_bpmp_init_debugfs(struct tegra_bpmp *bpmp)
{
	dma_addr_t phys;
	void *virt;
	const size_t sz = SZ_256K;
	size_t nbytes;
	int ret;
	struct dentry *root;

	if (!tegra_bpmp_mrq_is_supported(bpmp, MRQ_DEBUGFS))
		return 0;

	root = debugfs_create_dir("bpmp", NULL);
	if (!root)
		return -ENOMEM;

	virt = dma_alloc_coherent(bpmp->dev, sz, &phys,
				  GFP_KERNEL | GFP_DMA32);
	if (!virt) {
		ret = -ENOMEM;
		goto out;
	}

	ret = mrq_debugfs_dumpdir(bpmp, phys, sz, &nbytes);
	if (ret < 0)
		goto free;

	ret = create_debugfs_mirror(bpmp, virt, nbytes, root);
free:
	dma_free_coherent(bpmp->dev, sz, virt, phys);
out:
	if (ret < 0)
		debugfs_remove(root);

	return ret;
}