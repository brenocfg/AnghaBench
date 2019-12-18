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
struct uio {int dummy; } ;
struct mbuf {int dummy; } ;
struct hifn_softc {int /*<<< orphan*/  sc_needwakeup; int /*<<< orphan*/  sc_dev; } ;
struct hifn_session {int /*<<< orphan*/  hs_iv; } ;
struct hifn_command {int cry_masks; int cklen; int mac_masks; struct hifn_softc* softc; struct hifn_session* session; struct cryptop* crp; scalar_t__ mac; int /*<<< orphan*/  base_masks; struct cryptodesc* maccrd; int /*<<< orphan*/  ck; scalar_t__ iv; struct cryptodesc* enccrd; struct uio* dst_io; struct uio* src_io; struct mbuf* dst_m; struct mbuf* src_m; } ;
struct cryptop {int crp_flags; int crp_etype; scalar_t__ crp_buf; struct cryptodesc* crp_desc; int /*<<< orphan*/  crp_session; int /*<<< orphan*/ * crp_callback; } ;
struct cryptodesc {int crd_alg; int crd_flags; int crd_klen; int /*<<< orphan*/  crd_key; int /*<<< orphan*/  crd_inject; int /*<<< orphan*/  crd_iv; struct cryptodesc* crd_next; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  hst_nomem; int /*<<< orphan*/  hst_invalid; } ;

/* Variables and functions */
 int CRD_F_ENCRYPT ; 
 int CRD_F_IV_EXPLICIT ; 
 int CRD_F_IV_PRESENT ; 
 int CRD_F_KEY_EXPLICIT ; 
#define  CRYPTO_3DES_CBC 135 
#define  CRYPTO_AES_CBC 134 
#define  CRYPTO_ARC4 133 
#define  CRYPTO_DES_CBC 132 
 int CRYPTO_F_IMBUF ; 
 int CRYPTO_F_IOV ; 
