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
typedef  int /*<<< orphan*/  uint64_t ;
struct vas_window {int /*<<< orphan*/  winid; void* paste_kaddr; scalar_t__ nx_win; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LRFIFO_PUSH ; 
 int /*<<< orphan*/  RMA_LSMP_REPORT_ENABLE ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,unsigned long long,int) ; 
 int /*<<< orphan*/  VREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_hvwc_reg (struct vas_window*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_vas_paste_crb (int /*<<< orphan*/ ,struct vas_window*) ; 
 int vas_paste (void*,int) ; 

int vas_paste_crb(struct vas_window *txwin, int offset, bool re)
{
	int rc;
	void *addr;
	uint64_t val;

	trace_vas_paste_crb(current, txwin);

	/*
	 * Only NX windows are supported for now and hardware assumes
	 * report-enable flag is set for NX windows. Ensure software
	 * complies too.
	 */
	WARN_ON_ONCE(txwin->nx_win && !re);

	addr = txwin->paste_kaddr;
	if (re) {
		/*
		 * Set the REPORT_ENABLE bit (equivalent to writing
		 * to 1K offset of the paste address)
		 */
		val = SET_FIELD(RMA_LSMP_REPORT_ENABLE, 0ULL, 1);
		addr += val;
	}

	/*
	 * Map the raw CR value from vas_paste() to an error code (there
	 * is just pass or fail for now though).
	 */
	rc = vas_paste(addr, offset);
	if (rc == 2)
		rc = 0;
	else
		rc = -EINVAL;

	pr_debug("Txwin #%d: Msg count %llu\n", txwin->winid,
			read_hvwc_reg(txwin, VREG(LRFIFO_PUSH)));

	return rc;
}