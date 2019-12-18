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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct mbuf {size_t* m_data; int m_len; struct mbuf* m_next; } ;
struct TYPE_6__ {int km_flags; } ;
struct krb5_context {int /*<<< orphan*/  kc_checksumkey; TYPE_3__* kc_encryptkey; TYPE_2__ kc_msg_order; TYPE_3__* kc_tokenkey; } ;
struct TYPE_7__ {TYPE_1__* ks_class; } ;
struct TYPE_5__ {size_t ec_checksumlen; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int GSS_C_REPLAY_FLAG ; 
 int GSS_C_SEQUENCE_FLAG ; 
 scalar_t__ GSS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSS_S_BAD_SIG ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_DEFECTIVE_TOKEN ; 
 int /*<<< orphan*/  MGET (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bcmp (size_t*,size_t*,size_t) ; 
 scalar_t__ is_initiator (struct krb5_context*) ; 
 int /*<<< orphan*/  krb5_checksum (int /*<<< orphan*/ ,int,struct mbuf*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  krb5_decrypt (TYPE_3__*,struct mbuf*,int,size_t,int*,int) ; 
 int /*<<< orphan*/  krb5_sequence_check (struct krb5_context*,int) ; 
 int* krb5_verify_token (char*,size_t,struct mbuf**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,size_t,size_t,int*) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_getptr (struct mbuf*,size_t,int*) ; 
 struct mbuf* m_last (struct mbuf*) ; 
 size_t m_length (struct mbuf*,struct mbuf**) ; 
 struct mbuf* m_split (struct mbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_trim (struct mbuf*,size_t) ; 
 size_t token_length (TYPE_3__*) ; 

__attribute__((used)) static OM_uint32
krb5_unwrap_old(struct krb5_context *kc, struct mbuf **mp, int *conf_state,
    uint8_t sgn_alg[2], uint8_t seal_alg[2])
{
	OM_uint32 res;
	struct mbuf *m, *mlast, *hm, *cm, *n;
	uint8_t *p, dir;
	size_t mlen, tlen, elen, datalen, padlen;
	size_t cklen;
	uint8_t buf[32];
	uint32_t seq;
	int i, conf;

	m = *mp;
	mlen = m_length(m, &mlast);

	tlen = token_length(kc->kc_tokenkey);
	cklen = kc->kc_tokenkey->ks_class->ec_checksumlen;

	p = krb5_verify_token("\x02\x01", tlen, &m, &elen, TRUE);
	*mp = m;
	if (!p)
		return (GSS_S_DEFECTIVE_TOKEN);
	datalen = elen - tlen;

	/*
	 * Trim the framing header first to make life a little easier
	 * later.
	 */
	m_adj(m, p - (uint8_t *) m->m_data);

	/* TOK_ID */
	p += 2;

	/* SGN_ALG */
	if (p[0] != sgn_alg[0] || p[1] != sgn_alg[1])
		return (GSS_S_DEFECTIVE_TOKEN);
	p += 2;

	/* SEAL_ALG */
	if (p[0] == seal_alg[0] && p[1] == seal_alg[1])
		conf = 1;
	else if (p[0] == 0xff && p[1] == 0xff)
		conf = 0;
	else
		return (GSS_S_DEFECTIVE_TOKEN);
	p += 2;

	if (p[0] != 0xff || p[1] != 0xff)
		return (GSS_S_DEFECTIVE_TOKEN);
	p += 2;

	/*
	 * SND_SEQ:
	 *
	 * Take the four bytes of the sequence number least
	 * significant first (most significant for ARCFOUR) followed
	 * by four bytes of direction marker (zero for initiator and
	 * 0xff for acceptor). Encrypt that data using the SGN_CKSUM
	 * as IV.
	 */
	krb5_decrypt(kc->kc_tokenkey, m, 8, 8, p + 8, 8);
	if (sgn_alg[0] == 0x11) {
		seq = p[3] | (p[2] << 8) | (p[1] << 16) | (p[0] << 24);
	} else {
		seq = p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
	}

	if (is_initiator(kc)) {
		dir = 0xff;
	} else {
		dir = 0;
	}
	if (p[4] != dir || p[5] != dir || p[6] != dir || p[7] != dir)
		return (GSS_S_DEFECTIVE_TOKEN);

	if (kc->kc_msg_order.km_flags &
	    (GSS_C_REPLAY_FLAG | GSS_C_SEQUENCE_FLAG)) {
		res = krb5_sequence_check(kc, seq);
		if (GSS_ERROR(res))
			return (res);
	} else {
		res = GSS_S_COMPLETE;
	}

	/*
	 * If the token was encrypted, decode it in-place.
	 */
	if (conf) {
		/*
		 * Decrypt the padded message with an IV of zero for
		 * DES and DES3 or an IV of the big-endian encoded
		 * sequence number for ARCFOUR.
		 */
		if (seal_alg[0] == 0x10) {
			krb5_decrypt(kc->kc_encryptkey, m, 16 + cklen,
			    datalen, p, 4);
		} else {
			krb5_decrypt(kc->kc_encryptkey, m, 16 + cklen,
			    datalen, NULL, 0);
		}
	}
	if (conf_state)
		*conf_state = conf;

	/*
	 * Check the trailing pad bytes.
	 * RFC1964 specifies between 1<->8 bytes, each with a binary value
	 * equal to the number of bytes.
	 */
	if (mlast->m_len > 0)
		padlen = mlast->m_data[mlast->m_len - 1];
	else {
		n = m_getptr(m, tlen + datalen - 1, &i);
		/*
		 * When the position is exactly equal to the # of data bytes
		 * in the mbuf list, m_getptr() will return the last mbuf in
		 * the list and an off == m_len for that mbuf, so that case
		 * needs to be checked as well as a NULL return.
		 */
		if (n == NULL || n->m_len == i)
			return (GSS_S_DEFECTIVE_TOKEN);
		padlen = n->m_data[i];
	}
	if (padlen < 1 || padlen > 8 || padlen > tlen + datalen)
		return (GSS_S_DEFECTIVE_TOKEN);
	m_copydata(m, tlen + datalen - padlen, padlen, buf);
	for (i = 0; i < padlen; i++) {
		if (buf[i] != padlen) {
			return (GSS_S_DEFECTIVE_TOKEN);
		}
	}

	/*
	 * SGN_CKSUM:
	 *
	 * Calculate the keyed checksum of the token header plus the
	 * padded message. We do a little mbuf surgery to trim out the
	 * parts we don't want to checksum.
	 */
	hm = m;
	*mp = m = m_split(m, 16 + cklen, M_WAITOK);
	mlast = m_last(m);
	hm->m_len = 8;
	hm->m_next = m;
	MGET(cm, M_WAITOK, MT_DATA);
	cm->m_len = cklen;
	mlast->m_next = cm;

	krb5_checksum(kc->kc_checksumkey, 13, hm, 0, datalen + 8, cklen);
	hm->m_next = NULL;
	mlast->m_next = NULL;

	if (bcmp(cm->m_data, hm->m_data + 16, cklen)) {
		m_freem(hm);
		m_free(cm);
		return (GSS_S_BAD_SIG);
	}
	m_freem(hm);
	m_free(cm);

	/*
	 * Trim off the confounder and padding.
	 */
	m_adj(m, 8);
	if (mlast->m_len >= padlen) {
		mlast->m_len -= padlen;
	} else {
		m_trim(m, datalen - 8 - padlen);
	}

	*mp = m;
	return (res);
}