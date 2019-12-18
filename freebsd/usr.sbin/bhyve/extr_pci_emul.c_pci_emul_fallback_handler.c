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
struct vmctx {int dummy; } ;

/* Variables and functions */
 int MEM_F_READ ; 

__attribute__((used)) static int
pci_emul_fallback_handler(struct vmctx *ctx, int vcpu, int dir, uint64_t addr,
			  int size, uint64_t *val, void *arg1, long arg2)
{
	/*
	 * Ignore writes; return 0xff's for reads. The mem read code
	 * will take care of truncating to the correct size.
	 */
	if (dir == MEM_F_READ) {
		*val = 0xffffffffffffffff;
	}

	return (0);
}