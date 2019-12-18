#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct mbuf {int m_len; int* m_data; struct mbuf* m_next; } ;
struct krb5_key_state {TYPE_1__* ks_class; } ;
struct TYPE_4__ {int km_flags; } ;
struct krb5_context {int kc_more_flags; TYPE_2__ kc_msg_order; struct krb5_key_state* kc_recv_sign_Kc; } ;
struct TYPE_3__ {size_t ec_checksumlen; } ;
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
 int GSS_TOKEN_SENT_BY_ACCEPTOR ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bcmp (char*,int*,size_t) ; 
 scalar_t__ is_initiator (struct krb5_context*) ; 
 int /*<<< orphan*/  krb5_checksum (struct krb5_key_state*,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  krb5_sequence_check (struct krb5_context*,int) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int,size_t,char*) ; 
 size_t m_length (struct mbuf*,struct mbuf**) ; 

__attribute__((used)) static OM_uint32
krb5_verify_mic_new(struct krb5_context *kc, struct mbuf *m, struct mbuf *mic)
{
	OM_uint32 res;
	struct krb5_key_state *key = kc->kc_recv_sign_Kc;
	struct mbuf *mlast;
	uint8_t *p;
	int flags;
	size_t mlen, cklen;
	char buf[32];

	mlen = m_length(m, &mlast);
	cklen = key->ks_class->ec_checksumlen;

	KASSERT(mic->m_next == NULL, ("MIC should be contiguous"));
	if (mic->m_len != 16 + cklen)
		return (GSS_S_DEFECTIVE_TOKEN);
	p = mic->m_data;

	/* TOK_ID */
	if (p[0] != 0x04)
		return (GSS_S_DEFECTIVE_TOKEN);
	if (p[1] != 0x04)
		return (GSS_S_DEFECTIVE_TOKEN);

	/* Flags */
	flags = 0;
	if (is_initiator(kc))
		flags |= GSS_TOKEN_SENT_BY_ACCEPTOR;
	if (kc->kc_more_flags & ACCEPTOR_SUBKEY)
		flags |= GSS_TOKEN_ACCEPTOR_SUBKEY;
	if (p[2] != flags)
		return (GSS_S_DEFECTIVE_TOKEN);

	/* Filler */
	if (p[3] != 0xff)
		return (GSS_S_DEFECTIVE_TOKEN);
	if (p[4] != 0xff)
		return (GSS_S_DEFECTIVE_TOKEN);
	if (p[5] != 0xff)
		return (GSS_S_DEFECTIVE_TOKEN);
	if (p[6] != 0xff)
		return (GSS_S_DEFECTIVE_TOKEN);
	if (p[7] != 0xff)
		return (GSS_S_DEFECTIVE_TOKEN);

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
	 * SGN_CKSUM:
	 *
	 * Calculate the keyed checksum of the message plus the first
	 * 16 bytes of the token header.
	 */
	m_copydata(mic, 16, cklen, buf);
	mlast->m_next = mic;
	krb5_checksum(key, 0, m, 0, mlen + 16, cklen);
	mlast->m_next = NULL;
	if (bcmp(buf, p + 16, cklen)) {
		return (GSS_S_BAD_SIG);
	}

	return (GSS_S_COMPLETE);
}