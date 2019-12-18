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
struct aesni_session {int algo; void* rounds; int /*<<< orphan*/  xts_schedule; int /*<<< orphan*/  dec_schedule; int /*<<< orphan*/  enc_schedule; } ;

/* Variables and functions */
 void* AES128_ROUNDS ; 
 void* AES192_ROUNDS ; 
 void* AES256_ROUNDS ; 
 int /*<<< orphan*/  CRYPTDEB (char*) ; 
#define  CRYPTO_AES_CBC 132 
#define  CRYPTO_AES_CCM_16 131 
#define  CRYPTO_AES_ICM 130 
#define  CRYPTO_AES_NIST_GCM_16 129 
#define  CRYPTO_AES_XTS 128 
 int EINVAL ; 
 int /*<<< orphan*/  aesni_set_deckey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  aesni_set_enckey (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*) ; 

int
aesni_cipher_setup_common(struct aesni_session *ses, const uint8_t *key,
    int keylen)
{
	int decsched;

	decsched = 1;

	switch (ses->algo) {
	case CRYPTO_AES_ICM:
	case CRYPTO_AES_NIST_GCM_16:
	case CRYPTO_AES_CCM_16:
		decsched = 0;
		/* FALLTHROUGH */
	case CRYPTO_AES_CBC:
		switch (keylen) {
		case 128:
			ses->rounds = AES128_ROUNDS;
			break;
		case 192:
			ses->rounds = AES192_ROUNDS;
			break;
		case 256:
			ses->rounds = AES256_ROUNDS;
			break;
		default:
			CRYPTDEB("invalid CBC/ICM/GCM key length");
			return (EINVAL);
		}
		break;
	case CRYPTO_AES_XTS:
		switch (keylen) {
		case 256:
			ses->rounds = AES128_ROUNDS;
			break;
		case 512:
			ses->rounds = AES256_ROUNDS;
			break;
		default:
			CRYPTDEB("invalid XTS key length");
			return (EINVAL);
		}
		break;
	default:
		return (EINVAL);
	}

	aesni_set_enckey(key, ses->enc_schedule, ses->rounds);
	if (decsched)
		aesni_set_deckey(ses->enc_schedule, ses->dec_schedule,
		    ses->rounds);

	if (ses->algo == CRYPTO_AES_XTS)
		aesni_set_enckey(key + keylen / 16, ses->xts_schedule,
		    ses->rounds);

	return (0);
}