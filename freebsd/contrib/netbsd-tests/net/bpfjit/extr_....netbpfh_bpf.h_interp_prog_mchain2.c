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
typedef  int /*<<< orphan*/  uint32_t ;
struct mbuf {int dummy; } ;
struct bpf_insn {int dummy; } ;
struct TYPE_3__ {size_t wirelen; int /*<<< orphan*/ * mem; scalar_t__ buflen; int /*<<< orphan*/  pkt; } ;
typedef  TYPE_1__ bpf_args_t ;

/* Variables and functions */
 int BPF_MEMWORDS ; 
 int /*<<< orphan*/  init_mchain2 (struct mbuf*,struct mbuf*,unsigned char*,size_t,size_t) ; 
 int /*<<< orphan*/  rump_schedule () ; 
 int /*<<< orphan*/  rump_unschedule () ; 
 unsigned int rumpns_bpf_filter_ext (int /*<<< orphan*/ *,struct bpf_insn*,TYPE_1__*) ; 

__attribute__((used)) static inline unsigned int
interp_prog_mchain2(struct bpf_insn *insns,
    unsigned char pkt[], size_t pktsize, size_t split)
{
	uint32_t mem[BPF_MEMWORDS];
	struct mbuf mb1, mb2;
	bpf_args_t args;
	unsigned int res;

	args.pkt = init_mchain2(&mb1, &mb2, pkt, pktsize, split);
	args.buflen = 0;
	args.wirelen = pktsize;
	args.mem = mem;

	rump_schedule();
	res = rumpns_bpf_filter_ext(NULL, insns, &args);
	rump_unschedule();

	return res;
}