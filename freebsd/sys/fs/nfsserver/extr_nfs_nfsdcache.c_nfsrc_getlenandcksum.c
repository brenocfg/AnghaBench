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
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  scalar_t__ mbuf_t ;

/* Variables and functions */
 int NFSRVCACHE_CHECKLEN ; 
 int /*<<< orphan*/  in_cksum (scalar_t__,int) ; 
 scalar_t__ mbuf_len (scalar_t__) ; 
 scalar_t__ mbuf_next (scalar_t__) ; 

__attribute__((used)) static int
nfsrc_getlenandcksum(mbuf_t m1, u_int16_t *cksum)
{
	int len = 0, cklen;
	mbuf_t m;

	m = m1;
	while (m) {
		len += mbuf_len(m);
		m = mbuf_next(m);
	}
	cklen = (len > NFSRVCACHE_CHECKLEN) ? NFSRVCACHE_CHECKLEN : len;
	*cksum = in_cksum(m1, cklen);
	return (len);
}