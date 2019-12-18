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
typedef  int /*<<< orphan*/  u_int ;
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  scalar_t__ bpf_u_int32 ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_W ; 
 int /*<<< orphan*/  OR_LINKPL ; 
#define  Q_ADDR1 138 
#define  Q_ADDR2 137 
#define  Q_ADDR3 136 
#define  Q_ADDR4 135 
#define  Q_AND 134 
#define  Q_DEFAULT 133 
#define  Q_DST 132 
#define  Q_OR 131 
#define  Q_RA 130 
#define  Q_SRC 129 
#define  Q_TA 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bpf_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_linktype (int /*<<< orphan*/ *,int) ; 
 struct block* gen_mcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 

__attribute__((used)) static struct block *
gen_hostop(compiler_state_t *cstate, bpf_u_int32 addr, bpf_u_int32 mask,
    int dir, int proto, u_int src_off, u_int dst_off)
{
	struct block *b0, *b1;
	u_int offset;

	switch (dir) {

	case Q_SRC:
		offset = src_off;
		break;

	case Q_DST:
		offset = dst_off;
		break;

	case Q_AND:
		b0 = gen_hostop(cstate, addr, mask, Q_SRC, proto, src_off, dst_off);
		b1 = gen_hostop(cstate, addr, mask, Q_DST, proto, src_off, dst_off);
		gen_and(b0, b1);
		return b1;

	case Q_OR:
	case Q_DEFAULT:
		b0 = gen_hostop(cstate, addr, mask, Q_SRC, proto, src_off, dst_off);
		b1 = gen_hostop(cstate, addr, mask, Q_DST, proto, src_off, dst_off);
		gen_or(b0, b1);
		return b1;

	case Q_ADDR1:
		bpf_error(cstate, "'addr1' and 'address1' are not valid qualifiers for addresses other than 802.11 MAC addresses");
		break;

	case Q_ADDR2:
		bpf_error(cstate, "'addr2' and 'address2' are not valid qualifiers for addresses other than 802.11 MAC addresses");
		break;

	case Q_ADDR3:
		bpf_error(cstate, "'addr3' and 'address3' are not valid qualifiers for addresses other than 802.11 MAC addresses");
		break;

	case Q_ADDR4:
		bpf_error(cstate, "'addr4' and 'address4' are not valid qualifiers for addresses other than 802.11 MAC addresses");
		break;

	case Q_RA:
		bpf_error(cstate, "'ra' is not a valid qualifier for addresses other than 802.11 MAC addresses");
		break;

	case Q_TA:
		bpf_error(cstate, "'ta' is not a valid qualifier for addresses other than 802.11 MAC addresses");
		break;

	default:
		abort();
	}
	b0 = gen_linktype(cstate, proto);
	b1 = gen_mcmp(cstate, OR_LINKPL, offset, BPF_W, (bpf_int32)addr, mask);
	gen_and(b0, b1);
	return b1;
}