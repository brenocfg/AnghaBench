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
typedef  void* uint32_t ;
typedef  scalar_t__ u_int ;
struct wrqe {int dummy; } ;
struct cryptop {int /*<<< orphan*/  crp_buf; int /*<<< orphan*/  crp_flags; } ;
struct cryptodesc {scalar_t__ crd_len; scalar_t__ crd_skip; int crd_flags; scalar_t__ crd_inject; char* crd_iv; } ;
struct cpl_rx_phys_dsgl {int dummy; } ;
struct TYPE_9__ {char* key; int /*<<< orphan*/  ctx_hdr; } ;
struct TYPE_8__ {void* ivgen_hdrlen; void* seqno_numivs; void* cipherstop_lo_authinsert; void* aadstart_cipherstop_hi; void* pldlen; void* op_ivinsrtofst; } ;
struct chcr_wr {TYPE_2__ key_ctx; TYPE_1__ sec_cpl; } ;
struct ccr_softc {int /*<<< orphan*/  adapter; int /*<<< orphan*/  tx_channel_id; int /*<<< orphan*/  stats_wr_nomem; int /*<<< orphan*/  txq; TYPE_5__* sg_ulptx; int /*<<< orphan*/  sg_crp; TYPE_5__* sg_dsgl; int /*<<< orphan*/  sg_iv_aad; } ;
struct TYPE_10__ {scalar_t__ hash_len; char* ghash_h; } ;
struct TYPE_11__ {scalar_t__ key_len; int iv_len; char* enckey; int /*<<< orphan*/  key_ctx_hdr; } ;
struct ccr_session {TYPE_3__ gmac; TYPE_4__ blkcipher; } ;
struct TYPE_12__ {int sg_nseg; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_LEN ; 
 int /*<<< orphan*/  AES_GMAC_HASH_LEN ; 
 scalar_t__ CHCR_DECRYPT_OP ; 
 scalar_t__ CHCR_ENCRYPT_OP ; 
 int CHCR_MAX_CRYPTO_IV_LEN ; 
 scalar_t__ CIPHER_TRANSHDR_SIZE (scalar_t__,int) ; 
 int /*<<< orphan*/  CPL_TX_SEC_PDU ; 
 int CRD_F_ENCRYPT ; 
 int CRD_F_IV_EXPLICIT ; 
 int CRD_F_IV_PRESENT ; 
 int /*<<< orphan*/  DSGL_SGE_MAXLEN ; 
 int EFBIG ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 scalar_t__ GMAC_BLOCK_LEN ; 
 scalar_t__ MAX_AAD_LEN ; 
 scalar_t__ MAX_REQUEST_SIZE ; 
 int MAX_RX_PHYS_DSGL_SGE ; 
 int /*<<< orphan*/  SCMD_AUTH_MODE_GHASH ; 
 int /*<<< orphan*/  SCMD_CIPH_MODE_AES_GCM ; 
 int /*<<< orphan*/  SCMD_PROTO_VERSION_GENERIC ; 
 scalar_t__ SGE_MAX_WR_LEN ; 
 scalar_t__ V_CPL_TX_SEC_PDU_AADSTART (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_AADSTOP (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_ACKFOLLOWS (int /*<<< orphan*/ ) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_AUTHINSERT (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_AUTHSTART (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_AUTHSTOP (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_CIPHERSTART (scalar_t__) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_CIPHERSTOP_HI (int /*<<< orphan*/ ) ; 
 scalar_t__ V_CPL_TX_SEC_PDU_CIPHERSTOP_LO (int /*<<< orphan*/ ) ; 
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
 scalar_t__ V_SCMD_IV_SIZE (scalar_t__) ; 
 scalar_t__ V_SCMD_LAST_FRAG (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_MAC_ONLY (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_MORE_FRAGS (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_NUM_IVS (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_PROTO_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ V_SCMD_SEQ_NO_CTRL (int /*<<< orphan*/ ) ; 
 struct wrqe* alloc_wrqe (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc4rand (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int ccr_count_sgl (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ccr_hmac_ctrl (int /*<<< orphan*/ ,scalar_t__) ; 
 int ccr_phys_dsgl_len (int) ; 
 int /*<<< orphan*/  ccr_populate_wreq (struct ccr_softc*,struct chcr_wr*,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,struct cryptop*) ; 
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
ccr_gcm(struct ccr_softc *sc, struct ccr_session *s, struct cryptop *crp,
    struct cryptodesc *crda, struct cryptodesc *crde)
{
	char iv[CHCR_MAX_CRYPTO_IV_LEN];
	struct chcr_wr *crwr;
	struct wrqe *wr;
	char *dst;
	u_int iv_len, kctx_len, op_type, transhdr_len, wr_len;
	u_int hash_size_in_response, imm_len;
	u_int aad_start, aad_stop, cipher_start, cipher_stop, auth_insert;
	u_int hmac_ctrl, input_len;
	int dsgl_nsegs, dsgl_len;
	int sgl_nsegs, sgl_len;
	int error;

	if (s->blkcipher.key_len == 0)
		return (EINVAL);

	/*
	 * The crypto engine doesn't handle GCM requests with an empty
	 * payload, so handle those in software instead.
	 */
	if (crde->crd_len == 0)
		return (EMSGSIZE);

	/*
	 * AAD is only permitted before the cipher/plain text, not
	 * after.
	 */
	if (crda->crd_len + crda->crd_skip > crde->crd_len + crde->crd_skip)
		return (EMSGSIZE);

	if (crda->crd_len + AES_BLOCK_LEN > MAX_AAD_LEN)
		return (EMSGSIZE);

	hash_size_in_response = s->gmac.hash_len;
	if (crde->crd_flags & CRD_F_ENCRYPT)
		op_type = CHCR_ENCRYPT_OP;
	else
		op_type = CHCR_DECRYPT_OP;

	/*
	 * The IV handling for GCM in OCF is a bit more complicated in
	 * that IPSec provides a full 16-byte IV (including the
	 * counter), whereas the /dev/crypto interface sometimes
	 * provides a full 16-byte IV (if no IV is provided in the
	 * ioctl) and sometimes a 12-byte IV (if the IV was explicit).
	 *
	 * When provided a 12-byte IV, assume the IV is really 16 bytes
	 * with a counter in the last 4 bytes initialized to 1.
	 *
	 * While iv_len is checked below, the value is currently
	 * always set to 12 when creating a GCM session in this driver
	 * due to limitations in OCF (there is no way to know what the
	 * IV length of a given request will be).  This means that the
	 * driver always assumes as 12-byte IV for now.
	 */
	if (s->blkcipher.iv_len == 12)
		iv_len = AES_BLOCK_LEN;
	else
		iv_len = s->blkcipher.iv_len;

	/*
	 * The output buffer consists of the cipher text followed by
	 * the tag when encrypting.  For decryption it only contains
	 * the plain text.
	 *
	 * Due to a firmware bug, the output buffer must include a
	 * dummy output buffer for the IV and AAD prior to the real
	 * output buffer.
	 */
	if (op_type == CHCR_ENCRYPT_OP) {
		if (iv_len + crda->crd_len + crde->crd_len +
		    hash_size_in_response > MAX_REQUEST_SIZE)
			return (EFBIG);
	} else {
		if (iv_len + crda->crd_len + crde->crd_len > MAX_REQUEST_SIZE)
			return (EFBIG);
	}
	sglist_reset(sc->sg_dsgl);
	error = sglist_append_sglist(sc->sg_dsgl, sc->sg_iv_aad, 0, iv_len +
	    crda->crd_len);
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

	/*
	 * The 'key' part of the key context consists of the key followed
	 * by the Galois hash key.
	 */
	kctx_len = roundup2(s->blkcipher.key_len, 16) + GMAC_BLOCK_LEN;
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
	input_len = crda->crd_len + crde->crd_len;
	if (op_type == CHCR_DECRYPT_OP)
		input_len += hash_size_in_response;
	if (input_len > MAX_REQUEST_SIZE)
		return (EFBIG);
	if (ccr_use_imm_data(transhdr_len, iv_len + input_len)) {
		imm_len = input_len;
		sgl_nsegs = 0;
		sgl_len = 0;
	} else {
		imm_len = 0;
		sglist_reset(sc->sg_ulptx);
		if (crda->crd_len != 0) {
			error = sglist_append_sglist(sc->sg_ulptx, sc->sg_crp,
			    crda->crd_skip, crda->crd_len);
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

	if (crda->crd_len != 0) {
		aad_start = iv_len + 1;
		aad_stop = aad_start + crda->crd_len - 1;
	} else {
		aad_start = 0;
		aad_stop = 0;
	}
	cipher_start = iv_len + crda->crd_len + 1;
	if (op_type == CHCR_DECRYPT_OP)
		cipher_stop = hash_size_in_response;
	else
		cipher_stop = 0;
	if (op_type == CHCR_DECRYPT_OP)
		auth_insert = hash_size_in_response;
	else
		auth_insert = 0;

	wr_len = roundup2(transhdr_len, 16) + iv_len + roundup2(imm_len, 16) +
	    sgl_len;
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
	 *
	 * If the input IV is 12 bytes, append an explicit 4-byte
	 * counter of 1.
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
	if (s->blkcipher.iv_len == 12)
		*(uint32_t *)&iv[12] = htobe32(1);

	ccr_populate_wreq(sc, crwr, kctx_len, wr_len, imm_len, sgl_len, 0,
	    crp);

	/* XXX: Hardcodes SGE loopback channel of 0. */
	crwr->sec_cpl.op_ivinsrtofst = htobe32(
	    V_CPL_TX_SEC_PDU_OPCODE(CPL_TX_SEC_PDU) |
	    V_CPL_TX_SEC_PDU_RXCHID(sc->tx_channel_id) |
	    V_CPL_TX_SEC_PDU_ACKFOLLOWS(0) | V_CPL_TX_SEC_PDU_ULPTXLPBK(1) |
	    V_CPL_TX_SEC_PDU_CPLLEN(2) | V_CPL_TX_SEC_PDU_PLACEHOLDER(0) |
	    V_CPL_TX_SEC_PDU_IVINSRTOFST(1));

	crwr->sec_cpl.pldlen = htobe32(iv_len + input_len);

	/*
	 * NB: cipherstop is explicitly set to 0.  On encrypt it
	 * should normally be set to 0 anyway (as the encrypt crd ends
	 * at the end of the input).  However, for decrypt the cipher
	 * ends before the tag in the AUTHENC case (and authstop is
	 * set to stop before the tag), but for GCM the cipher still
	 * runs to the end of the buffer.  Not sure if this is
	 * intentional or a firmware quirk, but it is required for
	 * working tag validation with GCM decryption.
	 */
	crwr->sec_cpl.aadstart_cipherstop_hi = htobe32(
	    V_CPL_TX_SEC_PDU_AADSTART(aad_start) |
	    V_CPL_TX_SEC_PDU_AADSTOP(aad_stop) |
	    V_CPL_TX_SEC_PDU_CIPHERSTART(cipher_start) |
	    V_CPL_TX_SEC_PDU_CIPHERSTOP_HI(0));
	crwr->sec_cpl.cipherstop_lo_authinsert = htobe32(
	    V_CPL_TX_SEC_PDU_CIPHERSTOP_LO(0) |
	    V_CPL_TX_SEC_PDU_AUTHSTART(cipher_start) |
	    V_CPL_TX_SEC_PDU_AUTHSTOP(cipher_stop) |
	    V_CPL_TX_SEC_PDU_AUTHINSERT(auth_insert));

	/* These two flits are actually a CPL_TLS_TX_SCMD_FMT. */
	hmac_ctrl = ccr_hmac_ctrl(AES_GMAC_HASH_LEN, hash_size_in_response);
	crwr->sec_cpl.seqno_numivs = htobe32(
	    V_SCMD_SEQ_NO_CTRL(0) |
	    V_SCMD_PROTO_VERSION(SCMD_PROTO_VERSION_GENERIC) |
	    V_SCMD_ENC_DEC_CTRL(op_type) |
	    V_SCMD_CIPH_AUTH_SEQ_CTRL(op_type == CHCR_ENCRYPT_OP ? 1 : 0) |
	    V_SCMD_CIPH_MODE(SCMD_CIPH_MODE_AES_GCM) |
	    V_SCMD_AUTH_MODE(SCMD_AUTH_MODE_GHASH) |
	    V_SCMD_HMAC_CTRL(hmac_ctrl) |
	    V_SCMD_IV_SIZE(iv_len / 2) |
	    V_SCMD_NUM_IVS(0));
	crwr->sec_cpl.ivgen_hdrlen = htobe32(
	    V_SCMD_IV_GEN_CTRL(0) |
	    V_SCMD_MORE_FRAGS(0) | V_SCMD_LAST_FRAG(0) | V_SCMD_MAC_ONLY(0) |
	    V_SCMD_AADIVDROP(0) | V_SCMD_HDR_LEN(dsgl_len));

	crwr->key_ctx.ctx_hdr = s->blkcipher.key_ctx_hdr;
	memcpy(crwr->key_ctx.key, s->blkcipher.enckey, s->blkcipher.key_len);
	dst = crwr->key_ctx.key + roundup2(s->blkcipher.key_len, 16);
	memcpy(dst, s->gmac.ghash_h, GMAC_BLOCK_LEN);

	dst = (char *)(crwr + 1) + kctx_len;
	ccr_write_phys_dsgl(sc, dst, dsgl_nsegs);
	dst += sizeof(struct cpl_rx_phys_dsgl) + dsgl_len;
	memcpy(dst, iv, iv_len);
	dst += iv_len;
	if (imm_len != 0) {
		if (crda->crd_len != 0) {
			crypto_copydata(crp->crp_flags, crp->crp_buf,
			    crda->crd_skip, crda->crd_len, dst);
			dst += crda->crd_len;
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