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
struct TYPE_2__ {int size; struct tegra_bpmp_message* data; } ;
struct tegra_bpmp_message {TYPE_1__ tx; int /*<<< orphan*/  mrq; int /*<<< orphan*/  addr; } ;
struct tegra_bpmp {int /*<<< orphan*/  dev; } ;
struct mrq_query_tag_request {TYPE_1__ tx; int /*<<< orphan*/  mrq; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  request ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  MRQ_QUERY_TAG ; 
 size_t TAG_SZ ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memcpy (char*,void*,size_t) ; 
 int /*<<< orphan*/  memset (struct tegra_bpmp_message*,int /*<<< orphan*/ ,int) ; 
 int tegra_bpmp_transfer_atomic (struct tegra_bpmp*,struct tegra_bpmp_message*) ; 

__attribute__((used)) static int tegra_bpmp_get_firmware_tag_old(struct tegra_bpmp *bpmp, char *tag,
					   size_t size)
{
	struct mrq_query_tag_request request;
	struct tegra_bpmp_message msg;
	unsigned long flags;
	dma_addr_t phys;
	void *virt;
	int err;

	if (size != TAG_SZ)
		return -EINVAL;

	virt = dma_alloc_coherent(bpmp->dev, TAG_SZ, &phys,
				  GFP_KERNEL | GFP_DMA32);
	if (!virt)
		return -ENOMEM;

	memset(&request, 0, sizeof(request));
	request.addr = phys;

	memset(&msg, 0, sizeof(msg));
	msg.mrq = MRQ_QUERY_TAG;
	msg.tx.data = &request;
	msg.tx.size = sizeof(request);

	local_irq_save(flags);
	err = tegra_bpmp_transfer_atomic(bpmp, &msg);
	local_irq_restore(flags);

	if (err == 0)
		memcpy(tag, virt, TAG_SZ);

	dma_free_coherent(bpmp->dev, TAG_SZ, virt, phys);

	return err;
}