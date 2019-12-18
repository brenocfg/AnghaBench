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
typedef  int /*<<< orphan*/  u32 ;
struct sdma_engine {int /*<<< orphan*/  dev; int /*<<< orphan*/  channel_0_lock; struct sdma_buffer_descriptor* bd0; } ;
struct TYPE_2__ {int status; int count; int /*<<< orphan*/  command; } ;
struct sdma_buffer_descriptor {int /*<<< orphan*/  ext_buffer_addr; int /*<<< orphan*/  buffer_addr; TYPE_1__ mode; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int BD_DONE ; 
 int BD_EXTD ; 
 int BD_WRAP ; 
 int /*<<< orphan*/  C0_SETPM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int sdma_run_channel0 (struct sdma_engine*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sdma_load_script(struct sdma_engine *sdma, void *buf, int size,
		u32 address)
{
	struct sdma_buffer_descriptor *bd0 = sdma->bd0;
	void *buf_virt;
	dma_addr_t buf_phys;
	int ret;
	unsigned long flags;

	buf_virt = dma_alloc_coherent(sdma->dev, size, &buf_phys, GFP_KERNEL);
	if (!buf_virt) {
		return -ENOMEM;
	}

	spin_lock_irqsave(&sdma->channel_0_lock, flags);

	bd0->mode.command = C0_SETPM;
	bd0->mode.status = BD_DONE | BD_WRAP | BD_EXTD;
	bd0->mode.count = size / 2;
	bd0->buffer_addr = buf_phys;
	bd0->ext_buffer_addr = address;

	memcpy(buf_virt, buf, size);

	ret = sdma_run_channel0(sdma);

	spin_unlock_irqrestore(&sdma->channel_0_lock, flags);

	dma_free_coherent(sdma->dev, size, buf_virt, buf_phys);

	return ret;
}