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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint16_t ;
struct tls_record_layer {scalar_t__ tls_vmajor; scalar_t__ tls_vminor; int /*<<< orphan*/  tls_length; void* tls_type; } ;
struct mbuf_ext_pgs {int hdr_len; int trail_len; scalar_t__ npgs; scalar_t__ nrdy; void* record_type; scalar_t__ hdr; int /*<<< orphan*/  tls; } ;
struct TYPE_3__ {struct mbuf_ext_pgs* ext_pgs; } ;
struct mbuf {int m_len; int m_flags; TYPE_1__ m_ext; struct mbuf* m_next; } ;
struct TYPE_4__ {int max_frame_len; int tls_hlen; int tls_tlen; scalar_t__ cipher_algorithm; int tls_bs; scalar_t__ tls_vmajor; scalar_t__ tls_vminor; scalar_t__ iv; } ;
struct ktls_session {scalar_t__ mode; TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_LEN ; 
 scalar_t__ CRYPTO_AES_CBC ; 
 scalar_t__ CRYPTO_AES_NIST_GCM_16 ; 
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int M_NOMAP ; 
 int M_NOTREADY ; 
 scalar_t__ TCP_TLS_MODE_SW ; 
 scalar_t__ TLS_MAJOR_VER_ONE ; 
 scalar_t__ TLS_MINOR_VER_ONE ; 
 scalar_t__ TLS_MINOR_VER_THREE ; 
 scalar_t__ TLS_MINOR_VER_TWO ; 
 void* TLS_RLTYPE_APP ; 
 int /*<<< orphan*/  arc4rand (struct tls_record_layer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64enc (struct tls_record_layer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  ktls_hold (struct ktls_session*) ; 

int
ktls_frame(struct mbuf *top, struct ktls_session *tls, int *enq_cnt,
    uint8_t record_type)
{
	struct tls_record_layer *tlshdr;
	struct mbuf *m;
	struct mbuf_ext_pgs *pgs;
	uint64_t *noncep;
	uint16_t tls_len;
	int maxlen;

	maxlen = tls->params.max_frame_len;
	*enq_cnt = 0;
	for (m = top; m != NULL; m = m->m_next) {
		/*
		 * All mbufs in the chain should be non-empty TLS
		 * records whose payload does not exceed the maximum
		 * frame length.
		 */
		if (m->m_len > maxlen || m->m_len == 0)
			return (EINVAL);
		tls_len = m->m_len;

		/*
		 * TLS frames require unmapped mbufs to store session
		 * info.
		 */
		KASSERT((m->m_flags & M_NOMAP) != 0,
		    ("ktls_frame: mapped mbuf %p (top = %p)\n", m, top));

		pgs = m->m_ext.ext_pgs;

		/* Save a reference to the session. */
		pgs->tls = ktls_hold(tls);

		pgs->hdr_len = tls->params.tls_hlen;
		pgs->trail_len = tls->params.tls_tlen;
		if (tls->params.cipher_algorithm == CRYPTO_AES_CBC) {
			int bs, delta;

			/*
			 * AES-CBC pads messages to a multiple of the
			 * block size.  Note that the padding is
			 * applied after the digest and the encryption
			 * is done on the "plaintext || mac || padding".
			 * At least one byte of padding is always
			 * present.
			 *
			 * Compute the final trailer length assuming
			 * at most one block of padding.
			 * tls->params.sb_tls_tlen is the maximum
			 * possible trailer length (padding + digest).
			 * delta holds the number of excess padding
			 * bytes if the maximum were used.  Those
			 * extra bytes are removed.
			 */
			bs = tls->params.tls_bs;
			delta = (tls_len + tls->params.tls_tlen) & (bs - 1);
			pgs->trail_len -= delta;
		}
		m->m_len += pgs->hdr_len + pgs->trail_len;

		/* Populate the TLS header. */
		tlshdr = (void *)pgs->hdr;
		tlshdr->tls_vmajor = tls->params.tls_vmajor;

		/*
		 * TLS 1.3 masquarades as TLS 1.2 with a record type
		 * of TLS_RLTYPE_APP.
		 */
		if (tls->params.tls_vminor == TLS_MINOR_VER_THREE &&
		    tls->params.tls_vmajor == TLS_MAJOR_VER_ONE) {
			tlshdr->tls_vminor = TLS_MINOR_VER_TWO;
			tlshdr->tls_type = TLS_RLTYPE_APP;
			/* save the real record type for later */
			pgs->record_type = record_type;
		} else {
			tlshdr->tls_vminor = tls->params.tls_vminor;
			tlshdr->tls_type = record_type;
		}
		tlshdr->tls_length = htons(m->m_len - sizeof(*tlshdr));

		/*
		 * Store nonces / explicit IVs after the end of the
		 * TLS header.
		 *
		 * For GCM with TLS 1.2, an 8 byte nonce is copied
		 * from the end of the IV.  The nonce is then
		 * incremented for use by the next record.
		 *
		 * For CBC, a random nonce is inserted for TLS 1.1+.
		 */
		if (tls->params.cipher_algorithm == CRYPTO_AES_NIST_GCM_16 &&
		    tls->params.tls_vminor == TLS_MINOR_VER_TWO) {
			noncep = (uint64_t *)(tls->params.iv + 8);
			be64enc(tlshdr + 1, *noncep);
			(*noncep)++;
		} else if (tls->params.cipher_algorithm == CRYPTO_AES_CBC &&
		    tls->params.tls_vminor >= TLS_MINOR_VER_ONE)
			arc4rand(tlshdr + 1, AES_BLOCK_LEN, 0);

		/*
		 * When using SW encryption, mark the mbuf not ready.
		 * It will be marked ready via sbready() after the
		 * record has been encrypted.
		 *
		 * When using ifnet TLS, unencrypted TLS records are
		 * sent down the stack to the NIC.
		 */
		if (tls->mode == TCP_TLS_MODE_SW) {
			m->m_flags |= M_NOTREADY;
			pgs->nrdy = pgs->npgs;
			*enq_cnt += pgs->npgs;
		}
	}
	return (0);
}