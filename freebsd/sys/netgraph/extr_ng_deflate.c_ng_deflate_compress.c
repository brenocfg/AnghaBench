#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
typedef  TYPE_3__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_9__ {scalar_t__* next_in; int avail_in; int* next_out; int avail_out; int /*<<< orphan*/  msg; } ;
struct TYPE_7__ {int InOctets; int OutOctets; int /*<<< orphan*/  FramesComp; int /*<<< orphan*/  Errors; int /*<<< orphan*/  FramesUncomp; int /*<<< orphan*/  FramesPlain; } ;
struct TYPE_8__ {scalar_t__* inbuf; int* outbuf; int /*<<< orphan*/  seqnum; TYPE_2__ stats; TYPE_4__ cx; } ;

/* Variables and functions */
 int DEFLATE_BUF_SIZE ; 
 int DEFLATE_HDRLEN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 TYPE_3__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROT_COMPD ; 
 int Z_OK ; 
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 int /*<<< orphan*/  be16enc (int*,int /*<<< orphan*/ ) ; 
 int deflate (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int /*<<< orphan*/  m_copyback (struct mbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_unshare (struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_deflate_compress(node_p node, struct mbuf *m, struct mbuf **resultp)
{
	const priv_p 	priv = NG_NODE_PRIVATE(node);
	int 		outlen, inlen;
	int 		rtn;

	/* Initialize. */
	*resultp = NULL;

	inlen = m->m_pkthdr.len;

	priv->stats.FramesPlain++;
	priv->stats.InOctets+=inlen;

	if (inlen > DEFLATE_BUF_SIZE) {
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
	m_copydata(m, 0, inlen, (caddr_t)priv->inbuf);
	outlen = DEFLATE_BUF_SIZE;

	/* Compress "inbuf" into "outbuf". */
	/* Prepare to compress. */
	if (priv->inbuf[0] != 0) {
		priv->cx.next_in = priv->inbuf;
		priv->cx.avail_in = inlen;
	} else {
		priv->cx.next_in = priv->inbuf + 1; /* compress protocol */
		priv->cx.avail_in = inlen - 1;
	}
	priv->cx.next_out = priv->outbuf + 2 + DEFLATE_HDRLEN;
	priv->cx.avail_out = outlen - 2 - DEFLATE_HDRLEN;

	/* Compress. */
	rtn = deflate(&priv->cx, Z_SYNC_FLUSH);

	/* Check return value. */
	if (rtn != Z_OK) {
		priv->stats.Errors++;
		log(LOG_NOTICE, "ng_deflate: compression error: %d (%s)\n",
		    rtn, priv->cx.msg);
		NG_FREE_M(m);
		return (EINVAL);
	}

	/* Calculate resulting size. */
	outlen -= priv->cx.avail_out;
	/*
	 * Z_SYNC_FLUSH completes the current deflate block and follows
	 * it with an empty stored block that is three bits plus filler
	 * bits to the next byte, followed by four bytes (00 00 ff ff).
	 * RFC 1979 Section 2.1, "Data" requires the four bytes be
	 * removed before transmission.
	 */
	outlen -= 4;
	MPASS(outlen > 0);
	MPASS(priv->outbuf[outlen + 0] == 0x00);
	MPASS(priv->outbuf[outlen + 1] == 0x00);
	MPASS(priv->outbuf[outlen + 2] == 0xff);
	MPASS(priv->outbuf[outlen + 3] == 0xff);

	/* If we can't compress this packet, send it as-is. */
	if (outlen > inlen) {
		/* Return original packet uncompressed. */
		*resultp = m;
		priv->stats.FramesUncomp++;
		priv->stats.OutOctets+=inlen;
	} else {
		/* Install header. */
		be16enc(priv->outbuf, PROT_COMPD);
		be16enc(priv->outbuf + 2, priv->seqnum);

		/* Return packet in an mbuf. */
		m_copyback(m, 0, outlen, (caddr_t)priv->outbuf);
		if (m->m_pkthdr.len < outlen) {
			m_freem(m);
			priv->stats.Errors++;
			return (ENOMEM);
		} else if (outlen < m->m_pkthdr.len)
			m_adj(m, outlen - m->m_pkthdr.len);
		*resultp = m;
		priv->stats.FramesComp++;
		priv->stats.OutOctets+=outlen;
	}

	/* Update sequence number. */
	priv->seqnum++;

	return (0);
}