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
struct nicvf {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  NICVF_INTR_MBOX ; 
 int /*<<< orphan*/  nicvf_check_pf_ready (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_disable_intr (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_enable_intr (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nicvf_enable_misc_interrupt(struct nicvf *nic)
{

	/* Enable mailbox interrupt */
	nicvf_enable_intr(nic, NICVF_INTR_MBOX, 0);

	/* Check if VF is able to communicate with PF */
	if (!nicvf_check_pf_ready(nic)) {
		nicvf_disable_intr(nic, NICVF_INTR_MBOX, 0);
		return (ENXIO);
	}

	return (0);
}