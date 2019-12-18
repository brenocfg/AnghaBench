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
struct AdapterControlBlock {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  arcmsr_disable_allintr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop_parking (struct AdapterControlBlock*) ; 
 struct AdapterControlBlock* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arcmsr_suspend(device_t dev)
{
	struct AdapterControlBlock	*acb = device_get_softc(dev);

	/* flush controller */
	arcmsr_iop_parking(acb);
	/* disable all outbound interrupt */
	arcmsr_disable_allintr(acb);
	return(0);
}