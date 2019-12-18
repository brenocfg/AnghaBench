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
typedef  int uint32_t ;
struct vmctx {int dummy; } ;

/* Variables and functions */
 int CONF1_DATA_PORT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cfgbus ; 
 scalar_t__ cfgenable ; 
 int /*<<< orphan*/  cfgfunc ; 
 int cfgoff ; 
 int /*<<< orphan*/  cfgslot ; 
 int /*<<< orphan*/  pci_cfgrw (struct vmctx*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static int
pci_emul_cfgdata(struct vmctx *ctx, int vcpu, int in, int port, int bytes,
		 uint32_t *eax, void *arg)
{
	int coff;

	assert(bytes == 1 || bytes == 2 || bytes == 4);

	coff = cfgoff + (port - CONF1_DATA_PORT);
	if (cfgenable) {
		pci_cfgrw(ctx, vcpu, in, cfgbus, cfgslot, cfgfunc, coff, bytes,
		    eax);
	} else {
		/* Ignore accesses to cfgdata if not enabled by cfgaddr */
		if (in)
			*eax = 0xffffffff;
	}
	return (0);
}