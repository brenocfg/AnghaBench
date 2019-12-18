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
struct ev7_lf_subpackets {TYPE_2__* ev7; TYPE_1__* logout; } ;
struct TYPE_4__ {int c_stat; int c_sts; int c_addr; } ;
struct TYPE_3__ {int rbox_int; } ;

/* Variables and functions */
 int MCHK_DISPOSITION_DISMISS ; 
 int MCHK_DISPOSITION_UNKNOWN_ERROR ; 
 int marvel_process_io_error (struct ev7_lf_subpackets*,int) ; 

__attribute__((used)) static int
marvel_process_logout_frame(struct ev7_lf_subpackets *lf_subpackets, int print)
{
	int status = MCHK_DISPOSITION_UNKNOWN_ERROR;

	/*
	 * I/O error? 
	 */
#define EV7__RBOX_INT__IO_ERROR__MASK 0x20000400ul
	if (lf_subpackets->logout &&
	    (lf_subpackets->logout->rbox_int & 0x20000400ul))
		status = marvel_process_io_error(lf_subpackets, print);

	/*
	 * Probing behind PCI-X bridges can cause machine checks on
	 * Marvel when the probe is handled by the bridge as a split
	 * completion transaction. The symptom is an ERROR_RESPONSE 
	 * to a CONFIG address. Since these errors will happen in
	 * normal operation, dismiss them.
	 *
	 * Dismiss if:
	 *	C_STAT		= 0x14 		(Error Response)
	 *	C_STS<3>	= 0    		(C_ADDR valid)
	 *	C_ADDR<42>	= 1    		(I/O)
	 *	C_ADDR<31:22>	= 111110xxb	(PCI Config space)
	 */
	if (lf_subpackets->ev7 &&
	    (lf_subpackets->ev7->c_stat == 0x14) &&
	    !(lf_subpackets->ev7->c_sts & 0x8) &&
	    ((lf_subpackets->ev7->c_addr & 0x400ff000000ul) 
	     == 0x400fe000000ul))
		status = MCHK_DISPOSITION_DISMISS;

	return status;
}