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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ESCSR_CLEAR ; 
 int /*<<< orphan*/  IECSR_CLEAR ; 
 scalar_t__ RIO_ESCSR ; 
 scalar_t__ RIO_LTLEDCSR ; 
 scalar_t__ RIO_PORT1_EDCSR ; 
 scalar_t__ RIO_PORT1_IECSR ; 
 scalar_t__ RIO_PORT2_EDCSR ; 
 scalar_t__ RIO_PORT2_ESCSR ; 
 scalar_t__ RIO_PORT2_IECSR ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rio_regs_win ; 

void fsl_rio_port_error_handler(int offset)
{
	/*XXX: Error recovery is not implemented, we just clear errors */
	out_be32((u32 *)(rio_regs_win + RIO_LTLEDCSR), 0);

	if (offset == 0) {
		out_be32((u32 *)(rio_regs_win + RIO_PORT1_EDCSR), 0);
		out_be32((u32 *)(rio_regs_win + RIO_PORT1_IECSR), IECSR_CLEAR);
		out_be32((u32 *)(rio_regs_win + RIO_ESCSR), ESCSR_CLEAR);
	} else {
		out_be32((u32 *)(rio_regs_win + RIO_PORT2_EDCSR), 0);
		out_be32((u32 *)(rio_regs_win + RIO_PORT2_IECSR), IECSR_CLEAR);
		out_be32((u32 *)(rio_regs_win + RIO_PORT2_ESCSR), ESCSR_CLEAR);
	}
}