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
struct fpu_kern_ctx {int dummy; } ;
struct cryptop {struct cryptodesc* crp_desc; } ;
struct cryptodesc {scalar_t__ crd_alg; int crd_flags; } ;
struct aesni_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_CTX (int,struct fpu_kern_ctx*) ; 
 int CRD_F_IV_EXPLICIT ; 
 scalar_t__ CRYPTO_AES_CCM_16 ; 
 scalar_t__ CRYPTO_AES_ICM ; 
 scalar_t__ CRYPTO_AES_NIST_GCM_16 ; 
 int EINVAL ; 
 int FPU_KERN_KTHR ; 
 int FPU_KERN_NORMAL ; 
 int /*<<< orphan*/  RELEASE_CTX (int,struct fpu_kern_ctx*) ; 
 int aesni_cipher_crypt (struct aesni_session*,struct cryptodesc*,struct cryptodesc*,struct cryptop*) ; 
 int aesni_cipher_mac (struct aesni_session*,struct cryptodesc*,struct cryptop*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fpu_kern_enter (int /*<<< orphan*/ ,struct fpu_kern_ctx*,int) ; 
 int /*<<< orphan*/  fpu_kern_leave (int /*<<< orphan*/ ,struct fpu_kern_ctx*) ; 
 int is_fpu_kern_thread (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aesni_cipher_process(struct aesni_session *ses, struct cryptodesc *enccrd,
    struct cryptodesc *authcrd, struct cryptop *crp)
{
	struct fpu_kern_ctx *ctx;
	int error, ctxidx;
	bool kt;

	if (enccrd != NULL) {
		if ((enccrd->crd_alg == CRYPTO_AES_ICM ||
		    enccrd->crd_alg == CRYPTO_AES_CCM_16 ||
		    enccrd->crd_alg == CRYPTO_AES_NIST_GCM_16) &&
		    (enccrd->crd_flags & CRD_F_IV_EXPLICIT) == 0)
			return (EINVAL);
	}

	ctx = NULL;
	ctxidx = 0;
	error = 0;
	kt = is_fpu_kern_thread(0);
	if (!kt) {
		ACQUIRE_CTX(ctxidx, ctx);
		fpu_kern_enter(curthread, ctx,
		    FPU_KERN_NORMAL | FPU_KERN_KTHR);
	}

	/* Do work */
	if (enccrd != NULL && authcrd != NULL) {
		/* Perform the first operation */
		if (crp->crp_desc == enccrd)
			error = aesni_cipher_crypt(ses, enccrd, authcrd, crp);
		else
			error = aesni_cipher_mac(ses, authcrd, crp);
		if (error != 0)
			goto out;
		/* Perform the second operation */
		if (crp->crp_desc == enccrd)
			error = aesni_cipher_mac(ses, authcrd, crp);
		else
			error = aesni_cipher_crypt(ses, enccrd, authcrd, crp);
	} else if (enccrd != NULL)
		error = aesni_cipher_crypt(ses, enccrd, authcrd, crp);
	else
		error = aesni_cipher_mac(ses, authcrd, crp);

	if (error != 0)
		goto out;

out:
	if (!kt) {
		fpu_kern_leave(curthread, ctx);
		RELEASE_CTX(ctxidx, ctx);
	}
	return (error);
}