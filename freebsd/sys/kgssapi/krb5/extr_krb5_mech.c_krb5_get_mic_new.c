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
struct krb5_key_state {TYPE_1__* ks_class; } ;
struct krb5_context {int kc_more_flags; int /*<<< orphan*/  kc_local_seqnumber; struct krb5_key_state* kc_send_sign_Kc; } ;
struct TYPE_2__ {size_t ec_checksumlen; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int ACCEPTOR_SUBKEY ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int GSS_TOKEN_ACCEPTOR_SUBKEY ; 
 int GSS_TOKEN_SENT_BY_ACCEPTOR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MGET (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_ALIGN (struct mbuf*,int) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int atomic_fetchadd_32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_acceptor (struct krb5_context*) ; 
 int /*<<< orphan*/  krb5_checksum (struct krb5_key_state*,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ,size_t,size_t) ; 
 size_t m_length (struct mbuf*,struct mbuf**) ; 

__attribute__((used)) static OM_uint32
krb5_get_mic_new(struct krb5_context *kc,  struct mbuf *m,
    struct mbuf **micp)
{
	struct krb5_key_state *key = kc->kc_send_sign_Kc;
	struct mbuf *mlast, *mic;
	uint8_t *p;
	int flags;
	size_t mlen, cklen;
	uint32_t seq;

	mlen = m_length(m, &mlast);
	cklen = key->ks_class->ec_checksumlen;

	KASSERT(16 + cklen <= MLEN, ("checksum too large for an mbuf"));
	MGET(mic, M_WAITOK, MT_DATA);
	M_ALIGN(mic, 16 + cklen);
	mic->m_len = 16 + cklen;
	p = mic->m_data;

	/* TOK_ID */
	p[0] = 0x04;
	p[1] = 0x04;

	/* Flags */
	flags = 0;
	if (is_acceptor(kc))
		flags |= GSS_TOKEN_SENT_BY_ACCEPTOR;
	if (kc->kc_more_flags & ACCEPTOR_SUBKEY)
		flags |= GSS_TOKEN_ACCEPTOR_SUBKEY;
	p[2] = flags;

	/* Filler */
	p[3] = 0xff;
	p[4] = 0xff;
	p[5] = 0xff;
	p[6] = 0xff;
	p[7] = 0xff;

	/* SND_SEQ */
	p[8] = 0;
	p[9] = 0;
	p[10] = 0;
	p[11] = 0;
	seq = atomic_fetchadd_32(&kc->kc_local_seqnumber, 1);
	p[12] = (seq >> 24);
	p[13] = (seq >> 16);
	p[14] = (seq >> 8);
	p[15] = (seq >> 0);

	/*
	 * SGN_CKSUM:
	 *
	 * Calculate the keyed checksum of the message plus the first
	 * 16 bytes of the token header.
	 */
	mlast->m_next = mic;
	krb5_checksum(key, 0, m, 0, mlen + 16, cklen);
	mlast->m_next = NULL;

	*micp = mic;
	return (GSS_S_COMPLETE);
}