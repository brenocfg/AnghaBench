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
struct stratix10_svc_sh_memory {int /*<<< orphan*/  size; scalar_t__ addr; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct gen_pool {int dummy; } ;
typedef  size_t phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct gen_pool* ERR_PTR (int) ; 
 int /*<<< orphan*/  MEMREMAP_WC ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,void*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int gen_pool_add_virt (struct gen_pool*,unsigned long,size_t,size_t,int) ; 
 int /*<<< orphan*/  gen_pool_best_fit ; 
 struct gen_pool* gen_pool_create (int,int) ; 
 int /*<<< orphan*/  gen_pool_destroy (struct gen_pool*) ; 
 int /*<<< orphan*/  gen_pool_set_algo (struct gen_pool*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* memremap (size_t,size_t,int /*<<< orphan*/ ) ; 
 size_t rounddown (scalar_t__,int) ; 
 size_t roundup (scalar_t__,int) ; 

__attribute__((used)) static struct gen_pool *
svc_create_memory_pool(struct platform_device *pdev,
		       struct stratix10_svc_sh_memory *sh_memory)
{
	struct device *dev = &pdev->dev;
	struct gen_pool *genpool;
	unsigned long vaddr;
	phys_addr_t paddr;
	size_t size;
	phys_addr_t begin;
	phys_addr_t end;
	void *va;
	size_t page_mask = PAGE_SIZE - 1;
	int min_alloc_order = 3;
	int ret;

	begin = roundup(sh_memory->addr, PAGE_SIZE);
	end = rounddown(sh_memory->addr + sh_memory->size, PAGE_SIZE);
	paddr = begin;
	size = end - begin;
	va = memremap(paddr, size, MEMREMAP_WC);
	if (!va) {
		dev_err(dev, "fail to remap shared memory\n");
		return ERR_PTR(-EINVAL);
	}
	vaddr = (unsigned long)va;
	dev_dbg(dev,
		"reserved memory vaddr: %p, paddr: 0x%16x size: 0x%8x\n",
		va, (unsigned int)paddr, (unsigned int)size);
	if ((vaddr & page_mask) || (paddr & page_mask) ||
	    (size & page_mask)) {
		dev_err(dev, "page is not aligned\n");
		return ERR_PTR(-EINVAL);
	}
	genpool = gen_pool_create(min_alloc_order, -1);
	if (!genpool) {
		dev_err(dev, "fail to create genpool\n");
		return ERR_PTR(-ENOMEM);
	}
	gen_pool_set_algo(genpool, gen_pool_best_fit, NULL);
	ret = gen_pool_add_virt(genpool, vaddr, paddr, size, -1);
	if (ret) {
		dev_err(dev, "fail to add memory chunk to the pool\n");
		gen_pool_destroy(genpool);
		return ERR_PTR(ret);
	}

	return genpool;
}