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
struct cryptoini {scalar_t__ cri_alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_LEN ; 
 scalar_t__ CRYPTO_AES_CBC ; 

__attribute__((used)) static int
sec_aesu_newsession(struct sec_softc *sc, struct sec_session *ses,
    struct cryptoini *enc, struct cryptoini *mac)
{

	if (enc == NULL)
		return (-1);

	if (enc->cri_alg != CRYPTO_AES_CBC)
		return (-1);

	ses->ss_ivlen = AES_BLOCK_LEN;

	return (0);
}