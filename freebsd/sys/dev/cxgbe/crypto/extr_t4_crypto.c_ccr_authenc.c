#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct wrqe {int dummy; } ;
struct cryptop {int /*<<< orphan*/  crp_buf; int /*<<< orphan*/  crp_flags; } ;
struct cryptodesc {scalar_t__ crd_len; int crd_alg; scalar_t__ crd_skip; int crd_flags; scalar_t__ crd_inject; char* crd_iv; } ;
struct cpl_rx_phys_dsgl {int dummy; } ;
struct TYPE_9__ {char* key; int /*<<< orphan*/  ctx_hdr; } ;
struct TYPE_8__ {void* ivgen_hdrlen; void* seqno_numivs; void* cipherstop_lo_authinsert; void* aadstart_cipherstop_hi; void* pldlen; void* op_ivinsrtofst; } ;
struct chcr_wr {TYPE_2__ key_ctx; TYPE_1__ sec_cpl; } ;
struct ccr_softc {int /*<<< orphan*/  adapter; int /*<<< orphan*/  tx_channel_id; int /*<<< orphan*/  stats_wr_nomem; int /*<<< orphan*/  txq; TYPE_5__* sg_ulptx; int /*<<< orphan*/  sg_crp; TYPE_5__* sg_dsgl; int /*<<< orphan*/  sg_iv_aad; } ;
struct TYPE_11__ {scalar_t__ key_len; scalar_t__ iv_len; char* enckey; char* deckey; int /*<<< orphan*/  key_ctx_hdr; int /*<<< orphan*/  cipher_mode; } ;
struct TYPE_10__ {scalar_t__ hash_len; scalar_t__ partial_digest_len; char* pads; int /*<<< orphan*/  auth_mode; struct auth_hash* auth_hash; } ;
struct ccr_session {TYPE_4__ blkcipher; TYPE_3__ hmac; } ;
struct auth_hash {scalar_t__ hashsize; } ;
struct TYPE_12__ {int sg_nseg; } ;

/* Variables and functions */
 int AES_BLOCK_LEN ; 
 scalar_t__ CHCR_DECRYPT_OP ; 
 scalar_t__ CHCR_ENCRYPT_OP ; 
 int CHCR_MAX_CRYPTO_IV_LEN ; 
 scalar_t__ CIPHER_TRANSHDR_SIZE (scalar_t__,int) ; 
 int /*<<< orphan*/  CPL_TX_SEC_PDU ; 
 int CRD_F_ENCRYPT ; 
 int CRD_F_IV_EXPLICIT ; 
 int CRD_F_IV_PRESENT ; 
