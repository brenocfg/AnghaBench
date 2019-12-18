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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vmctx {int dummy; } ;

/* Variables and functions */
 int MEM_F_READ ; 
 int /*<<< orphan*/  pci_cfgrw (struct vmctx*,int,int,int,int,int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pci_emul_ecfg_handler(struct vmctx *ctx, int vcpu, int dir, uint64_t addr,
    int bytes, uint64_t *val, void *arg1, long arg2)
{
	int bus, slot, func, coff, in;

	coff = addr & 0xfff;
	func = (addr >> 12) & 0x7;
	slot = (addr >> 15) & 0x1f;
	bus = (addr >> 20) & 0xff;
	in = (dir == MEM_F_READ);
	if (in)
		*val = ~0UL;
	pci_cfgrw(ctx, vcpu, in, bus, slot, func, coff, bytes, (uint32_t *)val);
	return (0);
}