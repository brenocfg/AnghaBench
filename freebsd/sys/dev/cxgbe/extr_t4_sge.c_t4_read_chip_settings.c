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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sw_zone_info {int size; int head_hwidx; int tail_hwidx; int /*<<< orphan*/  type; int /*<<< orphan*/  zone; } ;
struct sge_params {int sge_control; scalar_t__ page_shift; int* sge_fl_buffer_size; int pad_boundary; } ;
struct sge {int safe_hwidx1; int safe_hwidx2; struct hw_buf_info* hw_buf_info; struct sw_zone_info* sw_zone_info; } ;
struct hw_buf_info {int size; int zidx; int next; } ;
struct TYPE_2__ {int /*<<< orphan*/  b_wnd; int /*<<< orphan*/  a_wnd; int /*<<< orphan*/  mtus; struct sge_params sge; } ;
struct adapter {int flags; TYPE_1__ params; int /*<<< orphan*/  dev; struct sge sge; } ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_PARA_REG5 ; 
 int /*<<< orphan*/  A_ULP_RX_CTL ; 
 int /*<<< orphan*/  A_ULP_RX_TDDP_PSZ ; 
 int BUF_PACKING_OK ; 
 int CL_METADATA_SIZE ; 
 int EINVAL ; 
 int F_REARMDDPOFFSET ; 
 int F_RESETDDPOFFSET ; 
 int F_RXPKTCPLMODE ; 
 int F_TDDPTAGTCB ; 
 int IS_VF ; 
