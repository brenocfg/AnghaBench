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
struct cryptoini {int /*<<< orphan*/  cri_klen; int /*<<< orphan*/  cri_key; int /*<<< orphan*/  cri_mlen; } ;
struct aesni_session {int auth_algo; int /*<<< orphan*/  mlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_CTX (int,struct fpu_kern_ctx*) ; 
#define  CRYPTO_SHA1 133 
#define  CRYPTO_SHA1_HMAC 132 
#define  CRYPTO_SHA2_224 131 
#define  CRYPTO_SHA2_224_HMAC 130 
#define  CRYPTO_SHA2_256 129 
#define  CRYPTO_SHA2_256_HMAC 128 
 int FPU_KERN_KTHR ; 
 int FPU_KERN_NORMAL ; 
 int /*<<< orphan*/  RELEASE_CTX (int,struct fpu_kern_ctx*) ; 
 int aesni_authprepare (struct aesni_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int aesni_cipher_setup_common (struct aesni_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fpu_kern_enter (int /*<<< orphan*/ ,struct fpu_kern_ctx*,int) ; 
 int /*<<< orphan*/  fpu_kern_leave (int /*<<< orphan*/ ,struct fpu_kern_ctx*) ; 
 scalar_t__ is_fpu_kern_thread (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aesni_cipher_setup(struct aesni_session *ses, struct cryptoini *encini,
    struct cryptoini *authini)
{
	struct fpu_kern_ctx *ctx;
	int kt, ctxidx, error;

	switch (ses->auth_algo) {
	case CRYPTO_SHA1:
	case CRYPTO_SHA1_HMAC:
	case CRYPTO_SHA2_224:
	case CRYPTO_SHA2_224_HMAC:
	case CRYPTO_SHA2_256:
	case CRYPTO_SHA2_256_HMAC:
		error = aesni_authprepare(ses, authini->cri_klen,
		    authini->cri_key);
		if (error != 0)
			return (error);
		ses->mlen = authini->cri_mlen;
	}

	kt = is_fpu_kern_thread(0) || (encini == NULL);
	if (!kt) {
		ACQUIRE_CTX(ctxidx, ctx);
		fpu_kern_enter(curthread, ctx,
		    FPU_KERN_NORMAL | FPU_KERN_KTHR);
	}

	error = 0;
	if (encini != NULL)
		error = aesni_cipher_setup_common(ses, encini->cri_key,
		    encini->cri_klen);

	if (!kt) {
		fpu_kern_leave(curthread, ctx);
		RELEASE_CTX(ctxidx, ctx);
	}
	return (error);
}