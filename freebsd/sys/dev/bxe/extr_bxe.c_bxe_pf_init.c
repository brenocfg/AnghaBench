#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_11__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct event_ring_data {int /*<<< orphan*/  sb_id; int /*<<< orphan*/  index_id; int /*<<< orphan*/  producer; TYPE_5__ base_addr; TYPE_1__ member_0; } ;
struct cmng_struct_per_port {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  paddr; } ;
struct TYPE_10__ {scalar_t__ pmf; } ;
struct TYPE_9__ {int /*<<< orphan*/  line_speed; } ;
struct TYPE_8__ {int /*<<< orphan*/  paddr; } ;
struct bxe_softc {int /*<<< orphan*/  eq_prod; TYPE_6__ eq_dma; int /*<<< orphan*/  cmng; TYPE_4__ port; TYPE_3__ link_vars; int /*<<< orphan*/  spq_prod_idx; TYPE_2__ spq_dma; int /*<<< orphan*/  ifp; } ;
struct bxe_func_init_params {int func_flgs; int pf_id; int func_id; int /*<<< orphan*/  spq_prod; int /*<<< orphan*/  spq_map; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int BXE_IGU_STAS_MSG_PF_CNT ; 
 int BXE_IGU_STAS_MSG_VF_CNT ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_MODE_4_PORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  DEF_SB_ID ; 
 int FUNC_FLG_LEADING ; 
 int FUNC_FLG_SPQ ; 
 int FUNC_FLG_STATS ; 
 int FUNC_FLG_TPA ; 
 int /*<<< orphan*/  HC_SP_INDEX_EQ_CONS ; 
 int IFCAP_LRO ; 
 scalar_t__ IGU_REG_STATISTIC_NUM_MESSAGE_SENT ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int SC_FUNC (struct bxe_softc*) ; 
 int /*<<< orphan*/  SC_PORT (struct bxe_softc*) ; 
 int SC_VN (struct bxe_softc*) ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_cmng_fns_init (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_func_init (struct bxe_softc*,struct bxe_func_init_params*) ; 
 int /*<<< orphan*/  bxe_get_cmng_fns_mode (struct bxe_softc*) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  storm_memset_cmng (struct bxe_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storm_memset_eq_data (struct bxe_softc*,struct event_ring_data*,int) ; 

__attribute__((used)) static void
bxe_pf_init(struct bxe_softc *sc)
{
    struct bxe_func_init_params func_init = { 0 };
    struct event_ring_data eq_data = { { 0 } };
    uint16_t flags;

    if (!CHIP_IS_E1x(sc)) {
        /* reset IGU PF statistics: MSIX + ATTN */
        /* PF */
        REG_WR(sc,
               (IGU_REG_STATISTIC_NUM_MESSAGE_SENT +
                (BXE_IGU_STAS_MSG_VF_CNT * 4) +
                ((CHIP_IS_MODE_4_PORT(sc) ? SC_FUNC(sc) : SC_VN(sc)) * 4)),
               0);
        /* ATTN */
        REG_WR(sc,
               (IGU_REG_STATISTIC_NUM_MESSAGE_SENT +
                (BXE_IGU_STAS_MSG_VF_CNT * 4) +
                (BXE_IGU_STAS_MSG_PF_CNT * 4) +
                ((CHIP_IS_MODE_4_PORT(sc) ? SC_FUNC(sc) : SC_VN(sc)) * 4)),
               0);
    }

    /* function setup flags */
    flags = (FUNC_FLG_STATS | FUNC_FLG_LEADING | FUNC_FLG_SPQ);

    /*
     * This flag is relevant for E1x only.
     * E2 doesn't have a TPA configuration in a function level.
     */
    flags |= (if_getcapenable(sc->ifp) & IFCAP_LRO) ? FUNC_FLG_TPA : 0;

    func_init.func_flgs = flags;
    func_init.pf_id     = SC_FUNC(sc);
    func_init.func_id   = SC_FUNC(sc);
    func_init.spq_map   = sc->spq_dma.paddr;
    func_init.spq_prod  = sc->spq_prod_idx;

    bxe_func_init(sc, &func_init);

    memset(&sc->cmng, 0, sizeof(struct cmng_struct_per_port));

    /*
     * Congestion management values depend on the link rate.
     * There is no active link so initial link rate is set to 10Gbps.
     * When the link comes up the congestion management values are
     * re-calculated according to the actual link rate.
     */
    sc->link_vars.line_speed = SPEED_10000;
    bxe_cmng_fns_init(sc, TRUE, bxe_get_cmng_fns_mode(sc));

    /* Only the PMF sets the HW */
    if (sc->port.pmf) {
        storm_memset_cmng(sc, &sc->cmng, SC_PORT(sc));
    }

    /* init Event Queue - PCI bus guarantees correct endainity */
    eq_data.base_addr.hi = U64_HI(sc->eq_dma.paddr);
    eq_data.base_addr.lo = U64_LO(sc->eq_dma.paddr);
    eq_data.producer     = sc->eq_prod;
    eq_data.index_id     = HC_SP_INDEX_EQ_CONS;
    eq_data.sb_id        = DEF_SB_ID;
    storm_memset_eq_data(sc, &eq_data, SC_FUNC(sc));
}