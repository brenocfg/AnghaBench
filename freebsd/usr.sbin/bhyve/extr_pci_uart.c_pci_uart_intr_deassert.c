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
struct pci_devinst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_lintr_deassert (struct pci_devinst*) ; 

__attribute__((used)) static void
pci_uart_intr_deassert(void *arg)
{
	struct pci_devinst *pi = arg;

	pci_lintr_deassert(pi);
}