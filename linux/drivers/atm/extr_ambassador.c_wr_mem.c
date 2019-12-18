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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ iobase; int /*<<< orphan*/ * membase; } ;
typedef  TYPE_1__ amb_dev ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int DBG_FLOW ; 
 int DBG_REGS ; 
 int /*<<< orphan*/  PRINTD (int,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void wr_mem (const amb_dev * dev, size_t addr, u32 data) {
  __be32 be = cpu_to_be32 (data);
  PRINTD (DBG_FLOW|DBG_REGS, "wr: %08zx <- %08x b[%08x]", addr, data, be);
#ifdef AMB_MMIO
  dev->membase[addr / sizeof(u32)] = be;
#else
  outl (be, dev->iobase + addr);
#endif
}