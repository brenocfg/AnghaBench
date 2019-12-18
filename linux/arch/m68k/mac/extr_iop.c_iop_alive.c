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
struct mac_iop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOP_ADDR_ALIVE ; 
 int iop_readb (struct mac_iop volatile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iop_writeb (struct mac_iop volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iop_alive(volatile struct mac_iop *iop)
{
	int retval;

	retval = (iop_readb(iop, IOP_ADDR_ALIVE) == 0xFF);
	iop_writeb(iop, IOP_ADDR_ALIVE, 0);
	return retval;
}