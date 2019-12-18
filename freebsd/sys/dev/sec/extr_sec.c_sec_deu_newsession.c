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
struct sec_softc {int dummy; } ;
struct sec_session {int /*<<< orphan*/  ss_ivlen; } ;
struct cryptoini {int cri_alg; } ;

/* Variables and functions */
#define  CRYPTO_3DES_CBC 129 
#define  CRYPTO_DES_CBC 128 
 int /*<<< orphan*/  DES_BLOCK_LEN ; 

__attribute__((used)) static int
sec_deu_newsession(struct sec_softc *sc, struct sec_session *ses,
    struct cryptoini *enc, struct cryptoini *mac)
{

	if (enc == NULL)
		return (-1);

	switch (enc->cri_alg) {
	case CRYPTO_DES_CBC:
	case CRYPTO_3DES_CBC:
		break;
	default:
		return (-1);
	}

	ses->ss_ivlen = DES_BLOCK_LEN;

	return (0);
}