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
typedef  char uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {char* dma_vaddr; scalar_t__ dma_paddr; } ;
struct glxsb_softc {TYPE_1__ sc_dma; } ;
struct glxsb_session {char* ses_iv; int /*<<< orphan*/  ses_key; } ;
struct cryptop {int /*<<< orphan*/  crp_buf; int /*<<< orphan*/  crp_flags; } ;
struct cryptodesc {int crd_len; int crd_flags; char* crd_iv; scalar_t__ crd_skip; scalar_t__ crd_inject; } ;
typedef  int /*<<< orphan*/  op_iv ;

/* Variables and functions */
 int CRD_F_ENCRYPT ; 
 int CRD_F_IV_EXPLICIT ; 
 int CRD_F_IV_PRESENT ; 
 int EINVAL ; 
 int GLXSB_MAX_AES_LEN ; 
 int SB_AES_BLOCK_SIZE ; 
 scalar_t__ SB_CTL_DEC ; 
 scalar_t__ SB_CTL_ENC ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  crypto_copyback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,char*) ; 
 int /*<<< orphan*/  crypto_copydata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,char*) ; 
 int glxsb_aes (struct glxsb_softc*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  glxsb_dma_post_op (struct glxsb_softc*,TYPE_1__*) ; 
 int /*<<< orphan*/  glxsb_dma_pre_op (struct glxsb_softc*,TYPE_1__*) ; 

__attribute__((used)) static int
glxsb_crypto_encdec(struct cryptop *crp, struct cryptodesc *crd,
    struct glxsb_session *ses, struct glxsb_softc *sc)
{
	char *op_src, *op_dst;
	uint32_t op_psrc, op_pdst;
	uint8_t op_iv[SB_AES_BLOCK_SIZE], *piv;
	int error;
	int len, tlen, xlen;
	int offset;
	uint32_t control;

	if (crd == NULL || (crd->crd_len % SB_AES_BLOCK_SIZE) != 0)
		return (EINVAL);

	/* How much of our buffer will we need to use? */
	xlen = crd->crd_len > GLXSB_MAX_AES_LEN ?
	    GLXSB_MAX_AES_LEN : crd->crd_len;

	/*
	 * XXX Check if we can have input == output on Geode LX.
	 * XXX In the meantime, use two separate (adjacent) buffers.
	 */
	op_src = sc->sc_dma.dma_vaddr;
	op_dst = (char *)sc->sc_dma.dma_vaddr + xlen;

	op_psrc = sc->sc_dma.dma_paddr;
	op_pdst = sc->sc_dma.dma_paddr + xlen;

	if (crd->crd_flags & CRD_F_ENCRYPT) {
		control = SB_CTL_ENC;
		if (crd->crd_flags & CRD_F_IV_EXPLICIT)
			bcopy(crd->crd_iv, op_iv, sizeof(op_iv));
		else
			bcopy(ses->ses_iv, op_iv, sizeof(op_iv));

		if ((crd->crd_flags & CRD_F_IV_PRESENT) == 0) {
			crypto_copyback(crp->crp_flags, crp->crp_buf,
			    crd->crd_inject, sizeof(op_iv), op_iv);
		}
	} else {
		control = SB_CTL_DEC;
		if (crd->crd_flags & CRD_F_IV_EXPLICIT)
			bcopy(crd->crd_iv, op_iv, sizeof(op_iv));
		else {
			crypto_copydata(crp->crp_flags, crp->crp_buf,
			    crd->crd_inject, sizeof(op_iv), op_iv);
		}
	}

	offset = 0;
	tlen = crd->crd_len;
	piv = op_iv;

	/* Process the data in GLXSB_MAX_AES_LEN chunks */
	while (tlen > 0) {
		len = (tlen > GLXSB_MAX_AES_LEN) ? GLXSB_MAX_AES_LEN : tlen;
		crypto_copydata(crp->crp_flags, crp->crp_buf,
		    crd->crd_skip + offset, len, op_src);

		glxsb_dma_pre_op(sc, &sc->sc_dma);

		error = glxsb_aes(sc, control, op_psrc, op_pdst, ses->ses_key,
		    len, op_iv);

		glxsb_dma_post_op(sc, &sc->sc_dma);
		if (error != 0)
			return (error);

		crypto_copyback(crp->crp_flags, crp->crp_buf,
		    crd->crd_skip + offset, len, op_dst);

		offset += len;
		tlen -= len;

		if (tlen <= 0) {	/* Ideally, just == 0 */
			/* Finished - put the IV in session IV */
			piv = ses->ses_iv;
		}

		/*
		 * Copy out last block for use as next iteration/session IV.
		 *
		 * piv is set to op_iv[] before the loop starts, but is
		 * set to ses->ses_iv if we're going to exit the loop this
		 * time.
		 */
		if (crd->crd_flags & CRD_F_ENCRYPT)
			bcopy(op_dst + len - sizeof(op_iv), piv, sizeof(op_iv));
		else {
			/* Decryption, only need this if another iteration */
			if (tlen > 0) {
				bcopy(op_src + len - sizeof(op_iv), piv,
				    sizeof(op_iv));
			}
		}
	} /* while */

	/* All AES processing has now been done. */
	bzero(sc->sc_dma.dma_vaddr, xlen * 2);

	return (0);
}