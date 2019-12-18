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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct TYPE_2__ {int wc_en; } ;
struct adapter {scalar_t__ rdmacaps; int /*<<< orphan*/  doorbells; TYPE_1__ iwt; int /*<<< orphan*/  dev; int /*<<< orphan*/ * udbs_res; scalar_t__ udbs_base; int /*<<< orphan*/  udbs_rid; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SGE_STAT_CFG ; 
 scalar_t__ CHELSIO_T5 ; 
 int /*<<< orphan*/  DOORBELL_UDB ; 
 int /*<<< orphan*/  DOORBELL_UDBWC ; 
 int /*<<< orphan*/  DOORBELL_WCWR ; 
 int ENXIO ; 
 int /*<<< orphan*/  PAT_WRITE_COMBINING ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int V_STATMODE (int /*<<< orphan*/ ) ; 
 int V_STATSOURCE_T5 (int) ; 
 int V_T6_STATMODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ chip_id (struct adapter*) ; 
 int /*<<< orphan*/  clrbit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ is_t4 (struct adapter*) ; 
 scalar_t__ is_t5 (struct adapter*) ; 
 scalar_t__ isset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pmap_change_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ *) ; 
 scalar_t__ rman_get_virtual (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ t5_write_combine ; 

int
t4_map_bar_2(struct adapter *sc)
{

	/*
	 * T4: only iWARP driver uses the userspace doorbells.  There is no need
	 * to map it if RDMA is disabled.
	 */
	if (is_t4(sc) && sc->rdmacaps == 0)
		return (0);

	sc->udbs_rid = PCIR_BAR(2);
	sc->udbs_res = bus_alloc_resource_any(sc->dev, SYS_RES_MEMORY,
	    &sc->udbs_rid, RF_ACTIVE);
	if (sc->udbs_res == NULL) {
		device_printf(sc->dev, "cannot map doorbell BAR.\n");
		return (ENXIO);
	}
	sc->udbs_base = rman_get_virtual(sc->udbs_res);

	if (chip_id(sc) >= CHELSIO_T5) {
		setbit(&sc->doorbells, DOORBELL_UDB);
#if defined(__i386__) || defined(__amd64__)
		if (t5_write_combine) {
			int rc, mode;

			/*
			 * Enable write combining on BAR2.  This is the
			 * userspace doorbell BAR and is split into 128B
			 * (UDBS_SEG_SIZE) doorbell regions, each associated
			 * with an egress queue.  The first 64B has the doorbell
			 * and the second 64B can be used to submit a tx work
			 * request with an implicit doorbell.
			 */

			rc = pmap_change_attr((vm_offset_t)sc->udbs_base,
			    rman_get_size(sc->udbs_res), PAT_WRITE_COMBINING);
			if (rc == 0) {
				clrbit(&sc->doorbells, DOORBELL_UDB);
				setbit(&sc->doorbells, DOORBELL_WCWR);
				setbit(&sc->doorbells, DOORBELL_UDBWC);
			} else {
				device_printf(sc->dev,
				    "couldn't enable write combining: %d\n",
				    rc);
			}

			mode = is_t5(sc) ? V_STATMODE(0) : V_T6_STATMODE(0);
			t4_write_reg(sc, A_SGE_STAT_CFG,
			    V_STATSOURCE_T5(7) | mode);
		}
#endif
	}
	sc->iwt.wc_en = isset(&sc->doorbells, DOORBELL_UDBWC) ? 1 : 0;

	return (0);
}