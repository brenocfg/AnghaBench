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
struct resource_list {int dummy; } ;
struct pccard_ivar {TYPE_2__* pf; struct resource_list resources; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int number; TYPE_1__* cfe; } ;
struct TYPE_3__ {int number; } ;

/* Variables and functions */
 struct pccard_ivar* PCCARD_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCCARD_NDRQ ; 
 int /*<<< orphan*/  PCCARD_NIRQ ; 
 int /*<<< orphan*/  PCCARD_NMEM ; 
 int /*<<< orphan*/  PCCARD_NPORT ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pccard_print_resources (struct resource_list*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ printf (char*,...) ; 

__attribute__((used)) static int
pccard_print_child(device_t dev, device_t child)
{
	struct pccard_ivar *devi = PCCARD_IVAR(child);
	struct resource_list *rl = &devi->resources;
	int retval = 0;

	retval += bus_print_child_header(dev, child);
	retval += printf(" at");

	if (devi != NULL) {
		pccard_print_resources(rl, "port", SYS_RES_IOPORT,
		    PCCARD_NPORT, "%#lx");
		pccard_print_resources(rl, "iomem", SYS_RES_MEMORY,
		    PCCARD_NMEM, "%#lx");
		pccard_print_resources(rl, "irq", SYS_RES_IRQ, PCCARD_NIRQ,
		    "%ld");
		pccard_print_resources(rl, "drq", SYS_RES_DRQ, PCCARD_NDRQ,
		    "%ld");
		retval += printf(" function %d config %d", devi->pf->number,
		    devi->pf->cfe->number);
	}

	retval += bus_print_child_footer(dev, child);

	return (retval);
}