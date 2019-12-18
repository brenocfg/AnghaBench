#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct fpu_kern_ctx {int dummy; } ;
struct cryptop {int /*<<< orphan*/  crp_buf; int /*<<< orphan*/  crp_flags; } ;
struct cryptodesc {int crd_flags; int crd_alg; int crd_len; int /*<<< orphan*/  crd_skip; int /*<<< orphan*/  crd_inject; int /*<<< orphan*/  crd_iv; } ;
struct armv8_crypto_session {int algo; int /*<<< orphan*/  dec_schedule; int /*<<< orphan*/  rounds; int /*<<< orphan*/  enc_schedule; } ;

/* Variables and functions */
 int AES_BLOCK_LEN ; 
 int /*<<< orphan*/  AQUIRE_CTX (int,struct fpu_kern_ctx*) ; 
 int CRD_F_ENCRYPT ; 
 int CRD_F_IV_EXPLICIT ; 
 int CRD_F_IV_PRESENT ; 
 int CRD_F_KEY_EXPLICIT ; 
#define  CRYPTO_AES_CBC 128 
 int ENOMEM ; 
 int FPU_KERN_KTHR ; 
 int FPU_KERN_NORMAL ; 
 int /*<<< orphan*/  M_ARMV8_CRYPTO ; 
 int /*<<< orphan*/  RELEASE_CTX (int,struct fpu_kern_ctx*) ; 
 int /*<<< orphan*/  arc4rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armv8_aes_decrypt_cbc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  armv8_aes_encrypt_cbc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * armv8_crypto_cipher_alloc (struct cryptodesc*,struct cryptop*,int*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_copyback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_copydata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fpu_kern_enter (int /*<<< orphan*/ ,struct fpu_kern_ctx*,int) ; 
 int /*<<< orphan*/  fpu_kern_leave (int /*<<< orphan*/ ,struct fpu_kern_ctx*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int is_fpu_kern_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
armv8_crypto_cipher_process(struct armv8_crypto_session *ses,
    struct cryptodesc *enccrd, struct cryptop *crp)
{
	struct fpu_kern_ctx *ctx;
	uint8_t *buf;
	uint8_t iv[AES_BLOCK_LEN];
	int allocated, i;
	int encflag, ivlen;
	int kt;

	encflag = (enccrd->crd_flags & CRD_F_ENCRYPT) == CRD_F_ENCRYPT;

	buf = armv8_crypto_cipher_alloc(enccrd, crp, &allocated);
	if (buf == NULL)
		return (ENOMEM);

	kt = is_fpu_kern_thread(0);
	if (!kt) {
		AQUIRE_CTX(i, ctx);
		fpu_kern_enter(curthread, ctx,
		    FPU_KERN_NORMAL | FPU_KERN_KTHR);
	}

	if ((enccrd->crd_flags & CRD_F_KEY_EXPLICIT) != 0) {
		panic("CRD_F_KEY_EXPLICIT");
	}

	switch (enccrd->crd_alg) {
	case CRYPTO_AES_CBC:
		ivlen = AES_BLOCK_LEN;
		break;
	}

	/* Setup iv */
	if (encflag) {
		if ((enccrd->crd_flags & CRD_F_IV_EXPLICIT) != 0)
			bcopy(enccrd->crd_iv, iv, ivlen);
		else
			arc4rand(iv, ivlen, 0);

		if ((enccrd->crd_flags & CRD_F_IV_PRESENT) == 0)
			crypto_copyback(crp->crp_flags, crp->crp_buf,
			    enccrd->crd_inject, ivlen, iv);
	} else {
		if ((enccrd->crd_flags & CRD_F_IV_EXPLICIT) != 0)
			bcopy(enccrd->crd_iv, iv, ivlen);
		else
			crypto_copydata(crp->crp_flags, crp->crp_buf,
			    enccrd->crd_inject, ivlen, iv);
	}

	/* Do work */
	switch (ses->algo) {
	case CRYPTO_AES_CBC:
		if (encflag)
			armv8_aes_encrypt_cbc(ses->rounds, ses->enc_schedule,
			    enccrd->crd_len, buf, buf, iv);
		else
			armv8_aes_decrypt_cbc(ses->rounds, ses->dec_schedule,
			    enccrd->crd_len, buf, iv);
		break;
	}

	if (allocated)
		crypto_copyback(crp->crp_flags, crp->crp_buf, enccrd->crd_skip,
		    enccrd->crd_len, buf);

	if (!kt) {
		fpu_kern_leave(curthread, ctx);
		RELEASE_CTX(i, ctx);
	}
	if (allocated) {
		bzero(buf, enccrd->crd_len);
		free(buf, M_ARMV8_CRYPTO);
	}
	return (0);
}