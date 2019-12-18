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
struct qual {int proto; int dir; int addr; } ;
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  int bpf_u_int32 ;

/* Variables and functions */
 int IPPROTO_SCTP ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int PROTO_UNDEF ; 
 int Q_DECNET ; 
#define  Q_DEFAULT 136 
#define  Q_GATEWAY 135 
#define  Q_HOST 134 
 int Q_LINK ; 
#define  Q_NET 133 
#define  Q_PORT 132 
#define  Q_PORTRANGE 131 
#define  Q_PROTO 130 
#define  Q_PROTOCHAIN 129 
 int Q_SCTP ; 
 int Q_TCP ; 
 int Q_UDP ; 
#define  Q_UNDEF 128 
 int __pcap_atodn (char const*,int*) ; 
 int __pcap_atoin (char const*,int*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bpf_error (int /*<<< orphan*/ *,char*,...) ; 
 struct block* gen_host (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  gen_or (int /*<<< orphan*/ ,struct block*) ; 
 struct block* gen_port (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  gen_port6 (int /*<<< orphan*/ *,int,int,int) ; 
 struct block* gen_portrange (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  gen_portrange6 (int /*<<< orphan*/ *,int,int,int,int) ; 
 struct block* gen_proto (int /*<<< orphan*/ *,int,int,int) ; 
 struct block* gen_protochain (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  syntax (int /*<<< orphan*/ *) ; 

struct block *
gen_ncode(compiler_state_t *cstate, const char *s, bpf_u_int32 v, struct qual q)
{
	bpf_u_int32 mask;
	int proto = q.proto;
	int dir = q.dir;
	register int vlen;

	if (s == NULL)
		vlen = 32;
	else if (q.proto == Q_DECNET) {
		vlen = __pcap_atodn(s, &v);
		if (vlen == 0)
			bpf_error(cstate, "malformed decnet address '%s'", s);
	} else
		vlen = __pcap_atoin(s, &v);

	switch (q.addr) {

	case Q_DEFAULT:
	case Q_HOST:
	case Q_NET:
		if (proto == Q_DECNET)
			return gen_host(cstate, v, 0, proto, dir, q.addr);
		else if (proto == Q_LINK) {
			bpf_error(cstate, "illegal link layer address");
		} else {
			mask = 0xffffffff;
			if (s == NULL && q.addr == Q_NET) {
				/* Promote short net number */
				while (v && (v & 0xff000000) == 0) {
					v <<= 8;
					mask <<= 8;
				}
			} else {
				/* Promote short ipaddr */
				v <<= 32 - vlen;
				mask <<= 32 - vlen ;
			}
			return gen_host(cstate, v, mask, proto, dir, q.addr);
		}

	case Q_PORT:
		if (proto == Q_UDP)
			proto = IPPROTO_UDP;
		else if (proto == Q_TCP)
			proto = IPPROTO_TCP;
		else if (proto == Q_SCTP)
			proto = IPPROTO_SCTP;
		else if (proto == Q_DEFAULT)
			proto = PROTO_UNDEF;
		else
			bpf_error(cstate, "illegal qualifier of 'port'");

		if (v > 65535)
			bpf_error(cstate, "illegal port number %u > 65535", v);

	    {
		struct block *b;
		b = gen_port(cstate, (int)v, proto, dir);
		gen_or(gen_port6(cstate, (int)v, proto, dir), b);
		return b;
	    }

	case Q_PORTRANGE:
		if (proto == Q_UDP)
			proto = IPPROTO_UDP;
		else if (proto == Q_TCP)
			proto = IPPROTO_TCP;
		else if (proto == Q_SCTP)
			proto = IPPROTO_SCTP;
		else if (proto == Q_DEFAULT)
			proto = PROTO_UNDEF;
		else
			bpf_error(cstate, "illegal qualifier of 'portrange'");

		if (v > 65535)
			bpf_error(cstate, "illegal port number %u > 65535", v);

	    {
		struct block *b;
		b = gen_portrange(cstate, (int)v, (int)v, proto, dir);
		gen_or(gen_portrange6(cstate, (int)v, (int)v, proto, dir), b);
		return b;
	    }

	case Q_GATEWAY:
		bpf_error(cstate, "'gateway' requires a name");
		/* NOTREACHED */

	case Q_PROTO:
		return gen_proto(cstate, (int)v, proto, dir);

	case Q_PROTOCHAIN:
		return gen_protochain(cstate, (int)v, proto, dir);

	case Q_UNDEF:
		syntax(cstate);
		/* NOTREACHED */

	default:
		abort();
		/* NOTREACHED */
	}
	/* NOTREACHED */
}