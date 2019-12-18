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
struct TYPE_2__ {int /*<<< orphan*/  (* post_intr ) (struct vlapic*,int) ;} ;
struct vlapic {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipi_cpu (int,int) ; 
 int /*<<< orphan*/  stub1 (struct vlapic*,int) ; 

void
vlapic_post_intr(struct vlapic *vlapic, int hostcpu, int ipinum)
{
	/*
	 * Post an interrupt to the vcpu currently running on 'hostcpu'.
	 *
	 * This is done by leveraging features like Posted Interrupts (Intel)
	 * Doorbell MSR (AMD AVIC) that avoid a VM exit.
	 *
	 * If neither of these features are available then fallback to
	 * sending an IPI to 'hostcpu'.
	 */
	if (vlapic->ops.post_intr)
		(*vlapic->ops.post_intr)(vlapic, hostcpu);
	else
		ipi_cpu(hostcpu, ipinum);
}