#define  CRYPTO_AES_CBC 130 
#define  CRYPTO_AES_ICM 129 
#define  CRYPTO_AES_XTS 128 
 int /*<<< orphan*/  DSGL_SGE_MAXLEN ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ MAX_AAD_LEN ; 
 scalar_t__ MAX_REQUEST_SIZE ; 
 int MAX_RX_PHYS_DSGL_SGE ; 
 int /*<<< orphan*/  SCMD_PROTO_VERSION_GENERIC ; 
 scalar_t__ SGE_MAX_WR_LEN ; 
 scalar_t__ V_CPL_TX_SEC_PDU_AADSTART (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_AADSTOP (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_ACKFOLLOWS (int /*<<< orphan*/ ) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_AUTHINSERT (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_AUTHSTART (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_AUTHSTOP (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_CIPHERSTART (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_CIPHERSTOP_HI (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_CIPHERSTOP_LO (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_CPLLEN (int) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_IVINSRTOFST (int) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_OPCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_PLACEHOLDER (int /*<<< orphan*/ ) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_RXCHID (int /*<<< orphan*/ ) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_ULPTXLPBK (int) ; 
 scalar_t__ V_SCMD_AADIVDROP (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_AUTH_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_CIPH_AUTH_SEQ_CTRL (int) ; 
 scalar_t__ V_SCMD_CIPH_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_ENC_DEC_CTRL (scalar_t__) ; 
 scalar_t__ V_SCMD_HDR_LEN (int) ; 
 scalar_t__ V_SCMD_HMAC_CTRL (scalar_t__) ; 
 scalar_t__ V_SCMD_IV_GEN_CTRL (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_IV_SIZE (int) ; 
 scalar_t__ V_SCMD_LAST_FRAG (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_MAC_ONLY (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_MORE_FRAGS (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_NUM_IVS (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_PROTO_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_SEQ_NO_CTRL (int /*<<< orphan*/ ) ; 
 struct wrqe* alloc_wrqe (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc4rand (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int ccr_count_sgl (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ccr_hmac_ctrl (scalar_t__,scalar_t__) ; 
 int ccr_phys_dsgl_len (int) ; 
 int /*<<< orphan*/  ccr_populate_wreq (struct ccr_softc*,struct chcr_wr*,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__,struct cryptop*) ; 
 int ccr_ulptx_sgl_len (int) ; 
 scalar_t__ ccr_use_imm_data (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ccr_write_phys_dsgl (struct ccr_softc*,char*,int) ; 
 int /*<<< orphan*/  ccr_write_ulptx_sgl (struct ccr_softc*,char*,int) ; 
 int /*<<< orphan*/  crypto_copyback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  crypto_copydata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*) ; 
 void* htobe32 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct chcr_wr*,int /*<<< orphan*/ ,scalar_t__) ; 
 int roundup2 (scalar_t__,int) ; 
 int sglist_append_sglist (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sglist_reset (TYPE_5__*) ; 
 int /*<<< orphan*/  t4_wrq_tx (int /*<<< orphan*/ ,struct wrqe*) ; 
 struct chcr_wr* wrtod (struct wrqe*) ; 

__attribute__((used)) static int
ccr_authenc(struct ccr_softc *sc, struct ccr_session *s, struct cryptop *crp,
    struct cryptodesc *crda, struct cryptodesc *crde)
{
	char iv[CHCR_MAX_CRYPTO_IV_LEN];
	struct chcr_wr *crwr;
	struct wrqe *wr;
	struct auth_hash *axf;
	char *dst;
	u_int kctx_len, key_half, op_type, transhdr_len, wr_len;
	u_int hash_size_in_response, imm_len, iopad_size;
	u_int aad_start, aad_len, aad_stop;
	u_int auth_start, auth_stop, auth_insert;
	u_int cipher_start, cipher_stop;
	u_int hmac_ctrl, input_len;
	int dsgl_nsegs, dsgl_len;
	int sgl_nsegs, sgl_len;
	int error;

	/*
	 * If there is a need in the future, requests with an empty
	 * payload could be supported as HMAC-only requests.
	 */
	if (s->blkcipher.key_len == 0 || crde->crd_len == 0)
		return (EINVAL);
	if (crde->crd_alg == CRYPTO_AES_CBC &&
	    (crde->crd_len % AES_BLOCK_LEN) != 0)
		return (EINVAL);

	/*
	 * Compute the length of the AAD (data covered by the
	 * authentication descriptor but not the encryption
	 * descriptor).  To simplify the logic, AAD is only permitted
	 * before the cipher/plain text, not after.  This is true of
	 * all currently-generated requests.
	 */
	if (crda->crd_len + crda->crd_skip > crde->crd_len + crde->crd_skip)
		return (EINVAL);
	if (crda->crd_skip < crde->crd_skip) {
		if (crda->crd_skip + crda->crd_len > crde->crd_skip)
			aad_len = (crde->crd_skip - crda->crd_skip);
		else
			aad_len = crda->crd_len;
	} else
		aad_len = 0;
	if (aad_len + s->blkcipher.iv_len > MAX_AAD_LEN)
		return (EINVAL);

	axf = s->hmac.auth_hash;
	hash_size_in_response = s->hmac.hash_len;
	if (crde->crd_flags & CRD_F_ENCRYPT)
		op_type = CHCR_ENCRYPT_OP;
	else
		op_type = CHCR_DECRYPT_OP;

	/*
	 * The output buffer consists of the cipher text followed by
	 * the hash when encrypting.  For decryption it only contains
	 * the plain text.
	 *
	 * Due to a firmware bug, the output buffer must include a
	 * dummy output buffer for the IV and AAD prior to the real
	 * output buffer.
	 */
	if (op_type == CHCR_ENCRYPT_OP) {
		if (s->blkcipher.iv_len + aad_len + crde->crd_len +
		    hash_size_in_response > MAX_REQUEST_SIZE)
			return (EFBIG);
	} else {
		if (s->blkcipher.iv_len + aad_len + crde->crd_len >
		    MAX_REQUEST_SIZE)
			return (EFBIG);
	}
	sglist_reset(sc->sg_dsgl);
	error = sglist_append_sglist(sc->sg_dsgl, sc->sg_iv_aad, 0,
	    s->blkcipher.iv_len + aad_len);
	if (error)
		return (error);
	error = sglist_append_sglist(sc->sg_dsgl, sc->sg_crp, crde->crd_skip,
	    crde->crd_len);
	if (error)
		return (error);
	if (op_type == CHCR_ENCRYPT_OP) {
		error = sglist_append_sglist(sc->sg_dsgl, sc->sg_crp,
		    crda->crd_inject, hash_size_in_response);
		if (error)
			return (error);
	}
	dsgl_nsegs = ccr_count_sgl(sc->sg_dsgl, DSGL_SGE_MAXLEN);
	if (dsgl_nsegs > MAX_RX_PHYS_DSGL_SGE)
		return (EFBIG);
	dsgl_len = ccr_phys_dsgl_len(dsgl_nsegs);

	/* PADs must be 128-bit aligned. */
	iopad_size = roundup2(s->hmac.partial_digest_len, 16);

	/*
	 * The 'key' part of the key context consists of the key followed
	 * by the IPAD and OPAD.
	 */
	kctx_len = roundup2(s->blkcipher.key_len, 16) + iopad_size * 2;
	transhdr_len = CIPHER_TRANSHDR_SIZE(kctx_len, dsgl_len);

	/*
	 * The input buffer consists of the IV, any AAD, and then the
	 * cipher/plain text.  For decryption requests the hash is
	 * appended after the cipher text.
	 *
	 * The IV is always stored at the start of the input buffer
	 * even though it may be duplicated in the payload.  The
	 * crypto engine doesn't work properly if the IV offset points
	 * inside of the AAD region, so a second copy is always
	 * required.
	 */
	input_len = aad_len + crde->crd_len;

	/*
	 * The firmware hangs if sent a request which is a
	 * bit smaller than MAX_REQUEST_SIZE.  In particular, the
	 * firmware appears to require 512 - 16 bytes of spare room
	 * along with the size of the hash even if the hash isn't
	 * included in the input buffer.
	 */
	if (input_len + roundup2(axf->hashsize, 16) + (512 - 16) >
	    MAX_REQUEST_SIZE)
		return (EFBIG);
	if (op_type == CHCR_DECRYPT_OP)
		input_len += hash_size_in_response;
	if (ccr_use_imm_data(transhdr_len, s->blkcipher.iv_len + input_len)) {
		imm_len = input_len;
		sgl_nsegs = 0;
		sgl_len = 0;
	} else {
		imm_len = 0;
		sglist_reset(sc->sg_ulptx);
		if (aad_len != 0) {
			error = sglist_append_sglist(sc->sg_ulptx, sc->sg_crp,
			    crda->crd_skip, aad_len);
			if (error)
				return (error);
		}
		error = sglist_append_sglist(sc->sg_ulptx, sc->sg_crp,
		    crde->crd_skip, crde->crd_len);
		if (error)
			return (error);
		if (op_type == CHCR_DECRYPT_OP) {
			error = sglist_append_sglist(sc->sg_ulptx, sc->sg_crp,
			    crda->crd_inject, hash_size_in_response);
			if (error)
				return (error);
		}
		sgl_nsegs = sc->sg_ulptx->sg_nseg;
		sgl_len = ccr_ulptx_sgl_len(sgl_nsegs);
	}

	/*
	 * Any auth-only data before the cipher region is marked as AAD.
	 * Auth-data that overlaps with the cipher region is placed in
	 * the auth section.
	 */
	if (aad_len != 0) {
		aad_start = s->blkcipher.iv_len + 1;
		aad_stop = aad_start + aad_len - 1;
	} else {
		aad_start = 0;
		aad_stop = 0;
	}
	cipher_start = s->blkcipher.iv_len + aad_len + 1;
	if (op_type == CHCR_DECRYPT_OP)
		cipher_stop = hash_size_in_response;
	else
		cipher_stop = 0;
	if (aad_len == crda->crd_len) {
		auth_start = 0;
		auth_stop = 0;
	} else {
		if (aad_len != 0)
			auth_start = cipher_start;
		else
			auth_start = s->blkcipher.iv_len + crda->crd_skip -
			    crde->crd_skip + 1;
		auth_stop = (crde->crd_skip + crde->crd_len) -
		    (crda->crd_skip + crda->crd_len) + cipher_stop;
	}
	if (op_type == CHCR_DECRYPT_OP)
		auth_insert = hash_size_in_response;
	else
		auth_insert = 0;

	wr_len = roundup2(transhdr_len, 16) + s->blkcipher.iv_len +
	    roundup2(imm_len, 16) + sgl_len;
	if (wr_len > SGE_MAX_WR_LEN)
		return (EFBIG);
	wr = alloc_wrqe(wr_len, sc->txq);
	if (wr == NULL) {
		sc->stats_wr_nomem++;
		return (ENOMEM);
	}
	crwr = wrtod(wr);
	memset(crwr, 0, wr_len);

	/*
	 * Read the existing IV from the request or generate a random
	 * one if none is provided.  Optionally copy the generated IV
	 * into the output buffer if requested.
	 */
	if (op_type == CHCR_ENCRYPT_OP) {
		if (crde->crd_flags & CRD_F_IV_EXPLICIT)
			memcpy(iv, crde->crd_iv, s->blkcipher.iv_len);
		else
			arc4rand(iv, s->blkcipher.iv_len, 0);
		if ((crde->crd_flags & CRD_F_IV_PRESENT) == 0)
			crypto_copyback(crp->crp_flags, crp->crp_buf,
			    crde->crd_inject, s->blkcipher.iv_len, iv);
	} else {
		if (crde->crd_flags & CRD_F_IV_EXPLICIT)
			memcpy(iv, crde->crd_iv, s->blkcipher.iv_len);
		else
			crypto_copydata(crp->crp_flags, crp->crp_buf,
			    crde->crd_inject, s->blkcipher.iv_len, iv);
	}

	ccr_populate_wreq(sc, crwr, kctx_len, wr_len, imm_len, sgl_len,
	    op_type == CHCR_DECRYPT_OP ? hash_size_in_response : 0, crp);

	/* XXX: Hardcodes SGE loopback channel of 0. */
	crwr->sec_cpl.op_ivinsrtofst = htobe32(
	    V_CPL_TX_SEC_PDU_OPCODE(CPL_TX_SEC_PDU) |
	    V_CPL_TX_SEC_PDU_RXCHID(sc->tx_channel_id) |
	    V_CPL_TX_SEC_PDU_ACKFOLLOWS(0) | V_CPL_TX_SEC_PDU_ULPTXLPBK(1) |
	    V_CPL_TX_SEC_PDU_CPLLEN(2) | V_CPL_TX_SEC_PDU_PLACEHOLDER(0) |
	    V_CPL_TX_SEC_PDU_IVINSRTOFST(1));

	crwr->sec_cpl.pldlen = htobe32(s->blkcipher.iv_len + input_len);

	crwr->sec_cpl.aadstart_cipherstop_hi = htobe32(
	    V_CPL_TX_SEC_PDU_AADSTART(aad_start) |
	    V_CPL_TX_SEC_PDU_AADSTOP(aad_stop) |
	    V_CPL_TX_SEC_PDU_CIPHERSTART(cipher_start) |
	    V_CPL_TX_SEC_PDU_CIPHERSTOP_HI(cipher_stop >> 4));
	crwr->sec_cpl.cipherstop_lo_authinsert = htobe32(
	    V_CPL_TX_SEC_PDU_CIPHERSTOP_LO(cipher_stop & 0xf) |
	    V_CPL_TX_SEC_PDU_AUTHSTART(auth_start) |
	    V_CPL_TX_SEC_PDU_AUTHSTOP(auth_stop) |
	    V_CPL_TX_SEC_PDU_AUTHINSERT(auth_insert));

	/* These two flits are actually a CPL_TLS_TX_SCMD_FMT. */
	hmac_ctrl = ccr_hmac_ctrl(axf->hashsize, hash_size_in_response);
	crwr->sec_cpl.seqno_numivs = htobe32(
	    V_SCMD_SEQ_NO_CTRL(0) |
	    V_SCMD_PROTO_VERSION(SCMD_PROTO_VERSION_GENERIC) |
	    V_SCMD_ENC_DEC_CTRL(op_type) |
	    V_SCMD_CIPH_AUTH_SEQ_CTRL(op_type == CHCR_ENCRYPT_OP ? 1 : 0) |
	    V_SCMD_CIPH_MODE(s->blkcipher.cipher_mode) |
	    V_SCMD_AUTH_MODE(s->hmac.auth_mode) |
	    V_SCMD_HMAC_CTRL(hmac_ctrl) |
	    V_SCMD_IV_SIZE(s->blkcipher.iv_len / 2) |
	    V_SCMD_NUM_IVS(0));
	crwr->sec_cpl.ivgen_hdrlen = htobe32(
	    V_SCMD_IV_GEN_CTRL(0) |
	    V_SCMD_MORE_FRAGS(0) | V_SCMD_LAST_FRAG(0) | V_SCMD_MAC_ONLY(0) |
	    V_SCMD_AADIVDROP(0) | V_SCMD_HDR_LEN(dsgl_len));

	crwr->key_ctx.ctx_hdr = s->blkcipher.key_ctx_hdr;
	switch (crde->crd_alg) {
	case CRYPTO_AES_CBC:
		if (crde->crd_flags & CRD_F_ENCRYPT)
			memcpy(crwr->key_ctx.key, s->blkcipher.enckey,
			    s->blkcipher.key_len);
		else
			memcpy(crwr->key_ctx.key, s->blkcipher.deckey,
			    s->blkcipher.key_len);
		break;
	case CRYPTO_AES_ICM:
		memcpy(crwr->key_ctx.key, s->blkcipher.enckey,
		    s->blkcipher.key_len);
		break;
	case CRYPTO_AES_XTS:
		key_half = s->blkcipher.key_len / 2;
		memcpy(crwr->key_ctx.key, s->blkcipher.enckey + key_half,
		    key_half);
		if (crde->crd_flags & CRD_F_ENCRYPT)
			memcpy(crwr->key_ctx.key + key_half,
			    s->blkcipher.enckey, key_half);
		else
			memcpy(crwr->key_ctx.key + key_half,
			    s->blkcipher.deckey, key_half);
		break;
	}

	dst = crwr->key_ctx.key + roundup2(s->blkcipher.key_len, 16);
	memcpy(dst, s->hmac.pads, iopad_size * 2);

	dst = (char *)(crwr + 1) + kctx_len;
	ccr_write_phys_dsgl(sc, dst, dsgl_nsegs);
	dst += sizeof(struct cpl_rx_phys_dsgl) + dsgl_len;
	memcpy(dst, iv, s->blkcipher.iv_len);
	dst += s->blkcipher.iv_len;
	if (imm_len != 0) {
		if (aad_len != 0) {
			crypto_copydata(crp->crp_flags, crp->crp_buf,
			    crda->crd_skip, aad_len, dst);
			dst += aad_len;
		}
		crypto_copydata(crp->crp_flags, crp->crp_buf, crde->crd_skip,
		    crde->crd_len, dst);
		dst += crde->crd_len;
		if (op_type == CHCR_DECRYPT_OP)
			crypto_copydata(crp->crp_flags, crp->crp_buf,
			    crda->crd_inject, hash_size_in_response, dst);
	} else
		ccr_write_ulptx_sgl(sc, dst, sgl_nsegs);

	/* XXX: TODO backpressure */
	t4_wrq_tx(sc->adapter, wr);

	return (0);
}