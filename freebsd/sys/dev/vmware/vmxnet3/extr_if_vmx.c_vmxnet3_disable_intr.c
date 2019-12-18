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
struct vmxnet3_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_BAR0_IMASK (int) ; 
 int /*<<< orphan*/  vmxnet3_write_bar0 (struct vmxnet3_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmxnet3_disable_intr(struct vmxnet3_softc *sc, int irq)
{

	vmxnet3_write_bar0(sc, VMXNET3_BAR0_IMASK(irq), 1);
}