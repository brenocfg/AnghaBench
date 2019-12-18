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
struct si_sm_io {scalar_t__ si_type; int /*<<< orphan*/  (* outputb ) (struct si_sm_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_BT_INTMASK_REG ; 
 scalar_t__ SI_BT ; 
 int /*<<< orphan*/  stub1 (struct si_sm_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ipmi_irq_start_cleanup(struct si_sm_io *io)
{
	if (io->si_type == SI_BT)
		/* Disable the interrupt in the BT interface. */
		io->outputb(io, IPMI_BT_INTMASK_REG, 0);
}