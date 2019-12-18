#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct block {int dummy; } ;
struct TYPE_6__ {scalar_t__ linktype; TYPE_1__* bpf_pcap; } ;
typedef  TYPE_2__ compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_int32 ;
struct TYPE_5__ {scalar_t__ swapped; int /*<<< orphan*/ * rfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_W ; 
 scalar_t__ DLT_ENC ; 
 scalar_t__ DLT_NULL ; 
 int /*<<< orphan*/  OR_LINKHDR ; 
 int SWAPLONG (int) ; 
 struct block* gen_cmp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int htonl (int) ; 

__attribute__((used)) static struct block *
gen_loopback_linktype(compiler_state_t *cstate, int proto)
{
	/*
	 * For DLT_NULL, the link-layer header is a 32-bit word
	 * containing an AF_ value in *host* byte order, and for
	 * DLT_ENC, the link-layer header begins with a 32-bit
	 * word containing an AF_ value in host byte order.
	 *
	 * In addition, if we're reading a saved capture file,
	 * the host byte order in the capture may not be the
	 * same as the host byte order on this machine.
	 *
	 * For DLT_LOOP, the link-layer header is a 32-bit
	 * word containing an AF_ value in *network* byte order.
	 */
	if (cstate->linktype == DLT_NULL || cstate->linktype == DLT_ENC) {
		/*
		 * The AF_ value is in host byte order, but the BPF
		 * interpreter will convert it to network byte order.
		 *
		 * If this is a save file, and it's from a machine
		 * with the opposite byte order to ours, we byte-swap
		 * the AF_ value.
		 *
		 * Then we run it through "htonl()", and generate
		 * code to compare against the result.
		 */
		if (cstate->bpf_pcap->rfile != NULL && cstate->bpf_pcap->swapped)
			proto = SWAPLONG(proto);
		proto = htonl(proto);
	}
	return (gen_cmp(cstate, OR_LINKHDR, 0, BPF_W, (bpf_int32)proto));
}