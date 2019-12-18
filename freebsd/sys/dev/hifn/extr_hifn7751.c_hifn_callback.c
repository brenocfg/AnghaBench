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
typedef  int /*<<< orphan*/  u_int8_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
struct mbuf {int m_len; TYPE_1__ m_pkthdr; struct mbuf* m_next; } ;
struct hifn_softc {int sc_dstk; int sc_dstu; scalar_t__ sc_dmamap; int /*<<< orphan*/  sc_dmat; struct hifn_dma* sc_dma; } ;
struct hifn_dma {TYPE_2__* dstr; int /*<<< orphan*/ * slop; } ;
struct hifn_command {scalar_t__ src_map; scalar_t__ dst_map; int src_mapsize; scalar_t__ sloplen; size_t slopidx; int base_masks; TYPE_3__* session; scalar_t__ dst_mapsize; struct mbuf* src_m; struct mbuf* dst_m; struct cryptop* crp; } ;
struct cryptop {int crp_flags; int /*<<< orphan*/ * crp_buf; struct cryptodesc* crp_desc; } ;
struct cryptodesc {scalar_t__ crd_alg; scalar_t__ crd_inject; struct cryptodesc* crd_next; scalar_t__ crd_len; scalar_t__ crd_skip; } ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_8__ {int /*<<< orphan*/  hst_obytes; } ;
struct TYPE_7__ {int hs_mlen; int /*<<< orphan*/  hs_iv; } ;
struct TYPE_6__ {int l; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 scalar_t__ CRYPTO_3DES_CBC ; 
 scalar_t__ CRYPTO_AES_CBC ; 
 scalar_t__ CRYPTO_DES_CBC ; 
 int CRYPTO_F_IMBUF ; 
 scalar_t__ CRYPTO_MD5 ; 
 scalar_t__ CRYPTO_MD5_HMAC ; 
 scalar_t__ CRYPTO_SHA1 ; 
 scalar_t__ CRYPTO_SHA1_HMAC ; 
 int HIFN_AES_IV_LENGTH ; 
 int HIFN_BASE_CMD_CRYPT ; 
 int HIFN_BASE_CMD_DECODE ; 
 int HIFN_D_DST_RSIZE ; 
 int /*<<< orphan*/  HIFN_D_VALID ; 
 int HIFN_IV_LENGTH ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  crypto_copyback (int,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_copydata (int,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_done (struct cryptop*) ; 
 int /*<<< orphan*/  free (struct hifn_command*,int /*<<< orphan*/ ) ; 
 TYPE_4__ hifnstats ; 
 int htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
hifn_callback(struct hifn_softc *sc, struct hifn_command *cmd, u_int8_t *macbuf)
{
	struct hifn_dma *dma = sc->sc_dma;
	struct cryptop *crp = cmd->crp;
	struct cryptodesc *crd;
	struct mbuf *m;
	int totlen, i, u, ivlen;

	if (cmd->src_map == cmd->dst_map) {
		bus_dmamap_sync(sc->sc_dmat, cmd->src_map,
		    BUS_DMASYNC_POSTWRITE | BUS_DMASYNC_POSTREAD);
	} else {
		bus_dmamap_sync(sc->sc_dmat, cmd->src_map,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_sync(sc->sc_dmat, cmd->dst_map,
		    BUS_DMASYNC_POSTREAD);
	}

	if (crp->crp_flags & CRYPTO_F_IMBUF) {
		if (cmd->src_m != cmd->dst_m) {
			crp->crp_buf = (caddr_t)cmd->dst_m;
			totlen = cmd->src_mapsize;
			for (m = cmd->dst_m; m != NULL; m = m->m_next) {
				if (totlen < m->m_len) {
					m->m_len = totlen;
					totlen = 0;
				} else
					totlen -= m->m_len;
			}
			cmd->dst_m->m_pkthdr.len = cmd->src_m->m_pkthdr.len;
			m_freem(cmd->src_m);
		}
	}

	if (cmd->sloplen != 0) {
		crypto_copyback(crp->crp_flags, crp->crp_buf,
		    cmd->src_mapsize - cmd->sloplen, cmd->sloplen,
		    (caddr_t)&dma->slop[cmd->slopidx]);
	}

	i = sc->sc_dstk; u = sc->sc_dstu;
	while (u != 0) {
		if (i == HIFN_D_DST_RSIZE)
			i = 0;
		bus_dmamap_sync(sc->sc_dmat, sc->sc_dmamap,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
		if (dma->dstr[i].l & htole32(HIFN_D_VALID)) {
			bus_dmamap_sync(sc->sc_dmat, sc->sc_dmamap,
			    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
			break;
		}
		i++, u--;
	}
	sc->sc_dstk = i; sc->sc_dstu = u;

	hifnstats.hst_obytes += cmd->dst_mapsize;

	if ((cmd->base_masks & (HIFN_BASE_CMD_CRYPT | HIFN_BASE_CMD_DECODE)) ==
	    HIFN_BASE_CMD_CRYPT) {
		for (crd = crp->crp_desc; crd; crd = crd->crd_next) {
			if (crd->crd_alg != CRYPTO_DES_CBC &&
			    crd->crd_alg != CRYPTO_3DES_CBC &&
			    crd->crd_alg != CRYPTO_AES_CBC)
				continue;
			ivlen = ((crd->crd_alg == CRYPTO_AES_CBC) ?
				HIFN_AES_IV_LENGTH : HIFN_IV_LENGTH);
			crypto_copydata(crp->crp_flags, crp->crp_buf,
			    crd->crd_skip + crd->crd_len - ivlen, ivlen,
			    cmd->session->hs_iv);
			break;
		}
	}

	if (macbuf != NULL) {
		for (crd = crp->crp_desc; crd; crd = crd->crd_next) {
                        int len;

			if (crd->crd_alg != CRYPTO_MD5 &&
			    crd->crd_alg != CRYPTO_SHA1 &&
			    crd->crd_alg != CRYPTO_MD5_HMAC &&
			    crd->crd_alg != CRYPTO_SHA1_HMAC) {
				continue;
			}
			len = cmd->session->hs_mlen;
			crypto_copyback(crp->crp_flags, crp->crp_buf,
			    crd->crd_inject, len, macbuf);
			break;
		}
	}

	if (cmd->src_map != cmd->dst_map) {
		bus_dmamap_unload(sc->sc_dmat, cmd->dst_map);
		bus_dmamap_destroy(sc->sc_dmat, cmd->dst_map);
	}
	bus_dmamap_unload(sc->sc_dmat, cmd->src_map);
	bus_dmamap_destroy(sc->sc_dmat, cmd->src_map);
	free(cmd, M_DEVBUF);
	crypto_done(crp);
}