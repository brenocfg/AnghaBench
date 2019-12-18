#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; int cur_ctrl; int org_data; int org_ctrl; scalar_t__ lpt_addr; } ;
typedef  TYPE_1__ Interface ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int port_init ; 
 int port_sel ; 

__attribute__((used)) static void ppc6_deselect(Interface *ppc)
{
	if (ppc->mode & 4)	// EPP
		ppc->cur_ctrl |= port_init;
	else								// PPC/ECP
		ppc->cur_ctrl |= port_sel;

	outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

	outb(ppc->org_data, ppc->lpt_addr);

	outb((ppc->org_ctrl | port_sel), ppc->lpt_addr + 2);

	outb(ppc->org_ctrl, ppc->lpt_addr + 2);
}