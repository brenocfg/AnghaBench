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
struct TYPE_3__ {int discard_count; int err_count; int /*<<< orphan*/  virt; int /*<<< orphan*/  msg_count; } ;
struct fsl_rio_pw {TYPE_2__* pw_regs; TYPE_1__ port_write_msg; int /*<<< orphan*/  pw_work; int /*<<< orphan*/  pw_fifo; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  pwsr; int /*<<< orphan*/  pwmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RIO_EPWISR ; 
 int RIO_EPWISR_MU ; 
 int RIO_EPWISR_PINT1 ; 
 int RIO_EPWISR_PINT2 ; 
 int RIO_EPWISR_PW ; 
 int RIO_IPWMR_CQ ; 
 int RIO_IPWMR_EIE ; 
 int RIO_IPWMR_PWE ; 
 int RIO_IPWSR_PWB ; 
 int RIO_IPWSR_PWD ; 
 int RIO_IPWSR_QF ; 
 int RIO_IPWSR_QFI ; 
 int RIO_IPWSR_TE ; 
 int RIO_LTLEDCSR ; 
 scalar_t__ RIO_PW_MSG_SIZE ; 
 int /*<<< orphan*/  fsl_rio_port_error_handler (int) ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 scalar_t__ kfifo_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msg_unit_error_handler () ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/ * rio_regs_win ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
fsl_rio_port_write_handler(int irq, void *dev_instance)
{
	u32 ipwmr, ipwsr;
	struct fsl_rio_pw *pw = (struct fsl_rio_pw *)dev_instance;
	u32 epwisr, tmp;

	epwisr = in_be32(rio_regs_win + RIO_EPWISR);
	if (!(epwisr & RIO_EPWISR_PW))
		goto pw_done;

	ipwmr = in_be32(&pw->pw_regs->pwmr);
	ipwsr = in_be32(&pw->pw_regs->pwsr);

#ifdef DEBUG_PW
	pr_debug("PW Int->IPWMR: 0x%08x IPWSR: 0x%08x (", ipwmr, ipwsr);
	if (ipwsr & RIO_IPWSR_QF)
		pr_debug(" QF");
	if (ipwsr & RIO_IPWSR_TE)
		pr_debug(" TE");
	if (ipwsr & RIO_IPWSR_QFI)
		pr_debug(" QFI");
	if (ipwsr & RIO_IPWSR_PWD)
		pr_debug(" PWD");
	if (ipwsr & RIO_IPWSR_PWB)
		pr_debug(" PWB");
	pr_debug(" )\n");
#endif
	/* Schedule deferred processing if PW was received */
	if (ipwsr & RIO_IPWSR_QFI) {
		/* Save PW message (if there is room in FIFO),
		 * otherwise discard it.
		 */
		if (kfifo_avail(&pw->pw_fifo) >= RIO_PW_MSG_SIZE) {
			pw->port_write_msg.msg_count++;
			kfifo_in(&pw->pw_fifo, pw->port_write_msg.virt,
				 RIO_PW_MSG_SIZE);
		} else {
			pw->port_write_msg.discard_count++;
			pr_debug("RIO: ISR Discarded Port-Write Msg(s) (%d)\n",
				 pw->port_write_msg.discard_count);
		}
		/* Clear interrupt and issue Clear Queue command. This allows
		 * another port-write to be received.
		 */
		out_be32(&pw->pw_regs->pwsr,	RIO_IPWSR_QFI);
		out_be32(&pw->pw_regs->pwmr, ipwmr | RIO_IPWMR_CQ);

		schedule_work(&pw->pw_work);
	}

	if ((ipwmr & RIO_IPWMR_EIE) && (ipwsr & RIO_IPWSR_TE)) {
		pw->port_write_msg.err_count++;
		pr_debug("RIO: Port-Write Transaction Err (%d)\n",
			 pw->port_write_msg.err_count);
		/* Clear Transaction Error: port-write controller should be
		 * disabled when clearing this error
		 */
		out_be32(&pw->pw_regs->pwmr, ipwmr & ~RIO_IPWMR_PWE);
		out_be32(&pw->pw_regs->pwsr,	RIO_IPWSR_TE);
		out_be32(&pw->pw_regs->pwmr, ipwmr);
	}

	if (ipwsr & RIO_IPWSR_PWD) {
		pw->port_write_msg.discard_count++;
		pr_debug("RIO: Port Discarded Port-Write Msg(s) (%d)\n",
			 pw->port_write_msg.discard_count);
		out_be32(&pw->pw_regs->pwsr, RIO_IPWSR_PWD);
	}

pw_done:
	if (epwisr & RIO_EPWISR_PINT1) {
		tmp = in_be32(rio_regs_win + RIO_LTLEDCSR);
		pr_debug("RIO_LTLEDCSR = 0x%x\n", tmp);
		fsl_rio_port_error_handler(0);
	}

	if (epwisr & RIO_EPWISR_PINT2) {
		tmp = in_be32(rio_regs_win + RIO_LTLEDCSR);
		pr_debug("RIO_LTLEDCSR = 0x%x\n", tmp);
		fsl_rio_port_error_handler(1);
	}

	if (epwisr & RIO_EPWISR_MU) {
		tmp = in_be32(rio_regs_win + RIO_LTLEDCSR);
		pr_debug("RIO_LTLEDCSR = 0x%x\n", tmp);
		msg_unit_error_handler();
	}

	return IRQ_HANDLED;
}