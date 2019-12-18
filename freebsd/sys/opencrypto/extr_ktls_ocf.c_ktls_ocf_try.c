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
struct socket {int dummy; } ;
struct ocf_session {int crda_alg; int /*<<< orphan*/  lock; int /*<<< orphan*/  sid; } ;
struct TYPE_2__ {int cipher_algorithm; int cipher_key_len; scalar_t__ tls_vmajor; scalar_t__ tls_vminor; int /*<<< orphan*/  cipher_key; int /*<<< orphan*/  iv_len; } ;
struct ktls_session {int /*<<< orphan*/  free; int /*<<< orphan*/  sw_encrypt; struct ocf_session* cipher; TYPE_1__ params; } ;
struct cryptoini {int cri_alg; int cri_klen; struct cryptoini* cri_next; int /*<<< orphan*/  cri_key; } ;
typedef  int /*<<< orphan*/  crie ;
typedef  int /*<<< orphan*/  cria ;

/* Variables and functions */
 int CRYPTO_AES_128_NIST_GMAC ; 
 int CRYPTO_AES_256_NIST_GMAC ; 
#define  CRYPTO_AES_NIST_GCM_16 128 
 int CRYPTO_FLAG_HARDWARE ; 
 int CRYPTO_FLAG_SOFTWARE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_KTLS_OCF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TLS_AEAD_GCM_LEN ; 
 scalar_t__ TLS_MAJOR_VER_ONE ; 
 scalar_t__ TLS_MINOR_VER_ONE ; 
 scalar_t__ TLS_MINOR_VER_TWO ; 
 int crypto_newsession (int /*<<< orphan*/ *,struct cryptoini*,int) ; 
 int /*<<< orphan*/  free (struct ocf_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktls_ocf_encrypt ; 
 int /*<<< orphan*/  ktls_ocf_free ; 
 struct ocf_session* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct cryptoini*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ktls_ocf_try(struct socket *so, struct ktls_session *tls)
{
	struct cryptoini cria, crie;
	struct ocf_session *os;
	int error;

	memset(&cria, 0, sizeof(cria));
	memset(&crie, 0, sizeof(crie));

	switch (tls->params.cipher_algorithm) {
	case CRYPTO_AES_NIST_GCM_16:
		if (tls->params.iv_len != TLS_AEAD_GCM_LEN)
			return (EINVAL);
		switch (tls->params.cipher_key_len) {
		case 128 / 8:
			cria.cri_alg = CRYPTO_AES_128_NIST_GMAC;
			break;
		case 256 / 8:
			cria.cri_alg = CRYPTO_AES_256_NIST_GMAC;
			break;
		default:
			return (EINVAL);
		}
		cria.cri_key = tls->params.cipher_key;
		cria.cri_klen = tls->params.cipher_key_len * 8;
		break;
	default:
		return (EPROTONOSUPPORT);
	}

	/* Only TLS 1.1 and TLS 1.2 are currently supported. */
	if (tls->params.tls_vmajor != TLS_MAJOR_VER_ONE ||
	    tls->params.tls_vminor < TLS_MINOR_VER_ONE ||
	    tls->params.tls_vminor > TLS_MINOR_VER_TWO)
		return (EPROTONOSUPPORT);

	os = malloc(sizeof(*os), M_KTLS_OCF, M_NOWAIT | M_ZERO);
	if (os == NULL)
		return (ENOMEM);

	crie.cri_alg = tls->params.cipher_algorithm;
	crie.cri_key = tls->params.cipher_key;
	crie.cri_klen = tls->params.cipher_key_len * 8;

	crie.cri_next = &cria;
	error = crypto_newsession(&os->sid, &crie,
	    CRYPTO_FLAG_HARDWARE | CRYPTO_FLAG_SOFTWARE);
	if (error) {
		free(os, M_KTLS_OCF);
		return (error);
	}

	os->crda_alg = cria.cri_alg;
	mtx_init(&os->lock, "ktls_ocf", NULL, MTX_DEF);
	tls->cipher = os;
	tls->sw_encrypt = ktls_ocf_encrypt;
	tls->free = ktls_ocf_free;
	return (0);
}