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
struct ev7_pal_io_subpacket {unsigned long po7_error_sum; TYPE_1__* ports; int /*<<< orphan*/  po7_err_pkt1; int /*<<< orphan*/  po7_err_pkt0; int /*<<< orphan*/  po7_ugbge_sym; int /*<<< orphan*/  po7_crrct_sym; int /*<<< orphan*/  po7_uncrr_sym; } ;
struct ev7_lf_subpackets {unsigned long io_pid; struct ev7_pal_io_subpacket* io; int /*<<< orphan*/  logout; } ;
struct TYPE_2__ {unsigned long pox_err_sum; unsigned long pox_first_err; } ;

/* Variables and functions */
 int IO7_NUM_PORTS ; 
 int IO7__PO7_ERRSUM__ERR_MASK ; 
 int /*<<< orphan*/  MARVEL_IO_ERR_VALID (unsigned long) ; 
 int MCHK_DISPOSITION_REPORT ; 
 int MCHK_DISPOSITION_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  marvel_find_io7_with_error (struct ev7_lf_subpackets*) ; 
 int /*<<< orphan*/  marvel_print_po7_err_sum (struct ev7_pal_io_subpacket*) ; 
 int /*<<< orphan*/  marvel_print_pox_err (unsigned long,TYPE_1__*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned long,...) ; 

__attribute__((used)) static int
marvel_process_io_error(struct ev7_lf_subpackets *lf_subpackets, int print)
{
	int status = MCHK_DISPOSITION_UNKNOWN_ERROR;

#ifdef CONFIG_VERBOSE_MCHECK
	struct ev7_pal_io_subpacket *io = lf_subpackets->io;
	int i;
#endif /* CONFIG_VERBOSE_MCHECK */

#define MARVEL_IO_ERR_VALID(x)  ((x) & (1UL << 63))

	if (!lf_subpackets->logout || !lf_subpackets->io)
		return status;

	/*
	 * The PALcode only builds an IO subpacket if there is a 
	 * locally connected IO7. In the cases of
	 *	1) a uniprocessor kernel
	 *	2) an mp kernel before the local secondary has called in
	 * error interrupts are all directed to the primary processor.
	 * In that case, we may not have an IO subpacket at all and, event
	 * if we do, it may not be the right now. 
	 *
	 * If the RBOX indicates an I/O error interrupt, make sure we have
	 * the correct IO7 information. If we don't have an IO subpacket
	 * or it's the wrong one, try to find the right one.
	 *
	 * RBOX I/O error interrupts are indicated by RBOX_INT<29> and
	 * RBOX_INT<10>.
	 */
	if ((lf_subpackets->io->po7_error_sum & (1UL << 32)) ||
	    ((lf_subpackets->io->po7_error_sum        |
	      lf_subpackets->io->ports[0].pox_err_sum |
	      lf_subpackets->io->ports[1].pox_err_sum |
	      lf_subpackets->io->ports[2].pox_err_sum |
	      lf_subpackets->io->ports[3].pox_err_sum) & (1UL << 63))) {
		/*
		 * Either we have no IO subpacket or no error is
		 * indicated in the one we do have. Try find the
		 * one with the error.
		 */
		if (!marvel_find_io7_with_error(lf_subpackets))
			return status;
	}

	/*
	 * We have an IO7 indicating an error - we're going to report it
	 */
	status = MCHK_DISPOSITION_REPORT;

#ifdef CONFIG_VERBOSE_MCHECK

	if (!print)
		return status;

	printk("%s*Error occurred on IO7 at PID %u\n", 
	       err_print_prefix, lf_subpackets->io_pid);

	/*
	 * Check port 7 first
	 */
	if (lf_subpackets->io->po7_error_sum & IO7__PO7_ERRSUM__ERR_MASK) {
		marvel_print_po7_err_sum(io);

#if 0
		printk("%s  PORT 7 ERROR:\n"
		       "%s    PO7_ERROR_SUM: %016llx\n"
		       "%s    PO7_UNCRR_SYM: %016llx\n"
		       "%s    PO7_CRRCT_SYM: %016llx\n"
		       "%s    PO7_UGBGE_SYM: %016llx\n"
		       "%s    PO7_ERR_PKT0:  %016llx\n"
		       "%s    PO7_ERR_PKT1:  %016llx\n",
		       err_print_prefix,
		       err_print_prefix, io->po7_error_sum,
		       err_print_prefix, io->po7_uncrr_sym,
		       err_print_prefix, io->po7_crrct_sym,
		       err_print_prefix, io->po7_ugbge_sym,
		       err_print_prefix, io->po7_err_pkt0,
		       err_print_prefix, io->po7_err_pkt1);
#endif
	}

	/*
	 * Then loop through the ports
	 */
	for (i = 0; i < IO7_NUM_PORTS; i++) {
		if (!MARVEL_IO_ERR_VALID(io->ports[i].pox_err_sum))
			continue;

		printk("%s  PID %u PORT %d POx_ERR_SUM: %016llx\n",
		       err_print_prefix, 
		       lf_subpackets->io_pid, i, io->ports[i].pox_err_sum);
		marvel_print_pox_err(io->ports[i].pox_err_sum, &io->ports[i]);

		printk("%s  [ POx_FIRST_ERR: %016llx ]\n",
		       err_print_prefix, io->ports[i].pox_first_err);
		marvel_print_pox_err(io->ports[i].pox_first_err, 
				     &io->ports[i]);

	}


#endif /* CONFIG_VERBOSE_MCHECK */

	return status;
}