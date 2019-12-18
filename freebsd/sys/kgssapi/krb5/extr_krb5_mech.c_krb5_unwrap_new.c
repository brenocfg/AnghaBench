#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct mbuf {int m_len; int* m_data; struct mbuf* m_next; } ;
struct krb5_key_state {struct krb5_encryption_class* ks_class; } ;
struct krb5_encryption_class {size_t ec_blocklen; size_t ec_checksumlen; } ;
struct TYPE_2__ {int km_flags; } ;
struct krb5_context {int kc_more_flags; TYPE_1__ kc_msg_order; struct krb5_key_state* kc_recv_seal_Kc; struct krb5_key_state* kc_recv_seal_Ki; struct krb5_key_state* kc_recv_seal_Ke; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int ACCEPTOR_SUBKEY ; 
 int GSS_C_REPLAY_FLAG ; 
 int GSS_C_SEQUENCE_FLAG ; 
 scalar_t__ GSS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSS_S_BAD_SIG ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_DEFECTIVE_TOKEN ; 
 int /*<<< orphan*/  GSS_S_UNSEQ_TOKEN ; 
 int GSS_TOKEN_ACCEPTOR_SUBKEY ; 
 int GSS_TOKEN_SEALED ; 
 int GSS_TOKEN_SENT_BY_ACCEPTOR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ bcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 scalar_t__ is_initiator (struct krb5_context*) ; 
 int /*<<< orphan*/  krb5_checksum (struct krb5_key_state*,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  krb5_decrypt (struct krb5_key_state*,struct mbuf*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_sequence_check (struct krb5_context*,int) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,size_t) ; 
 int /*<<< orphan*/  m_cat (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,size_t,size_t,char*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_last (struct mbuf*) ; 
 size_t m_length (struct mbuf*,struct mbuf**) ; 
 struct mbuf* m_pullup (struct mbuf*,int) ; 
 struct mbuf* m_split (struct mbuf*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_trim (struct mbuf*,size_t) ; 

__attribute__((used)) static OM_uint32
krb5_unwrap_new(struct krb5_context *kc, struct mbuf **mp, int *conf_state)
{
	OM_uint32 res;
	struct krb5_key_state *Ke = kc->kc_recv_seal_Ke;
	struct krb5_key_state *Ki = kc->kc_recv_seal_Ki;
	struct krb5_key_state *Kc = kc->kc_recv_seal_Kc;
	const struct krb5_encryption_class *ec = Ke->ks_class;
	struct mbuf *m, *mlast, *hm, *cm;
	uint8_t *p, *pp;
	int sealed, flags, EC, RRC;
	size_t blen, cklen, ctlen, mlen, plen, tlen;
	char buf[32], buf2[32];

	m = *mp;
	mlen = m_length(m, &mlast);

	if (mlen <= 16)
		return (GSS_S_DEFECTIVE_TOKEN);
	if (m->m_len < 16) {
		m = m_pullup(m, 16);
		*mp = m;
	}
	p = m->m_data;

	/* TOK_ID */
	if (p[0] != 0x05)
		return (GSS_S_DEFECTIVE_TOKEN);
	if (p[1] != 0x04)
		return (GSS_S_DEFECTIVE_TOKEN);

	/* Flags */
	sealed = p[2] & GSS_TOKEN_SEALED;
	flags = sealed;
	if (is_initiator(kc))
		flags |= GSS_TOKEN_SENT_BY_ACCEPTOR;
	if (kc->kc_more_flags & ACCEPTOR_SUBKEY)
		flags |= GSS_TOKEN_ACCEPTOR_SUBKEY;
	if (p[2] != flags)
		return (GSS_S_DEFECTIVE_TOKEN);

	/* Filler */
	if (p[3] != 0xff)
		return (GSS_S_DEFECTIVE_TOKEN);

	/* EC + RRC */
	EC = (p[4] << 8) + p[5];
	RRC = (p[6] << 8) + p[7];

	/* SND_SEQ */
	if (kc->kc_msg_order.km_flags &
		(GSS_C_REPLAY_FLAG | GSS_C_SEQUENCE_FLAG)) {
		uint32_t seq;
		if (p[8] || p[9] || p[10] || p[11]) {
			res = GSS_S_UNSEQ_TOKEN;
		} else {
			seq = (p[12] << 24) | (p[13] << 16)
				| (p[14] << 8) | p[15];
			res = krb5_sequence_check(kc, seq);
		}
		if (GSS_ERROR(res))
			return (res);
	} else {
		res = GSS_S_COMPLETE;
	}

	/*
	 * Separate the header before dealing with RRC. We only need
	 * to keep the header if the message isn't encrypted.
	 */
	if (sealed) {
		hm = NULL;
		m_adj(m, 16);
	} else {
		hm = m;
		*mp = m = m_split(m, 16, M_WAITOK);
		mlast = m_last(m);
	}

	/*
	 * Undo the effects of RRC by rotating left.
	 */
	if (RRC > 0) {
		struct mbuf *rm;
		size_t rlen;

		rlen = mlen - 16;
		if (RRC <= sizeof(buf) && m->m_len >= rlen) {
			/*
			 * Simple case, just rearrange the bytes in m.
			 */
			bcopy(m->m_data, buf, RRC);
			bcopy(m->m_data + RRC, m->m_data, rlen - RRC);
			bcopy(buf, m->m_data + rlen - RRC, RRC);
		} else {
			/*
			 * More complicated - rearrange the mbuf
			 * chain.
			 */
			rm = m;
			*mp = m = m_split(m, RRC, M_WAITOK);
			m_cat(m, rm);
			mlast = rm;
		}
	}

	blen = ec->ec_blocklen;
	cklen = ec->ec_checksumlen;
	if (sealed) {
		/*
		 * Decrypt according to RFC 4121 section 4.2 and RFC
		 * 3961 section 5.3. The message must be large enough
		 * for a blocksize confounder, at least one block of
		 * cyphertext and a checksum.
		 */
		if (mlen < 16 + 2*blen + cklen)
			return (GSS_S_DEFECTIVE_TOKEN);

		ctlen = mlen - 16 - cklen;
		krb5_decrypt(Ke, m, 0, ctlen, NULL, 0);

		/*
		 * The size of the plaintext is ctlen minus blocklen
		 * (for the confounder), 16 (for the copy of the token
		 * header) and EC (for the filler). The actual
		 * plaintext starts after the confounder.
		 */
		plen = ctlen - blen - 16 - EC;
		pp = p + 16 + blen;

		/*
		 * Checksum the padded plaintext.
		 */
		m_copydata(m, ctlen, cklen, buf);
		krb5_checksum(Ki, 0, m, 0, ctlen, cklen);
		m_copydata(m, ctlen, cklen, buf2);

		if (bcmp(buf, buf2, cklen))
			return (GSS_S_BAD_SIG);

		/*
		 * Trim the message back to just plaintext.
		 */
		m_adj(m, blen);
		tlen = 16 + EC + cklen;
		if (mlast->m_len >= tlen) {
			mlast->m_len -= tlen;
		} else {
			m_trim(m, plen);
		}
	} else {
		/*
		 * The plaintext message is followed by a checksum of
		 * the plaintext plus a version of the header where EC
		 * and RRC are set to zero. Also, the original EC must
		 * be our checksum size.
		 */
		if (mlen < 16 + cklen || EC != cklen)
			return (GSS_S_DEFECTIVE_TOKEN);

		/*
		 * The size of the plaintext is simply the message
		 * size less header and checksum. The plaintext starts
		 * right after the header (which we have saved in hm).
		 */
		plen = mlen - 16 - cklen;

		/*
		 * Insert a copy of the header (with EC and RRC set to
		 * zero) between the plaintext message and the
		 * checksum.
		 */
		p = hm->m_data;
		p[4] = p[5] = p[6] = p[7] = 0;

		cm = m_split(m, plen, M_WAITOK);
		mlast = m_last(m);
		m->m_next = hm;
		hm->m_next = cm;

		bcopy(cm->m_data, buf, cklen);
		krb5_checksum(Kc, 0, m, 0, plen + 16, cklen);
		if (bcmp(cm->m_data, buf, cklen))
			return (GSS_S_BAD_SIG);

		/*
		 * The checksum matches, discard all buf the plaintext.
		 */
		mlast->m_next = NULL;
		m_freem(hm);
	}

	if (conf_state)
		*conf_state = (sealed != 0);

	return (res);
}