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

/* Variables and functions */
 int /*<<< orphan*/  ETHERTYPE_IP ; 
#define  IPPROTO_SCTP 131 
#define  IPPROTO_TCP 130 
#define  IPPROTO_UDP 129 
#define  PROTO_UNDEF 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_linktype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 
 struct block* gen_portop (int /*<<< orphan*/ *,int,int const,int) ; 

__attribute__((used)) static struct block *
gen_port(compiler_state_t *cstate, int port, int ip_proto, int dir)
{
	struct block *b0, *b1, *tmp;

	/*
	 * ether proto ip
	 *
	 * For FDDI, RFC 1188 says that SNAP encapsulation is used,
	 * not LLC encapsulation with LLCSAP_IP.
	 *
	 * For IEEE 802 networks - which includes 802.5 token ring
	 * (which is what DLT_IEEE802 means) and 802.11 - RFC 1042
	 * says that SNAP encapsulation is used, not LLC encapsulation
	 * with LLCSAP_IP.
	 *
	 * For LLC-encapsulated ATM/"Classical IP", RFC 1483 and
	 * RFC 2225 say that SNAP encapsulation is used, not LLC
	 * encapsulation with LLCSAP_IP.
	 *
	 * So we always check for ETHERTYPE_IP.
	 */
	b0 = gen_linktype(cstate, ETHERTYPE_IP);

	switch (ip_proto) {
	case IPPROTO_UDP:
	case IPPROTO_TCP:
	case IPPROTO_SCTP:
		b1 = gen_portop(cstate, port, ip_proto, dir);
		break;

	case PROTO_UNDEF:
		tmp = gen_portop(cstate, port, IPPROTO_TCP, dir);
		b1 = gen_portop(cstate, port, IPPROTO_UDP, dir);
		gen_or(tmp, b1);
		tmp = gen_portop(cstate, port, IPPROTO_SCTP, dir);
		gen_or(tmp, b1);
		break;

	default:
		abort();
	}
	gen_and(b0, b1);
	return b1;
}