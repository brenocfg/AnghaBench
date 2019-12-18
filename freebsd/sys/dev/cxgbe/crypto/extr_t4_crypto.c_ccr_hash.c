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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ u_int ;
struct wrqe {int dummy; } ;
struct cryptop {int /*<<< orphan*/  crp_buf; int /*<<< orphan*/  crp_flags; struct cryptodesc* crp_desc; } ;
struct cryptodesc {scalar_t__ crd_len; int /*<<< orphan*/  crd_skip; } ;
struct TYPE_7__ {void* ctx_hdr; int /*<<< orphan*/  key; } ;
struct TYPE_6__ {void* ivgen_hdrlen; void* seqno_numivs; void* cipherstop_lo_authinsert; void* pldlen; void* op_ivinsrtofst; } ;
struct chcr_wr {TYPE_2__ key_ctx; TYPE_1__ sec_cpl; } ;
struct ccr_softc {int /*<<< orphan*/  adapter; int /*<<< orphan*/  tx_channel_id; int /*<<< orphan*/  stats_wr_nomem; int /*<<< orphan*/  txq; TYPE_4__* sg_ulptx; int /*<<< orphan*/  sg_crp; } ;
struct TYPE_8__ {scalar_t__ partial_digest_len; int /*<<< orphan*/  mk_size; int /*<<< orphan*/  pads; int /*<<< orphan*/  auth_mode; struct auth_hash* auth_hash; } ;
struct ccr_session {scalar_t__ mode; TYPE_3__ hmac; } ;
struct auth_hash {scalar_t__ hashsize; scalar_t__ blocksize; } ;
struct _key_ctx {int dummy; } ;
struct TYPE_9__ {int sg_nseg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHCR_KEYCTX_NO_KEY ; 
 int /*<<< orphan*/  CPL_TX_SEC_PDU ; 
 int DUMMY_BYTES ; 
 int EFBIG ; 
 int ENOMEM ; 
 scalar_t__ HASH_TRANSHDR_SIZE (scalar_t__) ; 
 scalar_t__ HMAC ; 
 scalar_t__ MAX_REQUEST_SIZE ; 
 int /*<<< orphan*/  SCMD_CIPH_MODE_NOP ; 
 scalar_t__ SCMD_HMAC_CTRL_NOP ; 
 scalar_t__ SCMD_HMAC_CTRL_NO_TRUNC ; 
 int /*<<< orphan*/  SCMD_PROTO_VERSION_GENERIC ; 
 scalar_t__ SGE_MAX_WR_LEN ; 
 int V_CPL_TX_SEC_PDU_ACKFOLLOWS (int /*<<< orphan*/ ) ; 
 int V_CPL_TX_SEC_PDU_AUTHSTART (int) ; 
 int V_CPL_TX_SEC_PDU_AUTHSTOP (int /*<<< orphan*/ ) ; 
 int V_CPL_TX_SEC_PDU_CPLLEN (int) ; 
 int V_CPL_TX_SEC_PDU_IVINSRTOFST (int /*<<< orphan*/ ) ; 
 int V_CPL_TX_SEC_PDU_OPCODE (int /*<<< orphan*/ ) ; 
 int V_CPL_TX_SEC_PDU_PLACEHOLDER (int /*<<< orphan*/ ) ; 
 int V_CPL_TX_SEC_PDU_RXCHID (int /*<<< orphan*/ ) ; 
 int V_CPL_TX_SEC_PDU_ULPTXLPBK (int) ; 
 int V_KEY_CONTEXT_CK_SIZE (int /*<<< orphan*/ ) ; 
 int V_KEY_CONTEXT_CTX_LEN (scalar_t__) ; 
 int V_KEY_CONTEXT_MK_SIZE (int /*<<< orphan*/ ) ; 
 int V_KEY_CONTEXT_OPAD_PRESENT (int) ; 
 int V_KEY_CONTEXT_SALT_PRESENT (int) ; 
 int V_KEY_CONTEXT_VALID (int) ; 
 int V_SCMD_AUTH_MODE (int /*<<< orphan*/ ) ; 
 int V_SCMD_CIPH_MODE (int /*<<< orphan*/ ) ; 
 int V_SCMD_HMAC_CTRL (scalar_t__) ; 
 int V_SCMD_LAST_FRAG (int /*<<< orphan*/ ) ; 
 int V_SCMD_MAC_ONLY (int) ; 
 int V_SCMD_MORE_FRAGS (int) ; 
 int V_SCMD_PROTO_VERSION (int /*<<< orphan*/ ) ; 
 int V_SCMD_SEQ_NO_CTRL (int /*<<< orphan*/ ) ; 
 struct wrqe* alloc_wrqe (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccr_populate_wreq (struct ccr_softc*,struct chcr_wr*,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__,struct cryptop*) ; 
 int ccr_ulptx_sgl_len (int) ; 
 scalar_t__ ccr_use_imm_data (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ccr_write_ulptx_sgl (struct ccr_softc*,char*,int) ; 
 int /*<<< orphan*/  crypto_copydata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 void* htobe32 (int) ; 
 int /*<<< orphan*/  htobe64 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct chcr_wr*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ roundup2 (scalar_t__,int) ; 
 int sglist_append_sglist (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sglist_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  t4_wrq_tx (int /*<<< orphan*/ ,struct wrqe*) ; 
 struct chcr_wr* wrtod (struct wrqe*) ; 

__attribute__((used)) static int
ccr_hash(struct ccr_softc *sc, struct ccr_session *s, struct cryptop *crp)
{
	struct chcr_wr *crwr;
	struct wrqe *wr;
	struct auth_hash *axf;
	struct cryptodesc *crd;
	char *dst;
	u_int hash_size_in_response, kctx_flits, kctx_len, transhdr_len, wr_len;
	u_int hmac_ctrl, imm_len, iopad_size;
	int error, sgl_nsegs, sgl_len, use_opad;

	crd = crp->crp_desc;

	/* Reject requests with too large of an input buffer. */
	if (crd->crd_len > MAX_REQUEST_SIZE)
		return (EFBIG);

	axf = s->hmac.auth_hash;

	if (s->mode == HMAC) {
		use_opad = 1;
		hmac_ctrl = SCMD_HMAC_CTRL_NO_TRUNC;
	} else {
		use_opad = 0;
		hmac_ctrl = SCMD_HMAC_CTRL_NOP;
	}

	/* PADs must be 128-bit aligned. */
	iopad_size = roundup2(s->hmac.partial_digest_len, 16);

	/*
	 * The 'key' part of the context includes the aligned IPAD and
	 * OPAD.
	 */
	kctx_len = iopad_size;
	if (use_opad)
		kctx_len += iopad_size;
	hash_size_in_response = axf->hashsize;
	transhdr_len = HASH_TRANSHDR_SIZE(kctx_len);

	if (crd->crd_len == 0) {
		imm_len = axf->blocksize;
		sgl_nsegs = 0;
		sgl_len = 0;
	} else if (ccr_use_imm_data(transhdr_len, crd->crd_len)) {
		imm_len = crd->crd_len;
		sgl_nsegs = 0;
		sgl_len = 0;
	} else {
		imm_len = 0;
		sglist_reset(sc->sg_ulptx);
		error = sglist_append_sglist(sc->sg_ulptx, sc->sg_crp,
		    crd->crd_skip, crd->crd_len);
		if (error)
			return (error);
		sgl_nsegs = sc->sg_ulptx->sg_nseg;
		sgl_len = ccr_ulptx_sgl_len(sgl_nsegs);
	}

	wr_len = roundup2(transhdr_len, 16) + roundup2(imm_len, 16) + sgl_len;
	if (wr_len > SGE_MAX_WR_LEN)
		return (EFBIG);
	wr = alloc_wrqe(wr_len, sc->txq);
	if (wr == NULL) {
		sc->stats_wr_nomem++;
		return (ENOMEM);
	}
	crwr = wrtod(wr);
	memset(crwr, 0, wr_len);

	ccr_populate_wreq(sc, crwr, kctx_len, wr_len, imm_len, sgl_len,
	    hash_size_in_response, crp);

	/* XXX: Hardcodes SGE loopback channel of 0. */
	crwr->sec_cpl.op_ivinsrtofst = htobe32(
	    V_CPL_TX_SEC_PDU_OPCODE(CPL_TX_SEC_PDU) |
	    V_CPL_TX_SEC_PDU_RXCHID(sc->tx_channel_id) |
	    V_CPL_TX_SEC_PDU_ACKFOLLOWS(0) | V_CPL_TX_SEC_PDU_ULPTXLPBK(1) |
	    V_CPL_TX_SEC_PDU_CPLLEN(2) | V_CPL_TX_SEC_PDU_PLACEHOLDER(0) |
	    V_CPL_TX_SEC_PDU_IVINSRTOFST(0));

	crwr->sec_cpl.pldlen = htobe32(crd->crd_len == 0 ? axf->blocksize :
	    crd->crd_len);

	crwr->sec_cpl.cipherstop_lo_authinsert = htobe32(
	    V_CPL_TX_SEC_PDU_AUTHSTART(1) | V_CPL_TX_SEC_PDU_AUTHSTOP(0));

	/* These two flits are actually a CPL_TLS_TX_SCMD_FMT. */
	crwr->sec_cpl.seqno_numivs = htobe32(
	    V_SCMD_SEQ_NO_CTRL(0) |
	    V_SCMD_PROTO_VERSION(SCMD_PROTO_VERSION_GENERIC) |
	    V_SCMD_CIPH_MODE(SCMD_CIPH_MODE_NOP) |
	    V_SCMD_AUTH_MODE(s->hmac.auth_mode) |
	    V_SCMD_HMAC_CTRL(hmac_ctrl));
	crwr->sec_cpl.ivgen_hdrlen = htobe32(
	    V_SCMD_LAST_FRAG(0) |
	    V_SCMD_MORE_FRAGS(crd->crd_len == 0 ? 1 : 0) | V_SCMD_MAC_ONLY(1));

	memcpy(crwr->key_ctx.key, s->hmac.pads, kctx_len);

	/* XXX: F_KEY_CONTEXT_SALT_PRESENT set, but 'salt' not set. */
	kctx_flits = (sizeof(struct _key_ctx) + kctx_len) / 16;
	crwr->key_ctx.ctx_hdr = htobe32(V_KEY_CONTEXT_CTX_LEN(kctx_flits) |
	    V_KEY_CONTEXT_OPAD_PRESENT(use_opad) |
	    V_KEY_CONTEXT_SALT_PRESENT(1) |
	    V_KEY_CONTEXT_CK_SIZE(CHCR_KEYCTX_NO_KEY) |
	    V_KEY_CONTEXT_MK_SIZE(s->hmac.mk_size) | V_KEY_CONTEXT_VALID(1));

	dst = (char *)(crwr + 1) + kctx_len + DUMMY_BYTES;
	if (crd->crd_len == 0) {
		dst[0] = 0x80;
		if (s->mode == HMAC)
			*(uint64_t *)(dst + axf->blocksize - sizeof(uint64_t)) =
			    htobe64(axf->blocksize << 3);
	} else if (imm_len != 0)
		crypto_copydata(crp->crp_flags, crp->crp_buf, crd->crd_skip,
		    crd->crd_len, dst);
	else
		ccr_write_ulptx_sgl(sc, dst, sgl_nsegs);

	/* XXX: TODO backpressure */
	t4_wrq_tx(sc->adapter, wr);

	return (0);
}