#define  MCLBYTES 131 
#define  MJUM16BYTES 130 
#define  MJUM9BYTES 129 
#define  MJUMPAGESIZE 128 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_INDICATESIZE ; 
 scalar_t__ PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ RX_COPY_THRESHOLD ; 
 int SGE_FLBUF_SIZES ; 
 int SW_ZONE_SIZES ; 
 int V_HPZ0 (int /*<<< orphan*/ ) ; 
 int V_HPZ1 (int) ; 
 int V_HPZ2 (int) ; 
 int V_HPZ3 (int) ; 
 int V_INDICATESIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fl_pad ; 
 scalar_t__ hwsz_ok (struct adapter*,int) ; 
 int /*<<< orphan*/  m_gettype (int) ; 
 int /*<<< orphan*/  m_getzone (int) ; 
 int /*<<< orphan*/  min (scalar_t__,int /*<<< orphan*/ ) ; 
 int nitems (struct hw_buf_info*) ; 
 int powerof2 (int) ; 
 int safest_rx_cluster ; 
 int /*<<< orphan*/  t4_init_tp_params (struct adapter*,int) ; 
 int /*<<< orphan*/  t4_load_mtus (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_mtu_tbl (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

int
t4_read_chip_settings(struct adapter *sc)
{
	struct sge *s = &sc->sge;
	struct sge_params *sp = &sc->params.sge;
	int i, j, n, rc = 0;
	uint32_t m, v, r;
	uint16_t indsz = min(RX_COPY_THRESHOLD - 1, M_INDICATESIZE);
	static int sw_buf_sizes[] = {	/* Sorted by size */
		MCLBYTES,
#if MJUMPAGESIZE != MCLBYTES
		MJUMPAGESIZE,
#endif
		MJUM9BYTES,
		MJUM16BYTES
	};
	struct sw_zone_info *swz, *safe_swz;
	struct hw_buf_info *hwb;

	m = F_RXPKTCPLMODE;
	v = F_RXPKTCPLMODE;
	r = sc->params.sge.sge_control;
	if ((r & m) != v) {
		device_printf(sc->dev, "invalid SGE_CONTROL(0x%x)\n", r);
		rc = EINVAL;
	}

	/*
	 * If this changes then every single use of PAGE_SHIFT in the driver
	 * needs to be carefully reviewed for PAGE_SHIFT vs sp->page_shift.
	 */
	if (sp->page_shift != PAGE_SHIFT) {
		device_printf(sc->dev, "invalid SGE_HOST_PAGE_SIZE(0x%x)\n", r);
		rc = EINVAL;
	}

	/* Filter out unusable hw buffer sizes entirely (mark with -2). */
	hwb = &s->hw_buf_info[0];
	for (i = 0; i < nitems(s->hw_buf_info); i++, hwb++) {
		r = sc->params.sge.sge_fl_buffer_size[i];
		hwb->size = r;
		hwb->zidx = hwsz_ok(sc, r) ? -1 : -2;
		hwb->next = -1;
	}

	/*
	 * Create a sorted list in decreasing order of hw buffer sizes (and so
	 * increasing order of spare area) for each software zone.
	 *
	 * If padding is enabled then the start and end of the buffer must align
	 * to the pad boundary; if packing is enabled then they must align with
	 * the pack boundary as well.  Allocations from the cluster zones are
	 * aligned to min(size, 4K), so the buffer starts at that alignment and
	 * ends at hwb->size alignment.  If mbuf inlining is allowed the
	 * starting alignment will be reduced to MSIZE and the driver will
	 * exercise appropriate caution when deciding on the best buffer layout
	 * to use.
	 */
	n = 0;	/* no usable buffer size to begin with */
	swz = &s->sw_zone_info[0];
	safe_swz = NULL;
	for (i = 0; i < SW_ZONE_SIZES; i++, swz++) {
		int8_t head = -1, tail = -1;

		swz->size = sw_buf_sizes[i];
		swz->zone = m_getzone(swz->size);
		swz->type = m_gettype(swz->size);

		if (swz->size < PAGE_SIZE) {
			MPASS(powerof2(swz->size));
			if (fl_pad && (swz->size % sp->pad_boundary != 0))
				continue;
		}

		if (swz->size == safest_rx_cluster)
			safe_swz = swz;

		hwb = &s->hw_buf_info[0];
		for (j = 0; j < SGE_FLBUF_SIZES; j++, hwb++) {
			if (hwb->zidx != -1 || hwb->size > swz->size)
				continue;
#ifdef INVARIANTS
			if (fl_pad)
				MPASS(hwb->size % sp->pad_boundary == 0);
#endif
			hwb->zidx = i;
			if (head == -1)
				head = tail = j;
			else if (hwb->size < s->hw_buf_info[tail].size) {
				s->hw_buf_info[tail].next = j;
				tail = j;
			} else {
				int8_t *cur;
				struct hw_buf_info *t;

				for (cur = &head; *cur != -1; cur = &t->next) {
					t = &s->hw_buf_info[*cur];
					if (hwb->size == t->size) {
						hwb->zidx = -2;
						break;
					}
					if (hwb->size > t->size) {
						hwb->next = *cur;
						*cur = j;
						break;
					}
				}
			}
		}
		swz->head_hwidx = head;
		swz->tail_hwidx = tail;

		if (tail != -1) {
			n++;
			if (swz->size - s->hw_buf_info[tail].size >=
			    CL_METADATA_SIZE)
				sc->flags |= BUF_PACKING_OK;
		}
	}
	if (n == 0) {
		device_printf(sc->dev, "no usable SGE FL buffer size.\n");
		rc = EINVAL;
	}

	s->safe_hwidx1 = -1;
	s->safe_hwidx2 = -1;
	if (safe_swz != NULL) {
		s->safe_hwidx1 = safe_swz->head_hwidx;
		for (i = safe_swz->head_hwidx; i != -1; i = hwb->next) {
			int spare;

			hwb = &s->hw_buf_info[i];
#ifdef INVARIANTS
			if (fl_pad)
				MPASS(hwb->size % sp->pad_boundary == 0);
#endif
			spare = safe_swz->size - hwb->size;
			if (spare >= CL_METADATA_SIZE) {
				s->safe_hwidx2 = i;
				break;
			}
		}
	}

	if (sc->flags & IS_VF)
		return (0);

	v = V_HPZ0(0) | V_HPZ1(2) | V_HPZ2(4) | V_HPZ3(6);
	r = t4_read_reg(sc, A_ULP_RX_TDDP_PSZ);
	if (r != v) {
		device_printf(sc->dev, "invalid ULP_RX_TDDP_PSZ(0x%x)\n", r);
		rc = EINVAL;
	}

	m = v = F_TDDPTAGTCB;
	r = t4_read_reg(sc, A_ULP_RX_CTL);
	if ((r & m) != v) {
		device_printf(sc->dev, "invalid ULP_RX_CTL(0x%x)\n", r);
		rc = EINVAL;
	}

	m = V_INDICATESIZE(M_INDICATESIZE) | F_REARMDDPOFFSET |
	    F_RESETDDPOFFSET;
	v = V_INDICATESIZE(indsz) | F_REARMDDPOFFSET | F_RESETDDPOFFSET;
	r = t4_read_reg(sc, A_TP_PARA_REG5);
	if ((r & m) != v) {
		device_printf(sc->dev, "invalid TP_PARA_REG5(0x%x)\n", r);
		rc = EINVAL;
	}

	t4_init_tp_params(sc, 1);

	t4_read_mtu_tbl(sc, sc->params.mtus, NULL);
	t4_load_mtus(sc, sc->params.mtus, sc->params.a_wnd, sc->params.b_wnd);

	return (rc);
}