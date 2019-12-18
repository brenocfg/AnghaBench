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
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
#define  ETHERTYPE_IP 129 
#define  ETHERTYPE_IPV6 128 
 int /*<<< orphan*/  IPH_AF_INET ; 
 int /*<<< orphan*/  IPH_AF_INET6 ; 
 int /*<<< orphan*/  OR_LINKTYPE ; 
 struct block* gen_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct block* gen_false (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct block *
gen_ipnet_linktype(compiler_state_t *cstate, int proto)
{
	switch (proto) {

	case ETHERTYPE_IP:
		return gen_cmp(cstate, OR_LINKTYPE, 0, BPF_B, (bpf_int32)IPH_AF_INET);
		/* NOTREACHED */

	case ETHERTYPE_IPV6:
		return gen_cmp(cstate, OR_LINKTYPE, 0, BPF_B,
		    (bpf_int32)IPH_AF_INET6);
		/* NOTREACHED */

	default:
		break;
	}

	return gen_false(cstate);
}