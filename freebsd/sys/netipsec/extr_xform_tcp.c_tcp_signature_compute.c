#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct tcphdr {int th_off; int /*<<< orphan*/  th_sum; } ;
struct secasvar {TYPE_6__* key_auth; TYPE_4__* sah; } ;
struct TYPE_11__ {int len; } ;
struct mbuf {TYPE_5__ m_pkthdr; } ;
struct TYPE_12__ {char* key_data; } ;
struct TYPE_7__ {int sa_family; } ;
struct TYPE_8__ {TYPE_1__ sa; } ;
struct TYPE_9__ {TYPE_2__ dst; } ;
struct TYPE_10__ {TYPE_3__ saidx; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  MD5Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,char*,int) ; 
 int _KEYLEN (TYPE_6__*) ; 
 int ip6_pseudo_compute (struct mbuf*,int /*<<< orphan*/ *) ; 
 int ip_pseudo_compute (struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_sa_recordxfer (struct secasvar*,struct mbuf*) ; 
 int /*<<< orphan*/  m_apply (struct mbuf*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_signature_apply ; 

__attribute__((used)) static int
tcp_signature_compute(struct mbuf *m, struct tcphdr *th,
    struct secasvar *sav, u_char *buf)
{
	MD5_CTX ctx;
	int len;
	u_short csum;

	MD5Init(&ctx);
	 /* Step 1: Update MD5 hash with IP(v6) pseudo-header. */
	switch (sav->sah->saidx.dst.sa.sa_family) {
#ifdef INET
	case AF_INET:
		len = ip_pseudo_compute(m, &ctx);
		break;
#endif
#ifdef INET6
	case AF_INET6:
		len = ip6_pseudo_compute(m, &ctx);
		break;
#endif
	default:
		return (EAFNOSUPPORT);
	}
	/*
	 * Step 2: Update MD5 hash with TCP header, excluding options.
	 * The TCP checksum must be set to zero.
	 */
	csum = th->th_sum;
	th->th_sum = 0;
	MD5Update(&ctx, (char *)th, sizeof(struct tcphdr));
	th->th_sum = csum;
	/*
	 * Step 3: Update MD5 hash with TCP segment data.
	 * Use m_apply() to avoid an early m_pullup().
	 */
	len += (th->th_off << 2);
	if (m->m_pkthdr.len - len > 0)
		m_apply(m, len, m->m_pkthdr.len - len,
		    tcp_signature_apply, &ctx);
	/*
	 * Step 4: Update MD5 hash with shared secret.
	 */
	MD5Update(&ctx, sav->key_auth->key_data, _KEYLEN(sav->key_auth));
	MD5Final(buf, &ctx);
	key_sa_recordxfer(sav, m);
	return (0);
}