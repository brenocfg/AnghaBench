#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct uio {int dummy; } ;
struct mbuf {int dummy; } ;
struct cesa_tdma_desc {int dummy; } ;
struct cesa_softc {int /*<<< orphan*/  sc_data_dtag; } ;
struct cesa_request {int cr_dmap_loaded; TYPE_4__* cr_crp; int /*<<< orphan*/  cr_dmap; scalar_t__ cr_mac; TYPE_3__* cr_enc; TYPE_2__* cr_cs; TYPE_1__* cr_csd; } ;
struct cesa_chain_info {int cci_config; int cci_error; scalar_t__ cci_mac; TYPE_3__* cci_enc; struct cesa_request* cci_cr; struct cesa_softc* cci_sc; } ;
struct TYPE_8__ {int crp_flags; int /*<<< orphan*/  crp_ilen; scalar_t__ crp_buf; } ;
struct TYPE_7__ {scalar_t__ crd_alg; int crd_flags; } ;
struct TYPE_6__ {int cs_config; int /*<<< orphan*/  cs_hiv_out; int /*<<< orphan*/  cs_hiv_in; int /*<<< orphan*/  cs_klen; int /*<<< orphan*/  cs_key; int /*<<< orphan*/  cs_aes_dkey; } ;
struct TYPE_5__ {int /*<<< orphan*/  csd_hiv_out; int /*<<< orphan*/  csd_hiv_in; int /*<<< orphan*/  csd_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int CESA_CSHD_DECRYPT ; 
 int CESA_CSHD_ENC ; 
 int CESA_CSHD_ENC_AND_MAC ; 
 int CESA_CSHD_MAC ; 
 int CESA_CSHD_MAC_AND_ENC ; 
 int /*<<< orphan*/  CESA_LOCK_ASSERT (struct cesa_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CESA_MAX_HASH_LEN ; 
 int CRD_F_ENCRYPT ; 
 scalar_t__ CRYPTO_AES_CBC ; 
 int CRYPTO_F_IMBUF ; 
 int CRYPTO_F_IOV ; 
 int ENOMEM ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cesa_chain_info*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_mbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ,struct cesa_chain_info*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_uio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio*,int /*<<< orphan*/ ,struct cesa_chain_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cesa_append_tdesc (struct cesa_request*,struct cesa_tdma_desc*) ; 
 int /*<<< orphan*/  cesa_create_chain_cb ; 
 int /*<<< orphan*/  cesa_create_chain_cb2 ; 
 struct cesa_tdma_desc* cesa_tdma_copyin_sa_data (struct cesa_softc*,struct cesa_request*) ; 
 struct cesa_tdma_desc* cesa_tdma_copyout_sa_data (struct cesa_softc*,struct cesa_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sessions ; 

__attribute__((used)) static int
cesa_create_chain(struct cesa_softc *sc, struct cesa_request *cr)
{
	struct cesa_chain_info cci;
	struct cesa_tdma_desc *ctd;
	uint32_t config;
	int error;

	error = 0;
	CESA_LOCK_ASSERT(sc, sessions);

	/* Create request metadata */
	if (cr->cr_enc) {
		if (cr->cr_enc->crd_alg == CRYPTO_AES_CBC &&
		    (cr->cr_enc->crd_flags & CRD_F_ENCRYPT) == 0)
			memcpy(cr->cr_csd->csd_key, cr->cr_cs->cs_aes_dkey,
			    cr->cr_cs->cs_klen);
		else
			memcpy(cr->cr_csd->csd_key, cr->cr_cs->cs_key,
			    cr->cr_cs->cs_klen);
	}

	if (cr->cr_mac) {
		memcpy(cr->cr_csd->csd_hiv_in, cr->cr_cs->cs_hiv_in,
		    CESA_MAX_HASH_LEN);
		memcpy(cr->cr_csd->csd_hiv_out, cr->cr_cs->cs_hiv_out,
		    CESA_MAX_HASH_LEN);
	}

	ctd = cesa_tdma_copyin_sa_data(sc, cr);
	if (!ctd)
		return (ENOMEM);

	cesa_append_tdesc(cr, ctd);

	/* Prepare SA configuration */
	config = cr->cr_cs->cs_config;

	if (cr->cr_enc && (cr->cr_enc->crd_flags & CRD_F_ENCRYPT) == 0)
		config |= CESA_CSHD_DECRYPT;
	if (cr->cr_enc && !cr->cr_mac)
		config |= CESA_CSHD_ENC;
	if (!cr->cr_enc && cr->cr_mac)
		config |= CESA_CSHD_MAC;
	if (cr->cr_enc && cr->cr_mac)
		config |= (config & CESA_CSHD_DECRYPT) ? CESA_CSHD_MAC_AND_ENC :
		    CESA_CSHD_ENC_AND_MAC;

	/* Create data packets */
	cci.cci_sc = sc;
	cci.cci_cr = cr;
	cci.cci_enc = cr->cr_enc;
	cci.cci_mac = cr->cr_mac;
	cci.cci_config = config;
	cci.cci_error = 0;

	if (cr->cr_crp->crp_flags & CRYPTO_F_IOV)
		error = bus_dmamap_load_uio(sc->sc_data_dtag,
		    cr->cr_dmap, (struct uio *)cr->cr_crp->crp_buf,
		    cesa_create_chain_cb2, &cci, BUS_DMA_NOWAIT);
	else if (cr->cr_crp->crp_flags & CRYPTO_F_IMBUF)
		error = bus_dmamap_load_mbuf(sc->sc_data_dtag,
		    cr->cr_dmap, (struct mbuf *)cr->cr_crp->crp_buf,
		    cesa_create_chain_cb2, &cci, BUS_DMA_NOWAIT);
	else
		error = bus_dmamap_load(sc->sc_data_dtag,
		    cr->cr_dmap, cr->cr_crp->crp_buf,
		    cr->cr_crp->crp_ilen, cesa_create_chain_cb, &cci,
		    BUS_DMA_NOWAIT);

	if (!error)
		cr->cr_dmap_loaded = 1;

	if (cci.cci_error)
		error = cci.cci_error;

	if (error)
		return (error);

	/* Read back request metadata */
	ctd = cesa_tdma_copyout_sa_data(sc, cr);
	if (!ctd)
		return (ENOMEM);

	cesa_append_tdesc(cr, ctd);

	return (0);
}