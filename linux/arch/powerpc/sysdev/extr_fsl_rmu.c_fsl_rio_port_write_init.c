#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ phys; int /*<<< orphan*/  virt; scalar_t__ discard_count; scalar_t__ err_count; } ;
struct fsl_rio_pw {TYPE_2__ port_write_msg; int /*<<< orphan*/  dev; TYPE_1__* pw_regs; int /*<<< orphan*/  pw_fifo; int /*<<< orphan*/  pw_fifo_lock; int /*<<< orphan*/  pw_work; } ;
struct TYPE_3__ {int pwmr; int epwqbar; int pwqbar; int pwsr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_RIO_PW (struct fsl_rio_pw*) ; 
 int LTLEECSR_ENABLE_ALL ; 
 int RIO_IPWMR_CQ ; 
 int RIO_IPWMR_EIE ; 
 int RIO_IPWMR_PWE ; 
 int RIO_IPWMR_QFIE ; 
 int RIO_IPWMR_SEN ; 
 int RIO_IPWSR_PWD ; 
 int RIO_IPWSR_QFI ; 
 int RIO_IPWSR_TE ; 
 scalar_t__ RIO_LTLEECSR ; 
 int RIO_PW_MSG_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  fsl_pw_dpc ; 
 int /*<<< orphan*/  fsl_rio_port_write_handler ; 
 int in_be32 (int*) ; 
 scalar_t__ kfifo_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 scalar_t__ rio_regs_win ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int fsl_rio_port_write_init(struct fsl_rio_pw *pw)
{
	int rc = 0;

	/* Following configurations require a disabled port write controller */
	out_be32(&pw->pw_regs->pwmr,
		 in_be32(&pw->pw_regs->pwmr) & ~RIO_IPWMR_PWE);

	/* Initialize port write */
	pw->port_write_msg.virt = dma_alloc_coherent(pw->dev,
					RIO_PW_MSG_SIZE,
					&pw->port_write_msg.phys, GFP_KERNEL);
	if (!pw->port_write_msg.virt) {
		pr_err("RIO: unable allocate port write queue\n");
		return -ENOMEM;
	}

	pw->port_write_msg.err_count = 0;
	pw->port_write_msg.discard_count = 0;

	/* Point dequeue/enqueue pointers at first entry */
	out_be32(&pw->pw_regs->epwqbar, 0);
	out_be32(&pw->pw_regs->pwqbar, (u32) pw->port_write_msg.phys);

	pr_debug("EIPWQBAR: 0x%08x IPWQBAR: 0x%08x\n",
		 in_be32(&pw->pw_regs->epwqbar),
		 in_be32(&pw->pw_regs->pwqbar));

	/* Clear interrupt status IPWSR */
	out_be32(&pw->pw_regs->pwsr,
		 (RIO_IPWSR_TE | RIO_IPWSR_QFI | RIO_IPWSR_PWD));

	/* Configure port write controller for snooping enable all reporting,
	   clear queue full */
	out_be32(&pw->pw_regs->pwmr,
		 RIO_IPWMR_SEN | RIO_IPWMR_QFIE | RIO_IPWMR_EIE | RIO_IPWMR_CQ);


	/* Hook up port-write handler */
	rc = request_irq(IRQ_RIO_PW(pw), fsl_rio_port_write_handler,
			IRQF_SHARED, "port-write", (void *)pw);
	if (rc < 0) {
		pr_err("MPC85xx RIO: unable to request inbound doorbell irq");
		goto err_out;
	}
	/* Enable Error Interrupt */
	out_be32((u32 *)(rio_regs_win + RIO_LTLEECSR), LTLEECSR_ENABLE_ALL);

	INIT_WORK(&pw->pw_work, fsl_pw_dpc);
	spin_lock_init(&pw->pw_fifo_lock);
	if (kfifo_alloc(&pw->pw_fifo, RIO_PW_MSG_SIZE * 32, GFP_KERNEL)) {
		pr_err("FIFO allocation failed\n");
		rc = -ENOMEM;
		goto err_out_irq;
	}

	pr_debug("IPWMR: 0x%08x IPWSR: 0x%08x\n",
		 in_be32(&pw->pw_regs->pwmr),
		 in_be32(&pw->pw_regs->pwsr));

	return rc;

err_out_irq:
	free_irq(IRQ_RIO_PW(pw), (void *)pw);
err_out:
	dma_free_coherent(pw->dev, RIO_PW_MSG_SIZE,
		pw->port_write_msg.virt,
		pw->port_write_msg.phys);
	return rc;
}