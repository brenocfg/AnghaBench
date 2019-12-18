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
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 

__attribute__((used)) static inline u32 rd_mem (const amb_dev * dev, size_t addr) {
#ifdef AMB_MMIO
  __be32 be = dev->membase[addr / sizeof(u32)];
#else
  __be32 be = inl (dev->iobase + addr);
#endif
  u32 data = be32_to_cpu (be);
  PRINTD (DBG_FLOW|DBG_REGS, "rd: %08zx -> %08x b[%08x]", addr, data, be);
  return data;
}