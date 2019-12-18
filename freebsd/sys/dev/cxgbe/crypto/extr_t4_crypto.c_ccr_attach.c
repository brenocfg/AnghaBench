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
struct ccr_softc {int /*<<< orphan*/  iv_aad_buf; int /*<<< orphan*/  sg_iv_aad; void* sg_dsgl; void* sg_ulptx; void* sg_crp; int /*<<< orphan*/  lock; scalar_t__ tx_channel_id; TYPE_2__* adapter; scalar_t__ cid; int /*<<< orphan*/ * rxq; int /*<<< orphan*/ * txq; int /*<<< orphan*/  dev; } ;
struct ccr_session {int dummy; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/ * rxq; int /*<<< orphan*/ * ctrlq; } ;
struct TYPE_4__ {struct ccr_softc* ccr_softc; TYPE_1__ sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTOCAP_F_HARDWARE ; 
 int /*<<< orphan*/  CRYPTO_AES_128_NIST_GMAC ; 
 int /*<<< orphan*/  CRYPTO_AES_192_NIST_GMAC ; 
 int /*<<< orphan*/  CRYPTO_AES_256_NIST_GMAC ; 
 int /*<<< orphan*/  CRYPTO_AES_CBC ; 
 int /*<<< orphan*/  CRYPTO_AES_CCM_16 ; 
 int /*<<< orphan*/  CRYPTO_AES_CCM_CBC_MAC ; 
 int /*<<< orphan*/  CRYPTO_AES_ICM ; 
 int /*<<< orphan*/  CRYPTO_AES_NIST_GCM_16 ; 
 int /*<<< orphan*/  CRYPTO_AES_XTS ; 
 int /*<<< orphan*/  CRYPTO_SHA1 ; 
 int /*<<< orphan*/  CRYPTO_SHA1_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_224 ; 
 int /*<<< orphan*/  CRYPTO_SHA2_224_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_256 ; 
 int /*<<< orphan*/  CRYPTO_SHA2_256_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_384 ; 
 int /*<<< orphan*/  CRYPTO_SHA2_384_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_512 ; 
 int /*<<< orphan*/  CRYPTO_SHA2_512_HMAC ; 
 int ENXIO ; 
 int /*<<< orphan*/  MAX_AAD_LEN ; 
 int /*<<< orphan*/  MAX_RX_PHYS_DSGL_SGE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_CCR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TX_SGL_SEGS ; 
 int /*<<< orphan*/  ccr_sysctls (struct ccr_softc*) ; 
 scalar_t__ crypto_get_driverid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_register (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* sglist_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sglist_build (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ccr_attach(device_t dev)
{
	struct ccr_softc *sc;
	int32_t cid;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->adapter = device_get_softc(device_get_parent(dev));
	sc->txq = &sc->adapter->sge.ctrlq[0];
	sc->rxq = &sc->adapter->sge.rxq[0];
	cid = crypto_get_driverid(dev, sizeof(struct ccr_session),
	    CRYPTOCAP_F_HARDWARE);
	if (cid < 0) {
		device_printf(dev, "could not get crypto driver id\n");
		return (ENXIO);
	}
	sc->cid = cid;
	sc->adapter->ccr_softc = sc;

	/* XXX: TODO? */
	sc->tx_channel_id = 0;

	mtx_init(&sc->lock, "ccr", NULL, MTX_DEF);
	sc->sg_crp = sglist_alloc(TX_SGL_SEGS, M_WAITOK);
	sc->sg_ulptx = sglist_alloc(TX_SGL_SEGS, M_WAITOK);
	sc->sg_dsgl = sglist_alloc(MAX_RX_PHYS_DSGL_SGE, M_WAITOK);
	sc->iv_aad_buf = malloc(MAX_AAD_LEN, M_CCR, M_WAITOK);
	sc->sg_iv_aad = sglist_build(sc->iv_aad_buf, MAX_AAD_LEN, M_WAITOK);
	ccr_sysctls(sc);

	crypto_register(cid, CRYPTO_SHA1, 0, 0);
	crypto_register(cid, CRYPTO_SHA2_224, 0, 0);
	crypto_register(cid, CRYPTO_SHA2_256, 0, 0);
	crypto_register(cid, CRYPTO_SHA2_384, 0, 0);
	crypto_register(cid, CRYPTO_SHA2_512, 0, 0);
	crypto_register(cid, CRYPTO_SHA1_HMAC, 0, 0);
	crypto_register(cid, CRYPTO_SHA2_224_HMAC, 0, 0);
	crypto_register(cid, CRYPTO_SHA2_256_HMAC, 0, 0);
	crypto_register(cid, CRYPTO_SHA2_384_HMAC, 0, 0);
	crypto_register(cid, CRYPTO_SHA2_512_HMAC, 0, 0);
	crypto_register(cid, CRYPTO_AES_CBC, 0, 0);
	crypto_register(cid, CRYPTO_AES_ICM, 0, 0);
	crypto_register(cid, CRYPTO_AES_NIST_GCM_16, 0, 0);
	crypto_register(cid, CRYPTO_AES_128_NIST_GMAC, 0, 0);
	crypto_register(cid, CRYPTO_AES_192_NIST_GMAC, 0, 0);
	crypto_register(cid, CRYPTO_AES_256_NIST_GMAC, 0, 0);
	crypto_register(cid, CRYPTO_AES_XTS, 0, 0);
	crypto_register(cid, CRYPTO_AES_CCM_16, 0, 0);
	crypto_register(cid, CRYPTO_AES_CCM_CBC_MAC, 0, 0);
	return (0);
}