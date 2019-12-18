#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sec_softc {int sc_version; int /*<<< orphan*/  sc_blocked; scalar_t__ sc_shutdown; } ;
struct sec_session {int ss_ivlen; int ss_klen; int ss_mklen; TYPE_1__* ss_eu; int /*<<< orphan*/  ss_mkey; int /*<<< orphan*/  ss_key; } ;
struct sec_desc {TYPE_2__* sd_desc; struct cryptop* sd_crp; scalar_t__ sd_error; scalar_t__ sd_lt_used; } ;
struct cryptop {scalar_t__ crp_ilen; int crp_etype; int crp_flags; int /*<<< orphan*/  crp_buf; int /*<<< orphan*/  crp_session; } ;
struct cryptodesc {int crd_flags; int crd_klen; int /*<<< orphan*/  crd_key; int /*<<< orphan*/  crd_inject; int /*<<< orphan*/  crd_iv; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int shd_dn; int /*<<< orphan*/  shd_mkey; int /*<<< orphan*/  shd_key; int /*<<< orphan*/  shd_iv; } ;
struct TYPE_3__ {int (* sem_make_desc ) (struct sec_softc*,struct sec_session*,struct sec_desc*,struct cryptop*,int) ;} ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CRD_F_ENCRYPT ; 
 int CRD_F_IV_EXPLICIT ; 
 int CRD_F_IV_PRESENT ; 
 int CRD_F_KEY_EXPLICIT ; 
 int CRYPTO_F_IMBUF ; 
 int CRYPTO_F_IOV ; 
 int CRYPTO_HINT_MORE ; 
 int /*<<< orphan*/  CRYPTO_SYMQ ; 
 void* E2BIG ; 
 int EINVAL ; 
 int ERESTART ; 
 int /*<<< orphan*/  SEC_DESC_FREE2READY (struct sec_softc*) ; 
 int /*<<< orphan*/  SEC_DESC_FREE_POINTERS (struct sec_desc*) ; 
 int /*<<< orphan*/  SEC_DESC_PUT_BACK_LT (struct sec_softc*,struct sec_desc*) ; 
 int /*<<< orphan*/  SEC_DESC_SYNC (struct sec_softc*,int) ; 
 int /*<<< orphan*/  SEC_DESC_SYNC_POINTERS (struct sec_desc*,int) ; 
 scalar_t__ SEC_FREE_DESC_CNT (struct sec_softc*) ; 
 struct sec_desc* SEC_GET_FREE_DESC (struct sec_softc*) ; 
 int /*<<< orphan*/  SEC_LOCK (struct sec_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ SEC_MAX_DMA_BLOCK_SIZE ; 
 int SEC_MAX_KEY_LEN ; 
 int SEC_MBUF ; 
 int SEC_MEMORY ; 
 int /*<<< orphan*/  SEC_PUT_BACK_FREE_DESC (struct sec_softc*) ; 
 int SEC_UIO ; 
 int /*<<< orphan*/  SEC_UNLOCK (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc4rand (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_copyback (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_copydata (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_done (struct cryptop*) ; 
 struct sec_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  descriptors ; 
 struct sec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sec_enqueue (struct sec_softc*) ; 
 scalar_t__ sec_split_crp (struct cryptop*,struct cryptodesc**,struct cryptodesc**) ; 
 int stub1 (struct sec_softc*,struct sec_session*,struct sec_desc*,struct cryptop*,int) ; 

__attribute__((used)) static int
sec_process(device_t dev, struct cryptop *crp, int hint)
{
	struct sec_softc *sc = device_get_softc(dev);
	struct sec_desc *desc = NULL;
	struct cryptodesc *mac, *enc;
	struct sec_session *ses;
	int buftype, error = 0;

	ses = crypto_get_driver_session(crp->crp_session);

	/* Check for input length */
	if (crp->crp_ilen > SEC_MAX_DMA_BLOCK_SIZE) {
		crp->crp_etype = E2BIG;
		crypto_done(crp);
		return (0);
	}

	/* Get descriptors */
	if (sec_split_crp(crp, &enc, &mac)) {
		crp->crp_etype = EINVAL;
		crypto_done(crp);
		return (0);
	}

	SEC_LOCK(sc, descriptors);
	SEC_DESC_SYNC(sc, BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	/* Block driver if there is no free descriptors or we are going down */
	if (SEC_FREE_DESC_CNT(sc) == 0 || sc->sc_shutdown) {
		sc->sc_blocked |= CRYPTO_SYMQ;
		SEC_UNLOCK(sc, descriptors);
		return (ERESTART);
	}

	/* Prepare descriptor */
	desc = SEC_GET_FREE_DESC(sc);
	desc->sd_lt_used = 0;
	desc->sd_error = 0;
	desc->sd_crp = crp;

	if (crp->crp_flags & CRYPTO_F_IOV)
		buftype = SEC_UIO;
	else if (crp->crp_flags & CRYPTO_F_IMBUF)
		buftype = SEC_MBUF;
	else
		buftype = SEC_MEMORY;

	if (enc && enc->crd_flags & CRD_F_ENCRYPT) {
		if (enc->crd_flags & CRD_F_IV_EXPLICIT)
			memcpy(desc->sd_desc->shd_iv, enc->crd_iv,
			    ses->ss_ivlen);
		else
			arc4rand(desc->sd_desc->shd_iv, ses->ss_ivlen, 0);

		if ((enc->crd_flags & CRD_F_IV_PRESENT) == 0)
			crypto_copyback(crp->crp_flags, crp->crp_buf,
			    enc->crd_inject, ses->ss_ivlen,
			    desc->sd_desc->shd_iv);
	} else if (enc) {
		if (enc->crd_flags & CRD_F_IV_EXPLICIT)
			memcpy(desc->sd_desc->shd_iv, enc->crd_iv,
			    ses->ss_ivlen);
		else
			crypto_copydata(crp->crp_flags, crp->crp_buf,
			    enc->crd_inject, ses->ss_ivlen,
			    desc->sd_desc->shd_iv);
	}

	if (enc && enc->crd_flags & CRD_F_KEY_EXPLICIT) {
		if ((enc->crd_klen / 8) <= SEC_MAX_KEY_LEN) {
			ses->ss_klen = enc->crd_klen / 8;
			memcpy(ses->ss_key, enc->crd_key, ses->ss_klen);
		} else
			error = E2BIG;
	}

	if (!error && mac && mac->crd_flags & CRD_F_KEY_EXPLICIT) {
		if ((mac->crd_klen / 8) <= SEC_MAX_KEY_LEN) {
			ses->ss_mklen = mac->crd_klen / 8;
			memcpy(ses->ss_mkey, mac->crd_key, ses->ss_mklen);
		} else
			error = E2BIG;
	}

	if (!error) {
		memcpy(desc->sd_desc->shd_key, ses->ss_key, ses->ss_klen);
		memcpy(desc->sd_desc->shd_mkey, ses->ss_mkey, ses->ss_mklen);

		error = ses->ss_eu->sem_make_desc(sc, ses, desc, crp, buftype);
	}

	if (error) {
		SEC_DESC_FREE_POINTERS(desc);
		SEC_DESC_PUT_BACK_LT(sc, desc);
		SEC_PUT_BACK_FREE_DESC(sc);
		SEC_UNLOCK(sc, descriptors);
		crp->crp_etype = error;
		crypto_done(crp);
		return (0);
	}

	/*
	 * Skip DONE interrupt if this is not last request in burst, but only
	 * if we are running on SEC 3.X. On SEC 2.X we have to enable DONE
	 * signaling on each descriptor.
	 */
	if ((hint & CRYPTO_HINT_MORE) && sc->sc_version == 3)
		desc->sd_desc->shd_dn = 0;
	else
		desc->sd_desc->shd_dn = 1;

	SEC_DESC_SYNC(sc, BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	SEC_DESC_SYNC_POINTERS(desc, BUS_DMASYNC_POSTREAD |
	    BUS_DMASYNC_POSTWRITE);
	SEC_DESC_FREE2READY(sc);
	SEC_UNLOCK(sc, descriptors);

	/* Enqueue ready descriptors in hardware */
	sec_enqueue(sc);

	return (0);
}