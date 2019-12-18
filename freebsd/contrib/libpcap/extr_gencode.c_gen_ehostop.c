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
typedef  int /*<<< orphan*/  u_char ;
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  OR_LINKHDR ; 
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
 struct block* gen_bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 

__attribute__((used)) static struct block *
gen_ehostop(compiler_state_t *cstate, const u_char *eaddr, int dir)
{
	register struct block *b0, *b1;

	switch (dir) {
	case Q_SRC:
		return gen_bcmp(cstate, OR_LINKHDR, 6, 6, eaddr);

	case Q_DST:
		return gen_bcmp(cstate, OR_LINKHDR, 0, 6, eaddr);

	case Q_AND:
		b0 = gen_ehostop(cstate, eaddr, Q_SRC);
		b1 = gen_ehostop(cstate, eaddr, Q_DST);
		gen_and(b0, b1);
		return b1;

	case Q_DEFAULT:
	case Q_OR:
		b0 = gen_ehostop(cstate, eaddr, Q_SRC);
		b1 = gen_ehostop(cstate, eaddr, Q_DST);
		gen_or(b0, b1);
		return b1;

	case Q_ADDR1:
		bpf_error(cstate, "'addr1' and 'address1' are only supported on 802.11 with 802.11 headers");
		break;

	case Q_ADDR2:
		bpf_error(cstate, "'addr2' and 'address2' are only supported on 802.11 with 802.11 headers");
		break;

	case Q_ADDR3:
		bpf_error(cstate, "'addr3' and 'address3' are only supported on 802.11 with 802.11 headers");
		break;

	case Q_ADDR4:
		bpf_error(cstate, "'addr4' and 'address4' are only supported on 802.11 with 802.11 headers");
		break;

	case Q_RA:
		bpf_error(cstate, "'ra' is only supported on 802.11 with 802.11 headers");
		break;

	case Q_TA:
		bpf_error(cstate, "'ta' is only supported on 802.11 with 802.11 headers");
		break;
	}
	abort();
	/* NOTREACHED */
}