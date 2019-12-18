#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct mem_ctl_info {int dummy; } ;
struct dram_addr {int chan; int /*<<< orphan*/  col; int /*<<< orphan*/  row; int /*<<< orphan*/  bank; int /*<<< orphan*/  rank; int /*<<< orphan*/  dimm; } ;
struct TYPE_2__ {int pmiaddr_shift; int pmiidx_shift; int (* pmi2mem ) (struct mem_ctl_info*,int,int,struct dram_addr*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ops ; 
 int stub1 (struct mem_ctl_info*,int,int,struct dram_addr*,char*) ; 
 int sys2pmi (int,int*,int*,char*) ; 

__attribute__((used)) static int get_memory_error_data(struct mem_ctl_info *mci, u64 addr,
								 struct dram_addr *daddr, char *msg)
{
	u64	pmiaddr;
	u32	pmiidx;
	int	ret;

	ret = sys2pmi(addr, &pmiidx, &pmiaddr, msg);
	if (ret)
		return ret;

	pmiaddr >>= ops->pmiaddr_shift;
	/* pmi channel idx to dimm channel idx */
	pmiidx >>= ops->pmiidx_shift;
	daddr->chan = pmiidx;

	ret = ops->pmi2mem(mci, pmiaddr, pmiidx, daddr, msg);
	if (ret)
		return ret;

	edac_dbg(0, "SysAddr=%llx PmiAddr=%llx Channel=%d DIMM=%d Rank=%d Bank=%d Row=%d Column=%d\n",
			 addr, pmiaddr, daddr->chan, daddr->dimm, daddr->rank, daddr->bank, daddr->row, daddr->col);

	return 0;
}