#define  CRYPTO_MD5 131 
#define  CRYPTO_MD5_HMAC 130 
#define  CRYPTO_SHA1 129 
#define  CRYPTO_SHA1_HMAC 128 
 int /*<<< orphan*/  CRYPTO_SYMQ ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERESTART ; 
 int HIFN_AES_IV_LENGTH ; 
 int /*<<< orphan*/  HIFN_BASE_CMD_CRYPT ; 
 int /*<<< orphan*/  HIFN_BASE_CMD_DECODE ; 
 int /*<<< orphan*/  HIFN_BASE_CMD_MAC ; 
 int HIFN_CRYPT_CMD_ALG_3DES ; 
 int HIFN_CRYPT_CMD_ALG_AES ; 
 int HIFN_CRYPT_CMD_ALG_DES ; 
 int HIFN_CRYPT_CMD_ALG_MASK ; 
 int HIFN_CRYPT_CMD_ALG_RC4 ; 
 int HIFN_CRYPT_CMD_KSZ_128 ; 
 int HIFN_CRYPT_CMD_KSZ_192 ; 
 int HIFN_CRYPT_CMD_KSZ_256 ; 
 int HIFN_CRYPT_CMD_MODE_CBC ; 
 int HIFN_CRYPT_CMD_NEW_IV ; 
 int HIFN_CRYPT_CMD_NEW_KEY ; 
 int HIFN_IV_LENGTH ; 
 int HIFN_MAC_CMD_ALG_MD5 ; 
 int HIFN_MAC_CMD_ALG_SHA1 ; 
 int HIFN_MAC_CMD_MODE_HASH ; 
 int HIFN_MAC_CMD_MODE_HMAC ; 
 int HIFN_MAC_CMD_NEW_KEY ; 
 int HIFN_MAC_CMD_POS_IPSEC ; 
 int HIFN_MAC_CMD_RESULT ; 
 int HIFN_MAC_CMD_TRUNC ; 
 scalar_t__ HIFN_MAC_KEY_LENGTH ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  bzero (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  crypto_copyback (int,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  crypto_copydata (int,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  crypto_done (struct cryptop*) ; 
 struct hifn_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 struct hifn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct hifn_command*,int /*<<< orphan*/ ) ; 
 int hifn_crypto (struct hifn_softc*,struct hifn_command*,struct cryptop*,int) ; 
 scalar_t__ hifn_debug ; 
 TYPE_1__ hifnstats ; 
 struct hifn_command* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hifn_process(device_t dev, struct cryptop *crp, int hint)
{
	struct hifn_softc *sc = device_get_softc(dev);
	struct hifn_command *cmd = NULL;
	int err, ivlen;
	struct cryptodesc *crd1, *crd2, *maccrd, *enccrd;
	struct hifn_session *ses;

	if (crp == NULL || crp->crp_callback == NULL) {
		hifnstats.hst_invalid++;
		return (EINVAL);
	}

	ses = crypto_get_driver_session(crp->crp_session);
	cmd = malloc(sizeof(struct hifn_command), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (cmd == NULL) {
		hifnstats.hst_nomem++;
		err = ENOMEM;
		goto errout;
	}

	if (crp->crp_flags & CRYPTO_F_IMBUF) {
		cmd->src_m = (struct mbuf *)crp->crp_buf;
		cmd->dst_m = (struct mbuf *)crp->crp_buf;
	} else if (crp->crp_flags & CRYPTO_F_IOV) {
		cmd->src_io = (struct uio *)crp->crp_buf;
		cmd->dst_io = (struct uio *)crp->crp_buf;
	} else {
		err = EINVAL;
		goto errout;	/* XXX we don't handle contiguous buffers! */
	}

	crd1 = crp->crp_desc;
	if (crd1 == NULL) {
		err = EINVAL;
		goto errout;
	}
	crd2 = crd1->crd_next;

	if (crd2 == NULL) {
		if (crd1->crd_alg == CRYPTO_MD5_HMAC ||
		    crd1->crd_alg == CRYPTO_SHA1_HMAC ||
		    crd1->crd_alg == CRYPTO_SHA1 ||
		    crd1->crd_alg == CRYPTO_MD5) {
			maccrd = crd1;
			enccrd = NULL;
		} else if (crd1->crd_alg == CRYPTO_DES_CBC ||
		    crd1->crd_alg == CRYPTO_3DES_CBC ||
		    crd1->crd_alg == CRYPTO_AES_CBC ||
		    crd1->crd_alg == CRYPTO_ARC4) {
			if ((crd1->crd_flags & CRD_F_ENCRYPT) == 0)
				cmd->base_masks |= HIFN_BASE_CMD_DECODE;
			maccrd = NULL;
			enccrd = crd1;
		} else {
			err = EINVAL;
			goto errout;
		}
	} else {
		if ((crd1->crd_alg == CRYPTO_MD5_HMAC ||
                     crd1->crd_alg == CRYPTO_SHA1_HMAC ||
                     crd1->crd_alg == CRYPTO_MD5 ||
                     crd1->crd_alg == CRYPTO_SHA1) &&
		    (crd2->crd_alg == CRYPTO_DES_CBC ||
		     crd2->crd_alg == CRYPTO_3DES_CBC ||
		     crd2->crd_alg == CRYPTO_AES_CBC ||
		     crd2->crd_alg == CRYPTO_ARC4) &&
		    ((crd2->crd_flags & CRD_F_ENCRYPT) == 0)) {
			cmd->base_masks = HIFN_BASE_CMD_DECODE;
			maccrd = crd1;
			enccrd = crd2;
		} else if ((crd1->crd_alg == CRYPTO_DES_CBC ||
		     crd1->crd_alg == CRYPTO_ARC4 ||
		     crd1->crd_alg == CRYPTO_3DES_CBC ||
		     crd1->crd_alg == CRYPTO_AES_CBC) &&
		    (crd2->crd_alg == CRYPTO_MD5_HMAC ||
                     crd2->crd_alg == CRYPTO_SHA1_HMAC ||
                     crd2->crd_alg == CRYPTO_MD5 ||
                     crd2->crd_alg == CRYPTO_SHA1) &&
		    (crd1->crd_flags & CRD_F_ENCRYPT)) {
			enccrd = crd1;
			maccrd = crd2;
		} else {
			/*
			 * We cannot order the 7751 as requested
			 */
			err = EINVAL;
			goto errout;
		}
	}

	if (enccrd) {
		cmd->enccrd = enccrd;
		cmd->base_masks |= HIFN_BASE_CMD_CRYPT;
		switch (enccrd->crd_alg) {
		case CRYPTO_ARC4:
			cmd->cry_masks |= HIFN_CRYPT_CMD_ALG_RC4;
			break;
		case CRYPTO_DES_CBC:
			cmd->cry_masks |= HIFN_CRYPT_CMD_ALG_DES |
			    HIFN_CRYPT_CMD_MODE_CBC |
			    HIFN_CRYPT_CMD_NEW_IV;
			break;
		case CRYPTO_3DES_CBC:
			cmd->cry_masks |= HIFN_CRYPT_CMD_ALG_3DES |
			    HIFN_CRYPT_CMD_MODE_CBC |
			    HIFN_CRYPT_CMD_NEW_IV;
			break;
		case CRYPTO_AES_CBC:
			cmd->cry_masks |= HIFN_CRYPT_CMD_ALG_AES |
			    HIFN_CRYPT_CMD_MODE_CBC |
			    HIFN_CRYPT_CMD_NEW_IV;
			break;
		default:
			err = EINVAL;
			goto errout;
		}
		if (enccrd->crd_alg != CRYPTO_ARC4) {
			ivlen = ((enccrd->crd_alg == CRYPTO_AES_CBC) ?
				HIFN_AES_IV_LENGTH : HIFN_IV_LENGTH);
			if (enccrd->crd_flags & CRD_F_ENCRYPT) {
				if (enccrd->crd_flags & CRD_F_IV_EXPLICIT)
					bcopy(enccrd->crd_iv, cmd->iv, ivlen);
				else
					bcopy(ses->hs_iv, cmd->iv, ivlen);

				if ((enccrd->crd_flags & CRD_F_IV_PRESENT)
				    == 0) {
					crypto_copyback(crp->crp_flags,
					    crp->crp_buf, enccrd->crd_inject,
					    ivlen, cmd->iv);
				}
			} else {
				if (enccrd->crd_flags & CRD_F_IV_EXPLICIT)
					bcopy(enccrd->crd_iv, cmd->iv, ivlen);
				else {
					crypto_copydata(crp->crp_flags,
					    crp->crp_buf, enccrd->crd_inject,
					    ivlen, cmd->iv);
				}
			}
		}

		if (enccrd->crd_flags & CRD_F_KEY_EXPLICIT)
			cmd->cry_masks |= HIFN_CRYPT_CMD_NEW_KEY;
		cmd->ck = enccrd->crd_key;
		cmd->cklen = enccrd->crd_klen >> 3;
		cmd->cry_masks |= HIFN_CRYPT_CMD_NEW_KEY;

		/* 
		 * Need to specify the size for the AES key in the masks.
		 */
		if ((cmd->cry_masks & HIFN_CRYPT_CMD_ALG_MASK) ==
		    HIFN_CRYPT_CMD_ALG_AES) {
			switch (cmd->cklen) {
			case 16:
				cmd->cry_masks |= HIFN_CRYPT_CMD_KSZ_128;
				break;
			case 24:
				cmd->cry_masks |= HIFN_CRYPT_CMD_KSZ_192;
				break;
			case 32:
				cmd->cry_masks |= HIFN_CRYPT_CMD_KSZ_256;
				break;
			default:
				err = EINVAL;
				goto errout;
			}
		}
	}

	if (maccrd) {
		cmd->maccrd = maccrd;
		cmd->base_masks |= HIFN_BASE_CMD_MAC;

		switch (maccrd->crd_alg) {
		case CRYPTO_MD5:
			cmd->mac_masks |= HIFN_MAC_CMD_ALG_MD5 |
			    HIFN_MAC_CMD_RESULT | HIFN_MAC_CMD_MODE_HASH |
			    HIFN_MAC_CMD_POS_IPSEC;
                       break;
		case CRYPTO_MD5_HMAC:
			cmd->mac_masks |= HIFN_MAC_CMD_ALG_MD5 |
			    HIFN_MAC_CMD_RESULT | HIFN_MAC_CMD_MODE_HMAC |
			    HIFN_MAC_CMD_POS_IPSEC | HIFN_MAC_CMD_TRUNC;
			break;
		case CRYPTO_SHA1:
			cmd->mac_masks |= HIFN_MAC_CMD_ALG_SHA1 |
			    HIFN_MAC_CMD_RESULT | HIFN_MAC_CMD_MODE_HASH |
			    HIFN_MAC_CMD_POS_IPSEC;
			break;
		case CRYPTO_SHA1_HMAC:
			cmd->mac_masks |= HIFN_MAC_CMD_ALG_SHA1 |
			    HIFN_MAC_CMD_RESULT | HIFN_MAC_CMD_MODE_HMAC |
			    HIFN_MAC_CMD_POS_IPSEC | HIFN_MAC_CMD_TRUNC;
			break;
		}

		if (maccrd->crd_alg == CRYPTO_SHA1_HMAC ||
		     maccrd->crd_alg == CRYPTO_MD5_HMAC) {
			cmd->mac_masks |= HIFN_MAC_CMD_NEW_KEY;
			bcopy(maccrd->crd_key, cmd->mac, maccrd->crd_klen >> 3);
			bzero(cmd->mac + (maccrd->crd_klen >> 3),
			    HIFN_MAC_KEY_LENGTH - (maccrd->crd_klen >> 3));
		}
	}

	cmd->crp = crp;
	cmd->session = ses;
	cmd->softc = sc;

	err = hifn_crypto(sc, cmd, crp, hint);
	if (!err) {
		return 0;
	} else if (err == ERESTART) {
		/*
		 * There weren't enough resources to dispatch the request
		 * to the part.  Notify the caller so they'll requeue this
		 * request and resubmit it again soon.
		 */
#ifdef HIFN_DEBUG
		if (hifn_debug)
			device_printf(sc->sc_dev, "requeue request\n");
#endif
		free(cmd, M_DEVBUF);
		sc->sc_needwakeup |= CRYPTO_SYMQ;
		return (err);
	}

errout:
	if (cmd != NULL)
		free(cmd, M_DEVBUF);
	if (err == EINVAL)
		hifnstats.hst_invalid++;
	else
		hifnstats.hst_nomem++;
	crp->crp_etype = err;
	crypto_done(crp);
	return (err);
}