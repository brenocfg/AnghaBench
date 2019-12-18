#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_aead {int dummy; } ;
struct cpl_tx_sec_pdu {int /*<<< orphan*/  ivgen_hdrlen; int /*<<< orphan*/  seqno_numivs; int /*<<< orphan*/  cipherstop_lo_authinsert; int /*<<< orphan*/  aadstart_cipherstop_hi; int /*<<< orphan*/  pldlen; int /*<<< orphan*/  op_ivinsrtofst; } ;
struct chcr_aead_ctx {int /*<<< orphan*/  hmac_ctrl; } ;
struct aead_request {int assoclen; unsigned char cryptlen; } ;
struct TYPE_3__ {unsigned int tx_chan_id; } ;

/* Variables and functions */
 struct chcr_aead_ctx* AEAD_CTX (TYPE_1__*) ; 
 unsigned int CCM_AAD_FIELD_SIZE ; 
 unsigned int CCM_B0_SIZE ; 
 unsigned short CHCR_DECRYPT_OP ; 
 unsigned short CHCR_ENCRYPT_OP ; 
 unsigned int CHCR_SCMD_AUTH_MODE_CBCMAC ; 
 unsigned int CHCR_SCMD_CIPHER_MODE_AES_CCM ; 
 scalar_t__ CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309 ; 
 int /*<<< orphan*/  FILL_SEC_CPL_AUTHINSERT (int /*<<< orphan*/ ,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_CIPHERSTOP_HI (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_IVGEN_HDRLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_OP_IVINSR (unsigned int,int,int) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_SCMD0_SEQNO (unsigned short,int,unsigned int,unsigned int,int /*<<< orphan*/ ,int) ; 
 int IV ; 
 TYPE_1__* a_ctx (struct crypto_aead*) ; 
 unsigned char crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 scalar_t__ get_aead_subtype (struct crypto_aead*) ; 
 int /*<<< orphan*/  htonl (int) ; 

__attribute__((used)) static void fill_sec_cpl_for_aead(struct cpl_tx_sec_pdu *sec_cpl,
				  unsigned int dst_size,
				  struct aead_request *req,
				  unsigned short op_type)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	unsigned int cipher_mode = CHCR_SCMD_CIPHER_MODE_AES_CCM;
	unsigned int mac_mode = CHCR_SCMD_AUTH_MODE_CBCMAC;
	unsigned int c_id = a_ctx(tfm)->tx_chan_id;
	unsigned int ccm_xtra;
	unsigned char tag_offset = 0, auth_offset = 0;
	unsigned int assoclen;

	if (get_aead_subtype(tfm) == CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309)
		assoclen = req->assoclen - 8;
	else
		assoclen = req->assoclen;
	ccm_xtra = CCM_B0_SIZE +
		((assoclen) ? CCM_AAD_FIELD_SIZE : 0);

	auth_offset = req->cryptlen ?
		(req->assoclen + IV + 1 + ccm_xtra) : 0;
	if (op_type == CHCR_DECRYPT_OP) {
		if (crypto_aead_authsize(tfm) != req->cryptlen)
			tag_offset = crypto_aead_authsize(tfm);
		else
			auth_offset = 0;
	}


	sec_cpl->op_ivinsrtofst = FILL_SEC_CPL_OP_IVINSR(c_id,
					 2, 1);
	sec_cpl->pldlen =
		htonl(req->assoclen + IV + req->cryptlen + ccm_xtra);
	/* For CCM there wil be b0 always. So AAD start will be 1 always */
	sec_cpl->aadstart_cipherstop_hi = FILL_SEC_CPL_CIPHERSTOP_HI(
				1 + IV,	IV + assoclen + ccm_xtra,
				req->assoclen + IV + 1 + ccm_xtra, 0);

	sec_cpl->cipherstop_lo_authinsert = FILL_SEC_CPL_AUTHINSERT(0,
					auth_offset, tag_offset,
					(op_type == CHCR_ENCRYPT_OP) ? 0 :
					crypto_aead_authsize(tfm));
	sec_cpl->seqno_numivs =  FILL_SEC_CPL_SCMD0_SEQNO(op_type,
					(op_type == CHCR_ENCRYPT_OP) ? 0 : 1,
					cipher_mode, mac_mode,
					aeadctx->hmac_ctrl, IV >> 1);

	sec_cpl->ivgen_hdrlen = FILL_SEC_CPL_IVGEN_HDRLEN(0, 0, 1, 0,
					0, dst_size);
}