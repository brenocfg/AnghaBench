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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct msix_entry {int /*<<< orphan*/  vector; } ;
struct ioatdma_device {int irq_mode; struct msix_entry* msix_entries; struct pci_dev* pdev; } ;
struct ioatdma_chan {int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  cleanup_task; int /*<<< orphan*/  timer; int /*<<< orphan*/  state; struct ioatdma_device* ioat_dma; } ;

/* Variables and functions */
#define  IOAT_INTX 130 
#define  IOAT_MSI 129 
#define  IOAT_MSIX 128 
 int /*<<< orphan*/  IOAT_RUN ; 
 int chan_num (struct ioatdma_chan*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioat_cleanup_event (unsigned long) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void ioat_stop(struct ioatdma_chan *ioat_chan)
{
	struct ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	struct pci_dev *pdev = ioat_dma->pdev;
	int chan_id = chan_num(ioat_chan);
	struct msix_entry *msix;

	/* 1/ stop irq from firing tasklets
	 * 2/ stop the tasklet from re-arming irqs
	 */
	clear_bit(IOAT_RUN, &ioat_chan->state);

	/* flush inflight interrupts */
	switch (ioat_dma->irq_mode) {
	case IOAT_MSIX:
		msix = &ioat_dma->msix_entries[chan_id];
		synchronize_irq(msix->vector);
		break;
	case IOAT_MSI:
	case IOAT_INTX:
		synchronize_irq(pdev->irq);
		break;
	default:
		break;
	}

	/* flush inflight timers */
	del_timer_sync(&ioat_chan->timer);

	/* flush inflight tasklet runs */
	tasklet_kill(&ioat_chan->cleanup_task);

	/* final cleanup now that everything is quiesced and can't re-arm */
	ioat_cleanup_event((unsigned long)&ioat_chan->dma_chan);
}