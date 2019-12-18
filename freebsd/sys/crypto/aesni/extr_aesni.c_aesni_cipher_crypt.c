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
typedef  int /*<<< orphan*/  tag ;
struct cryptop {int /*<<< orphan*/  crp_buf; int /*<<< orphan*/  crp_flags; } ;
struct cryptodesc {int crd_flags; int crd_alg; int crd_len; int /*<<< orphan*/  crd_skip; int /*<<< orphan*/  crd_inject; int /*<<< orphan*/  crd_iv; int /*<<< orphan*/  crd_klen; int /*<<< orphan*/  crd_key; } ;
struct aesni_session {int algo; int /*<<< orphan*/  rounds; int /*<<< orphan*/  enc_schedule; int /*<<< orphan*/  xts_schedule; int /*<<< orphan*/  dec_schedule; } ;

/* Variables and functions */
 int AES_BLOCK_LEN ; 
 int /*<<< orphan*/  AES_CCM_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AES_CCM_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AES_GCM_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AES_GCM_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CRD_F_ENCRYPT ; 
 int CRD_F_IV_EXPLICIT ; 
 int CRD_F_IV_PRESENT ; 
 int CRD_F_KEY_EXPLICIT ; 
#define  CRYPTO_AES_CBC 132 
#define  CRYPTO_AES_CCM_16 131 
#define  CRYPTO_AES_ICM 130 
#define  CRYPTO_AES_NIST_GCM_16 129 
#define  CRYPTO_AES_XTS 128 
 int EBADMSG ; 
 int ENOMEM ; 
 int GMAC_DIGEST_LEN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_AESNI ; 
 int /*<<< orphan*/ * aesni_cipher_alloc (struct cryptodesc*,struct cryptop*,int*) ; 
 int aesni_cipher_setup_common (struct aesni_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aesni_decrypt_cbc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aesni_decrypt_xts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aesni_encrypt_cbc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aesni_encrypt_icm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aesni_encrypt_xts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc4rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_copyback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_copydata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aesni_cipher_crypt(struct aesni_session *ses, struct cryptodesc *enccrd,
	struct cryptodesc *authcrd, struct cryptop *crp)
{
	uint8_t iv[AES_BLOCK_LEN], tag[GMAC_DIGEST_LEN], *buf, *authbuf;
	int error, ivlen;
	bool encflag, allocated, authallocated;

	KASSERT((ses->algo != CRYPTO_AES_NIST_GCM_16 &&
		ses->algo != CRYPTO_AES_CCM_16) || authcrd != NULL,
	    ("AES_NIST_GCM_16/AES_CCM_16  must include MAC descriptor"));

	ivlen = 0;
	authbuf = NULL;

	buf = aesni_cipher_alloc(enccrd, crp, &allocated);
	if (buf == NULL)
		return (ENOMEM);

	authallocated = false;
	if (ses->algo == CRYPTO_AES_NIST_GCM_16 ||
	    ses->algo == CRYPTO_AES_CCM_16) {
		authbuf = aesni_cipher_alloc(authcrd, crp, &authallocated);
		if (authbuf == NULL) {
			error = ENOMEM;
			goto out;
		}
	}

	error = 0;
	encflag = (enccrd->crd_flags & CRD_F_ENCRYPT) == CRD_F_ENCRYPT;
	if ((enccrd->crd_flags & CRD_F_KEY_EXPLICIT) != 0) {
		error = aesni_cipher_setup_common(ses, enccrd->crd_key,
		    enccrd->crd_klen);
		if (error != 0)
			goto out;
	}

	switch (enccrd->crd_alg) {
	case CRYPTO_AES_CBC:
	case CRYPTO_AES_ICM:
		ivlen = AES_BLOCK_LEN;
		break;
	case CRYPTO_AES_XTS:
		ivlen = 8;
		break;
	case CRYPTO_AES_NIST_GCM_16:
	case CRYPTO_AES_CCM_16:
		ivlen = 12;	/* should support arbitarily larger */
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

	switch (ses->algo) {
	case CRYPTO_AES_CBC:
		if (encflag)
			aesni_encrypt_cbc(ses->rounds, ses->enc_schedule,
			    enccrd->crd_len, buf, buf, iv);
		else
			aesni_decrypt_cbc(ses->rounds, ses->dec_schedule,
			    enccrd->crd_len, buf, iv);
		break;
	case CRYPTO_AES_ICM:
		/* encryption & decryption are the same */
		aesni_encrypt_icm(ses->rounds, ses->enc_schedule,
		    enccrd->crd_len, buf, buf, iv);
		break;
	case CRYPTO_AES_XTS:
		if (encflag)
			aesni_encrypt_xts(ses->rounds, ses->enc_schedule,
			    ses->xts_schedule, enccrd->crd_len, buf, buf,
			    iv);
		else
			aesni_decrypt_xts(ses->rounds, ses->dec_schedule,
			    ses->xts_schedule, enccrd->crd_len, buf, buf,
			    iv);
		break;
	case CRYPTO_AES_NIST_GCM_16:
		if (!encflag)
			crypto_copydata(crp->crp_flags, crp->crp_buf,
			    authcrd->crd_inject, sizeof(tag), tag);
		else
			bzero(tag, sizeof tag);

		if (encflag) {
			AES_GCM_encrypt(buf, buf, authbuf, iv, tag,
			    enccrd->crd_len, authcrd->crd_len, ivlen,
			    ses->enc_schedule, ses->rounds);

			if (authcrd != NULL)
				crypto_copyback(crp->crp_flags, crp->crp_buf,
				    authcrd->crd_inject, sizeof(tag), tag);
		} else {
			if (!AES_GCM_decrypt(buf, buf, authbuf, iv, tag,
			    enccrd->crd_len, authcrd->crd_len, ivlen,
			    ses->enc_schedule, ses->rounds))
				error = EBADMSG;
		}
		break;
	case CRYPTO_AES_CCM_16:
		if (!encflag)
			crypto_copydata(crp->crp_flags, crp->crp_buf,
			    authcrd->crd_inject, sizeof(tag), tag);
		else
			bzero(tag, sizeof tag);
		if (encflag) {
			AES_CCM_encrypt(buf, buf, authbuf, iv, tag,
			    enccrd->crd_len, authcrd->crd_len, ivlen,
			    ses->enc_schedule, ses->rounds);
			if (authcrd != NULL)
				crypto_copyback(crp->crp_flags, crp->crp_buf,
				    authcrd->crd_inject, sizeof(tag), tag);
		} else {
			if (!AES_CCM_decrypt(buf, buf, authbuf, iv, tag,
			    enccrd->crd_len, authcrd->crd_len, ivlen,
			    ses->enc_schedule, ses->rounds))
				error = EBADMSG;
		}
		break;
	}
	if (allocated && error == 0)
		crypto_copyback(crp->crp_flags, crp->crp_buf, enccrd->crd_skip,
		    enccrd->crd_len, buf);

out:
	if (allocated) {
		explicit_bzero(buf, enccrd->crd_len);
		free(buf, M_AESNI);
	}
	if (authallocated) {
		explicit_bzero(authbuf, authcrd->crd_len);
		free(authbuf, M_AESNI);
	}
	return (error);
}