#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct krb5_key_state {void* ks_key; TYPE_1__* ks_class; struct aes_state* ks_priv; } ;
struct cryptoini {int cri_mlen; int /*<<< orphan*/ * cri_next; void* cri_key; int /*<<< orphan*/  cri_klen; int /*<<< orphan*/  cri_alg; } ;
struct aes_state {scalar_t__ as_session_aes; scalar_t__ as_session_sha1; } ;
typedef  int /*<<< orphan*/  cri ;
struct TYPE_2__ {int /*<<< orphan*/  ec_keybits; int /*<<< orphan*/  ec_keylen; } ;

/* Variables and functions */
 int CRYPTOCAP_F_HARDWARE ; 
 int CRYPTOCAP_F_SOFTWARE ; 
 int /*<<< orphan*/  CRYPTO_AES_CBC ; 
 int /*<<< orphan*/  CRYPTO_SHA1_HMAC ; 
 int /*<<< orphan*/  bcopy (void const*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct cryptoini*,int) ; 
 int /*<<< orphan*/  crypto_freesession (scalar_t__) ; 
 int /*<<< orphan*/  crypto_newsession (scalar_t__*,struct cryptoini*,int) ; 

__attribute__((used)) static void
aes_set_key(struct krb5_key_state *ks, const void *in)
{
	void *kp = ks->ks_key;
	struct aes_state *as = ks->ks_priv;
	struct cryptoini cri;

	if (kp != in)
		bcopy(in, kp, ks->ks_class->ec_keylen);

	if (as->as_session_aes != 0)
		crypto_freesession(as->as_session_aes);
	if (as->as_session_sha1 != 0)
		crypto_freesession(as->as_session_sha1);

	/*
	 * We only want the first 96 bits of the HMAC.
	 */
	bzero(&cri, sizeof(cri));
	cri.cri_alg = CRYPTO_SHA1_HMAC;
	cri.cri_klen = ks->ks_class->ec_keybits;
	cri.cri_mlen = 12;
	cri.cri_key = ks->ks_key;
	cri.cri_next = NULL;
	crypto_newsession(&as->as_session_sha1, &cri,
	    CRYPTOCAP_F_HARDWARE | CRYPTOCAP_F_SOFTWARE);

	bzero(&cri, sizeof(cri));
	cri.cri_alg = CRYPTO_AES_CBC;
	cri.cri_klen = ks->ks_class->ec_keybits;
	cri.cri_mlen = 0;
	cri.cri_key = ks->ks_key;
	cri.cri_next = NULL;
	crypto_newsession(&as->as_session_aes, &cri,
	    CRYPTOCAP_F_HARDWARE | CRYPTOCAP_F_SOFTWARE);
}