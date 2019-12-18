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
typedef  int /*<<< orphan*/  uint64_t ;
struct xlp_sec_softc {int dummy; } ;
struct xlp_sec_command {scalar_t__ cipheralg; scalar_t__ hashdest; int /*<<< orphan*/  cipherlen; int /*<<< orphan*/  cipheroff; int /*<<< orphan*/  hmacpad; int /*<<< orphan*/  hashlen; int /*<<< orphan*/  hashoff; int /*<<< orphan*/  ivlen; int /*<<< orphan*/  ivoff; int /*<<< orphan*/  hashsrc; int /*<<< orphan*/  paramp; int /*<<< orphan*/  ctrlp; int /*<<< orphan*/  ciphermode; int /*<<< orphan*/  hashmode; int /*<<< orphan*/  hashalg; scalar_t__ des3key; struct cryptodesc* maccrd; struct cryptodesc* enccrd; } ;
struct cryptodesc {int crd_flags; int crd_klen; scalar_t__ crd_key; } ;

/* Variables and functions */
 int CRD_F_ENCRYPT ; 
 scalar_t__ NLM_CIPHER_3DES ; 
 int nlm_crypto_complete_sec_request (struct xlp_sec_softc*,struct xlp_sec_command*) ; 
 int /*<<< orphan*/  nlm_crypto_fill_cipher_auth_pkt_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  nlm_crypto_fill_pkt_ctrl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  nlm_crypto_form_srcdst_segs (struct xlp_sec_command*) ; 

int
nlm_crypto_do_cipher_digest(struct xlp_sec_softc *sc,
    struct xlp_sec_command *cmd)
{
	struct cryptodesc *cipdesc=NULL, *digdesc=NULL;
	unsigned char *cipkey = NULL;
	int ret=0;

	cipdesc = cmd->enccrd;
	digdesc = cmd->maccrd;

	cipkey = (unsigned char *)cipdesc->crd_key;
	if (cmd->cipheralg == NLM_CIPHER_3DES) {
		if (!(cipdesc->crd_flags & CRD_F_ENCRYPT)) {
			uint64_t *k, *tkey;
			k = (uint64_t *)cipdesc->crd_key;
			tkey = (uint64_t *)cmd->des3key;
			tkey[2] = k[0];
			tkey[1] = k[1];
			tkey[0] = k[2];
			cipkey = (unsigned char *)tkey;
		}
	}
	nlm_crypto_fill_pkt_ctrl(cmd->ctrlp, (digdesc->crd_klen) ? 1 : 0,
	    cmd->hashalg, cmd->hashmode, cmd->cipheralg, cmd->ciphermode,
	    cipkey, (cipdesc->crd_klen >> 3),
	    digdesc->crd_key, (digdesc->crd_klen >> 3));

	nlm_crypto_fill_cipher_auth_pkt_param(cmd->ctrlp, cmd->paramp,
	    (cipdesc->crd_flags & CRD_F_ENCRYPT) ? 1 : 0, cmd->hashsrc,
	    cmd->ivoff, cmd->ivlen, cmd->hashoff, cmd->hashlen,
	    cmd->hmacpad, cmd->cipheroff, cmd->cipherlen,
	    (unsigned char *)cmd->hashdest);

	nlm_crypto_form_srcdst_segs(cmd);

	ret = nlm_crypto_complete_sec_request(sc, cmd);
	return (ret);
}