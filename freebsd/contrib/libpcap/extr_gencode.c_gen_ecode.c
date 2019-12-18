#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct qual {scalar_t__ addr; scalar_t__ proto; scalar_t__ dir; } ;
struct block {int dummy; } ;
struct TYPE_10__ {int linktype; } ;
typedef  TYPE_1__ compiler_state_t ;

/* Variables and functions */
#define  DLT_EN10MB 138 
#define  DLT_FDDI 137 
#define  DLT_IEEE802 136 
#define  DLT_IEEE802_11 135 
#define  DLT_IEEE802_11_RADIO 134 
#define  DLT_IEEE802_11_RADIO_AVS 133 
#define  DLT_IP_OVER_FC 132 
#define  DLT_NETANALYZER 131 
#define  DLT_NETANALYZER_TRANSPARENT 130 
#define  DLT_PPI 129 
#define  DLT_PRISM_HEADER 128 
 scalar_t__ Q_DEFAULT ; 
 scalar_t__ Q_HOST ; 
 scalar_t__ Q_LINK ; 
 int /*<<< orphan*/  bpf_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_ehostop (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 struct block* gen_fhostop (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 struct block* gen_ipfchostop (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 struct block* gen_prevlinkhdr_check (TYPE_1__*) ; 
 struct block* gen_thostop (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 struct block* gen_wlanhostop (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

struct block *
gen_ecode(compiler_state_t *cstate, const u_char *eaddr, struct qual q)
{
	struct block *b, *tmp;

	if ((q.addr == Q_HOST || q.addr == Q_DEFAULT) && q.proto == Q_LINK) {
		switch (cstate->linktype) {
		case DLT_EN10MB:
		case DLT_NETANALYZER:
		case DLT_NETANALYZER_TRANSPARENT:
			tmp = gen_prevlinkhdr_check(cstate);
			b = gen_ehostop(cstate, eaddr, (int)q.dir);
			if (tmp != NULL)
				gen_and(tmp, b);
			return b;
		case DLT_FDDI:
			return gen_fhostop(cstate, eaddr, (int)q.dir);
		case DLT_IEEE802:
			return gen_thostop(cstate, eaddr, (int)q.dir);
		case DLT_IEEE802_11:
		case DLT_PRISM_HEADER:
		case DLT_IEEE802_11_RADIO_AVS:
		case DLT_IEEE802_11_RADIO:
		case DLT_PPI:
			return gen_wlanhostop(cstate, eaddr, (int)q.dir);
		case DLT_IP_OVER_FC:
			return gen_ipfchostop(cstate, eaddr, (int)q.dir);
		default:
			bpf_error(cstate, "ethernet addresses supported only on ethernet/FDDI/token ring/802.11/ATM LANE/Fibre Channel");
			break;
		}
	}
	bpf_error(cstate, "ethernet address used in non-ether expression");
	/* NOTREACHED */
}