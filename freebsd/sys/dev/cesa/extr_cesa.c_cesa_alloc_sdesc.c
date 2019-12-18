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
struct cesa_softc {int /*<<< orphan*/  sc_dev; } ;
struct cesa_sa_desc {TYPE_1__* csd_cshd; } ;
struct cesa_request {int /*<<< orphan*/  cr_sdesc; } ;
struct TYPE_2__ {scalar_t__ cshd_mac_dlen; scalar_t__ cshd_mac_src; void* cshd_mac_iv_out; void* cshd_mac_iv_in; void* cshd_mac_dst; scalar_t__ cshd_enc_dlen; scalar_t__ cshd_enc_dst; scalar_t__ cshd_enc_src; void* cshd_enc_iv_buf; void* cshd_enc_iv; void* cshd_enc_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_GENERIC_ALLOC_LOCKED (struct cesa_softc*,struct cesa_sa_desc*,int /*<<< orphan*/ ) ; 
 void* CESA_SA_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cesa_sa_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csd_hash ; 
 int /*<<< orphan*/  csd_hiv_in ; 
 int /*<<< orphan*/  csd_hiv_out ; 
 int /*<<< orphan*/  csd_iv ; 
 int /*<<< orphan*/  csd_key ; 
 int /*<<< orphan*/  csd_stq ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdesc ; 

__attribute__((used)) static struct cesa_sa_desc *
cesa_alloc_sdesc(struct cesa_softc *sc, struct cesa_request *cr)
{
	struct cesa_sa_desc *csd;

	CESA_GENERIC_ALLOC_LOCKED(sc, csd, sdesc);
	if (!csd) {
		device_printf(sc->sc_dev, "SA descriptors pool exhaused. "
		    "Consider increasing CESA_SA_DESCRIPTORS.\n");
		return (NULL);
	}

	STAILQ_INSERT_TAIL(&cr->cr_sdesc, csd, csd_stq);

	/* Fill-in SA descriptor with default values */
	csd->csd_cshd->cshd_enc_key = CESA_SA_DATA(csd_key);
	csd->csd_cshd->cshd_enc_iv = CESA_SA_DATA(csd_iv);
	csd->csd_cshd->cshd_enc_iv_buf = CESA_SA_DATA(csd_iv);
	csd->csd_cshd->cshd_enc_src = 0;
	csd->csd_cshd->cshd_enc_dst = 0;
	csd->csd_cshd->cshd_enc_dlen = 0;
	csd->csd_cshd->cshd_mac_dst = CESA_SA_DATA(csd_hash);
	csd->csd_cshd->cshd_mac_iv_in = CESA_SA_DATA(csd_hiv_in);
	csd->csd_cshd->cshd_mac_iv_out = CESA_SA_DATA(csd_hiv_out);
	csd->csd_cshd->cshd_mac_src = 0;
	csd->csd_cshd->cshd_mac_dlen = 0;

	return (csd);
}