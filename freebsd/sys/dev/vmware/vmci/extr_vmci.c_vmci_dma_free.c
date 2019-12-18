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
struct vmci_dma_alloc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmci_dma_free_int (int /*<<< orphan*/ ,struct vmci_dma_alloc*) ; 
 int /*<<< orphan*/  vmci_sc ; 

void
vmci_dma_free(struct vmci_dma_alloc *dma)
{

	vmci_dma_free_int(vmci_sc, dma);
}