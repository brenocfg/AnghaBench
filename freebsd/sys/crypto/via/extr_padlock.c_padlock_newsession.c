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
struct thread {int dummy; } ;
struct padlock_softc {int dummy; } ;
struct padlock_session {int /*<<< orphan*/  ses_fpu_ctx; } ;
struct cryptoini {int cri_alg; struct cryptoini* cri_next; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;

/* Variables and functions */
#define  CRYPTO_AES_CBC 135 
#define  CRYPTO_MD5_HMAC 134 
#define  CRYPTO_NULL_HMAC 133 
#define  CRYPTO_RIPEMD160_HMAC 132 
#define  CRYPTO_SHA1_HMAC 131 
#define  CRYPTO_SHA2_256_HMAC 130 
#define  CRYPTO_SHA2_384_HMAC 129 
#define  CRYPTO_SHA2_512_HMAC 128 
 int EINVAL ; 
 int FPU_KERN_KTHR ; 
 int FPU_KERN_NORMAL ; 
 struct padlock_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 struct padlock_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpu_kern_alloc_ctx (int) ; 
 int /*<<< orphan*/  fpu_kern_enter (struct thread*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fpu_kern_leave (struct thread*,int /*<<< orphan*/ ) ; 
 int padlock_cipher_setup (struct padlock_session*,struct cryptoini*) ; 
 int /*<<< orphan*/  padlock_freesession_one (struct padlock_softc*,struct padlock_session*) ; 
 int padlock_hash_setup (struct padlock_session*,struct cryptoini*) ; 

__attribute__((used)) static int
padlock_newsession(device_t dev, crypto_session_t cses, struct cryptoini *cri)
{
	struct padlock_softc *sc = device_get_softc(dev);
	struct padlock_session *ses = NULL;
	struct cryptoini *encini, *macini;
	struct thread *td;
	int error;

	if (cri == NULL)
		return (EINVAL);

	encini = macini = NULL;
	for (; cri != NULL; cri = cri->cri_next) {
		switch (cri->cri_alg) {
		case CRYPTO_NULL_HMAC:
		case CRYPTO_MD5_HMAC:
		case CRYPTO_SHA1_HMAC:
		case CRYPTO_RIPEMD160_HMAC:
		case CRYPTO_SHA2_256_HMAC:
		case CRYPTO_SHA2_384_HMAC:
		case CRYPTO_SHA2_512_HMAC:
			if (macini != NULL)
				return (EINVAL);
			macini = cri;
			break;
		case CRYPTO_AES_CBC:
			if (encini != NULL)
				return (EINVAL);
			encini = cri;
			break;
		default:
			return (EINVAL);
		}
	}

	/*
	 * We only support HMAC algorithms to be able to work with
	 * ipsec(4), so if we are asked only for authentication without
	 * encryption, don't pretend we can accellerate it.
	 */
	if (encini == NULL)
		return (EINVAL);

	ses = crypto_get_driver_session(cses);
	ses->ses_fpu_ctx = fpu_kern_alloc_ctx(FPU_KERN_NORMAL);

	error = padlock_cipher_setup(ses, encini);
	if (error != 0) {
		padlock_freesession_one(sc, ses);
		return (error);
	}

	if (macini != NULL) {
		td = curthread;
		fpu_kern_enter(td, ses->ses_fpu_ctx, FPU_KERN_NORMAL |
		    FPU_KERN_KTHR);
		error = padlock_hash_setup(ses, macini);
		fpu_kern_leave(td, ses->ses_fpu_ctx);
		if (error != 0) {
			padlock_freesession_one(sc, ses);
			return (error);
		}
	}

	return (0);
}