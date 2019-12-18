#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int u_int ;
struct ubsec_softc {int sc_flags; int /*<<< orphan*/  sc_mcr2lock; int /*<<< orphan*/  sc_queue2; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_13__ {int dma_size; int dma_paddr; int /*<<< orphan*/ * dma_tag; struct ubsec_q2_modexp* dma_vaddr; } ;
struct TYPE_14__ {int q_type; TYPE_5__ q_ctx; TYPE_5__ q_mcr; } ;
struct ubsec_q2_modexp {int me_modbits; int me_shiftbits; int me_normbits; TYPE_5__ me_epb; TYPE_5__ me_C; TYPE_5__ me_E; TYPE_5__ me_M; TYPE_8__ me_q; void* me_N_len; void* me_E_len; void* me_op; void* me_len; struct ubsec_q2_modexp* me_N; struct cryptkop* me_krp; } ;
struct ubsec_pktbuf {void* pb_len; scalar_t__ pb_next; void* pb_addr; } ;
struct TYPE_10__ {void* pb_len; void* pb_addr; scalar_t__ pb_next; } ;
struct TYPE_9__ {void* pb_next; void* pb_len; void* pb_addr; } ;
struct ubsec_mcr {TYPE_2__ mcr_opktbuf; TYPE_1__ mcr_ipktbuf; scalar_t__ mcr_pktlen; scalar_t__ mcr_reserved; void* mcr_cmdctxp; scalar_t__ mcr_flags; void* mcr_pkts; } ;
struct ubsec_ctx_modexp {int me_modbits; int me_shiftbits; int me_normbits; TYPE_5__ me_epb; TYPE_5__ me_C; TYPE_5__ me_E; TYPE_5__ me_M; TYPE_8__ me_q; void* me_N_len; void* me_E_len; void* me_op; void* me_len; struct ubsec_ctx_modexp* me_N; struct cryptkop* me_krp; } ;
struct ubsec_ctx_keyop {int dummy; } ;
struct cryptkop {size_t krp_iparams; int krp_status; TYPE_4__* krp_param; } ;
struct TYPE_12__ {int crp_nbits; int /*<<< orphan*/  crp_p; } ;
struct TYPE_11__ {int /*<<< orphan*/  hst_modexp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int E2BIG ; 
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  SIMPLEQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int UBS_CTXOP_MODEXP ; 
 int UBS_FLAGS_BIGKEY ; 
 size_t UBS_MODEXP_PAR_E ; 
 size_t UBS_MODEXP_PAR_M ; 
 size_t UBS_MODEXP_PAR_N ; 
 int /*<<< orphan*/  bzero (struct ubsec_q2_modexp*,int) ; 
 int /*<<< orphan*/  crypto_kdone (struct cryptkop*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ubsec_q2_modexp*,int /*<<< orphan*/ ) ; 
 void* htole16 (int) ; 
 void* htole32 (int) ; 
 int letoh32 (void*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  q_next ; 
 scalar_t__ ubsec_debug ; 
 int /*<<< orphan*/  ubsec_dma_free (struct ubsec_softc*,TYPE_5__*) ; 
 scalar_t__ ubsec_dma_malloc (struct ubsec_softc*,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubsec_dma_sync (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubsec_dump_ctx2 (struct ubsec_ctx_keyop*) ; 
 int /*<<< orphan*/  ubsec_dump_mcr (struct ubsec_mcr*) ; 
 int /*<<< orphan*/  ubsec_dump_pb (struct ubsec_pktbuf*) ; 
 int /*<<< orphan*/  ubsec_feed2 (struct ubsec_softc*) ; 
 int /*<<< orphan*/  ubsec_kshift_r (int,int /*<<< orphan*/ ,int,struct ubsec_q2_modexp*,int) ; 
 int ubsec_ksigbits (TYPE_4__*) ; 
 TYPE_3__ ubsecstats ; 

__attribute__((used)) static int
ubsec_kprocess_modexp_sw(struct ubsec_softc *sc, struct cryptkop *krp, int hint)
{
	struct ubsec_q2_modexp *me;
	struct ubsec_mcr *mcr;
	struct ubsec_ctx_modexp *ctx;
	struct ubsec_pktbuf *epb;
	int err = 0;
	u_int nbits, normbits, mbits, shiftbits, ebits;

	me = (struct ubsec_q2_modexp *)malloc(sizeof *me, M_DEVBUF, M_NOWAIT);
	if (me == NULL) {
		err = ENOMEM;
		goto errout;
	}
	bzero(me, sizeof *me);
	me->me_krp = krp;
	me->me_q.q_type = UBS_CTXOP_MODEXP;

	nbits = ubsec_ksigbits(&krp->krp_param[UBS_MODEXP_PAR_N]);
	if (nbits <= 512)
		normbits = 512;
	else if (nbits <= 768)
		normbits = 768;
	else if (nbits <= 1024)
		normbits = 1024;
	else if (sc->sc_flags & UBS_FLAGS_BIGKEY && nbits <= 1536)
		normbits = 1536;
	else if (sc->sc_flags & UBS_FLAGS_BIGKEY && nbits <= 2048)
		normbits = 2048;
	else {
		err = E2BIG;
		goto errout;
	}

	shiftbits = normbits - nbits;

	me->me_modbits = nbits;
	me->me_shiftbits = shiftbits;
	me->me_normbits = normbits;

	/* Sanity check: result bits must be >= true modulus bits. */
	if (krp->krp_param[krp->krp_iparams].crp_nbits < nbits) {
		err = ERANGE;
		goto errout;
	}

	if (ubsec_dma_malloc(sc, sizeof(struct ubsec_mcr),
	    &me->me_q.q_mcr, 0)) {
		err = ENOMEM;
		goto errout;
	}
	mcr = (struct ubsec_mcr *)me->me_q.q_mcr.dma_vaddr;

	if (ubsec_dma_malloc(sc, sizeof(struct ubsec_ctx_modexp),
	    &me->me_q.q_ctx, 0)) {
		err = ENOMEM;
		goto errout;
	}

	mbits = ubsec_ksigbits(&krp->krp_param[UBS_MODEXP_PAR_M]);
	if (mbits > nbits) {
		err = E2BIG;
		goto errout;
	}
	if (ubsec_dma_malloc(sc, normbits / 8, &me->me_M, 0)) {
		err = ENOMEM;
		goto errout;
	}
	ubsec_kshift_r(shiftbits,
	    krp->krp_param[UBS_MODEXP_PAR_M].crp_p, mbits,
	    me->me_M.dma_vaddr, normbits);

	if (ubsec_dma_malloc(sc, normbits / 8, &me->me_C, 0)) {
		err = ENOMEM;
		goto errout;
	}
	bzero(me->me_C.dma_vaddr, me->me_C.dma_size);

	ebits = ubsec_ksigbits(&krp->krp_param[UBS_MODEXP_PAR_E]);
	if (ebits > nbits) {
		err = E2BIG;
		goto errout;
	}
	if (ubsec_dma_malloc(sc, normbits / 8, &me->me_E, 0)) {
		err = ENOMEM;
		goto errout;
	}
	ubsec_kshift_r(shiftbits,
	    krp->krp_param[UBS_MODEXP_PAR_E].crp_p, ebits,
	    me->me_E.dma_vaddr, normbits);

	if (ubsec_dma_malloc(sc, sizeof(struct ubsec_pktbuf),
	    &me->me_epb, 0)) {
		err = ENOMEM;
		goto errout;
	}
	epb = (struct ubsec_pktbuf *)me->me_epb.dma_vaddr;
	epb->pb_addr = htole32(me->me_E.dma_paddr);
	epb->pb_next = 0;
	epb->pb_len = htole32(normbits / 8);

#ifdef UBSEC_DEBUG
	if (ubsec_debug) {
		printf("Epb ");
		ubsec_dump_pb(epb);
	}
#endif

	mcr->mcr_pkts = htole16(1);
	mcr->mcr_flags = 0;
	mcr->mcr_cmdctxp = htole32(me->me_q.q_ctx.dma_paddr);
	mcr->mcr_reserved = 0;
	mcr->mcr_pktlen = 0;

	mcr->mcr_ipktbuf.pb_addr = htole32(me->me_M.dma_paddr);
	mcr->mcr_ipktbuf.pb_len = htole32(normbits / 8);
	mcr->mcr_ipktbuf.pb_next = htole32(me->me_epb.dma_paddr);

	mcr->mcr_opktbuf.pb_addr = htole32(me->me_C.dma_paddr);
	mcr->mcr_opktbuf.pb_next = 0;
	mcr->mcr_opktbuf.pb_len = htole32(normbits / 8);

#ifdef DIAGNOSTIC
	/* Misaligned output buffer will hang the chip. */
	if ((letoh32(mcr->mcr_opktbuf.pb_addr) & 3) != 0)
		panic("%s: modexp invalid addr 0x%x\n",
		    device_get_nameunit(sc->sc_dev),
		    letoh32(mcr->mcr_opktbuf.pb_addr));
	if ((letoh32(mcr->mcr_opktbuf.pb_len) & 3) != 0)
		panic("%s: modexp invalid len 0x%x\n",
		    device_get_nameunit(sc->sc_dev),
		    letoh32(mcr->mcr_opktbuf.pb_len));
#endif

	ctx = (struct ubsec_ctx_modexp *)me->me_q.q_ctx.dma_vaddr;
	bzero(ctx, sizeof(*ctx));
	ubsec_kshift_r(shiftbits,
	    krp->krp_param[UBS_MODEXP_PAR_N].crp_p, nbits,
	    ctx->me_N, normbits);
	ctx->me_len = htole16((normbits / 8) + (4 * sizeof(u_int16_t)));
	ctx->me_op = htole16(UBS_CTXOP_MODEXP);
	ctx->me_E_len = htole16(nbits);
	ctx->me_N_len = htole16(nbits);

#ifdef UBSEC_DEBUG
	if (ubsec_debug) {
		ubsec_dump_mcr(mcr);
		ubsec_dump_ctx2((struct ubsec_ctx_keyop *)ctx);
	}
#endif

	/*
	 * ubsec_feed2 will sync mcr and ctx, we just need to sync
	 * everything else.
	 */
	ubsec_dma_sync(&me->me_M, BUS_DMASYNC_PREWRITE);
	ubsec_dma_sync(&me->me_E, BUS_DMASYNC_PREWRITE);
	ubsec_dma_sync(&me->me_C, BUS_DMASYNC_PREREAD);
	ubsec_dma_sync(&me->me_epb, BUS_DMASYNC_PREWRITE);

	/* Enqueue and we're done... */
	mtx_lock(&sc->sc_mcr2lock);
	SIMPLEQ_INSERT_TAIL(&sc->sc_queue2, &me->me_q, q_next);
	ubsec_feed2(sc);
	ubsecstats.hst_modexp++;
	mtx_unlock(&sc->sc_mcr2lock);

	return (0);

errout:
	if (me != NULL) {
		if (me->me_q.q_mcr.dma_tag != NULL)
			ubsec_dma_free(sc, &me->me_q.q_mcr);
		if (me->me_q.q_ctx.dma_tag != NULL) {
			bzero(me->me_q.q_ctx.dma_vaddr, me->me_q.q_ctx.dma_size);
			ubsec_dma_free(sc, &me->me_q.q_ctx);
		}
		if (me->me_M.dma_tag != NULL) {
			bzero(me->me_M.dma_vaddr, me->me_M.dma_size);
			ubsec_dma_free(sc, &me->me_M);
		}
		if (me->me_E.dma_tag != NULL) {
			bzero(me->me_E.dma_vaddr, me->me_E.dma_size);
			ubsec_dma_free(sc, &me->me_E);
		}
		if (me->me_C.dma_tag != NULL) {
			bzero(me->me_C.dma_vaddr, me->me_C.dma_size);
			ubsec_dma_free(sc, &me->me_C);
		}
		if (me->me_epb.dma_tag != NULL)
			ubsec_dma_free(sc, &me->me_epb);
		free(me, M_DEVBUF);
	}
	krp->krp_status = err;
	crypto_kdone(krp);
	return (0);
}