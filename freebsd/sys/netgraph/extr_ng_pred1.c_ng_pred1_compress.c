#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int u_char ;
struct TYPE_5__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
typedef  TYPE_3__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {int InOctets; int OutOctets; int /*<<< orphan*/  Errors; int /*<<< orphan*/  FramesUncomp; int /*<<< orphan*/  FramesComp; int /*<<< orphan*/  FramesPlain; } ;
struct TYPE_7__ {int* inbuf; int* outbuf; TYPE_2__ stats; } ;

/* Variables and functions */
 int Crc16 (int,int*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 TYPE_3__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int PPP_INITFCS ; 
 int PRED1_BUF_SIZE ; 
 int Pred1Compress (int /*<<< orphan*/ ,int*,int*,int) ; 
 int htons (int) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int /*<<< orphan*/  m_copyback (struct mbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_unshare (struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_pred1_compress(node_p node, struct mbuf *m, struct mbuf **resultp)
{
	const priv_p 	priv = NG_NODE_PRIVATE(node);
	int 		outlen, inlen;
	u_char		*out;
	uint16_t	fcs, lenn;
	int		len;

	/* Initialize. */
	*resultp = NULL;

	inlen = m->m_pkthdr.len;

	priv->stats.FramesPlain++;
	priv->stats.InOctets += inlen;

	/* Reserve space for expansion. */
	if (inlen > (PRED1_BUF_SIZE*8/9 + 1 + 4)) {
		priv->stats.Errors++;
		NG_FREE_M(m);
		return (ENOMEM);
	}

	/* We must own the mbuf chain exclusively to modify it. */
	m = m_unshare(m, M_NOWAIT);
	if (m == NULL) {
		priv->stats.Errors++;
		return (ENOMEM);
	}

	/* Work with contiguous regions of memory. */
	m_copydata(m, 0, inlen, (caddr_t)(priv->inbuf + 2));

	lenn = htons(inlen & 0x7FFF);

	/* Compute FCS. */
	fcs = Crc16(PPP_INITFCS, (u_char *)&lenn, 2);
	fcs = Crc16(fcs, priv->inbuf + 2, inlen);
	fcs = ~fcs;

	/* Compress data. */
	len = Pred1Compress(node, priv->inbuf + 2, priv->outbuf + 2, inlen);

	/* What happened? */
	if (len < inlen) {
		out = priv->outbuf;
		outlen = 2 + len;
		*(uint16_t *)out = lenn;
		*out |= 0x80;
		priv->stats.FramesComp++;
	} else {
		out = priv->inbuf;
		outlen = 2 + inlen;
		*(uint16_t *)out = lenn;
		priv->stats.FramesUncomp++;
	}

	/* Add FCS. */
	(out + outlen)[0] = fcs & 0xFF;
	(out + outlen)[1] = fcs >> 8;

	/* Calculate resulting size. */
	outlen += 2;

	/* Return packet in an mbuf. */
	m_copyback(m, 0, outlen, (caddr_t)out);
	if (m->m_pkthdr.len < outlen) {
		m_freem(m);
		priv->stats.Errors++;
		return (ENOMEM);
	} else if (outlen < m->m_pkthdr.len)
		m_adj(m, outlen - m->m_pkthdr.len);
	*resultp = m;
	priv->stats.OutOctets += outlen;

	return (0);
}