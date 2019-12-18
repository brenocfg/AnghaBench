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
struct qual {int addr; int /*<<< orphan*/  dir; int /*<<< orphan*/  proto; } ;
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  int bpf_u_int32 ;

/* Variables and functions */
#define  Q_NET 128 
 int __pcap_atoin (char const*,int*) ; 
 int /*<<< orphan*/  bpf_error (int /*<<< orphan*/ *,char*,...) ; 
 struct block* gen_host (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct block *
gen_mcode(compiler_state_t *cstate, const char *s1, const char *s2,
    unsigned int masklen, struct qual q)
{
	register int nlen, mlen;
	bpf_u_int32 n, m;

	nlen = __pcap_atoin(s1, &n);
	/* Promote short ipaddr */
	n <<= 32 - nlen;

	if (s2 != NULL) {
		mlen = __pcap_atoin(s2, &m);
		/* Promote short ipaddr */
		m <<= 32 - mlen;
		if ((n & ~m) != 0)
			bpf_error(cstate, "non-network bits set in \"%s mask %s\"",
			    s1, s2);
	} else {
		/* Convert mask len to mask */
		if (masklen > 32)
			bpf_error(cstate, "mask length must be <= 32");
		if (masklen == 0) {
			/*
			 * X << 32 is not guaranteed by C to be 0; it's
			 * undefined.
			 */
			m = 0;
		} else
			m = 0xffffffff << (32 - masklen);
		if ((n & ~m) != 0)
			bpf_error(cstate, "non-network bits set in \"%s/%d\"",
			    s1, masklen);
	}

	switch (q.addr) {

	case Q_NET:
		return gen_host(cstate, n, m, q.proto, q.dir, q.addr);

	default:
		bpf_error(cstate, "Mask syntax for networks only");
		/* NOTREACHED */
	}
	/* NOTREACHED */
}