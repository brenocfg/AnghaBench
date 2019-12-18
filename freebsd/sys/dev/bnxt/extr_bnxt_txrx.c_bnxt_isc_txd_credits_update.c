#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct tx_cmpl {size_t flags_type; int opaque; int /*<<< orphan*/  errors_v; } ;
struct bnxt_softc {int /*<<< orphan*/  dev; struct bnxt_cp_ring* tx_cp_rings; } ;
struct TYPE_3__ {scalar_t__ vaddr; } ;
struct bnxt_cp_ring {size_t cons; int v_bit; TYPE_1__ ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_CP_IDX_DISABLE_DB (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  CMPL_PREFETCH_NEXT (struct bnxt_cp_ring*,size_t) ; 
 int /*<<< orphan*/  CMP_VALID (struct tx_cmpl*,int) ; 
 int /*<<< orphan*/  NEXT_CP_CONS_V (TYPE_1__*,size_t,int) ; 
 size_t TX_CMPL_ERRORS_BUFFER_ERROR_MASK ; 
 size_t TX_CMPL_ERRORS_BUFFER_ERROR_SFT ; 
 size_t TX_CMPL_TYPE_MASK ; 
#define  TX_CMPL_TYPE_TX_L2 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 size_t le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnxt_isc_txd_credits_update(void *sc, uint16_t txqid, bool clear)
{
	struct bnxt_softc *softc = (struct bnxt_softc *)sc;
	struct bnxt_cp_ring *cpr = &softc->tx_cp_rings[txqid];
	struct tx_cmpl *cmpl = (struct tx_cmpl *)cpr->ring.vaddr;
	int avail = 0;
	uint32_t cons = cpr->cons;
	bool v_bit = cpr->v_bit;
	bool last_v_bit;
	uint32_t last_cons;
	uint16_t type;
	uint16_t err;

	for (;;) {
		last_cons = cons;
		last_v_bit = v_bit;
		NEXT_CP_CONS_V(&cpr->ring, cons, v_bit);
		CMPL_PREFETCH_NEXT(cpr, cons);

		if (!CMP_VALID(&cmpl[cons], v_bit))
			goto done;

		type = cmpl[cons].flags_type & TX_CMPL_TYPE_MASK;
		switch (type) {
		case TX_CMPL_TYPE_TX_L2:
			err = (le16toh(cmpl[cons].errors_v) &
			    TX_CMPL_ERRORS_BUFFER_ERROR_MASK) >>
			    TX_CMPL_ERRORS_BUFFER_ERROR_SFT;
			if (err)
				device_printf(softc->dev,
				    "TX completion error %u\n", err);
			/* No need to byte-swap the opaque value */
			avail += cmpl[cons].opaque >> 24;
			/*
			 * If we're not clearing, iflib only cares if there's
			 * at least one buffer.  Don't scan the whole ring in
			 * this case.
			 */
			if (!clear)
				goto done;
			break;
		default:
			if (type & 1) {
				NEXT_CP_CONS_V(&cpr->ring, cons, v_bit);
				if (!CMP_VALID(&cmpl[cons], v_bit))
					goto done;
			}
			device_printf(softc->dev,
			    "Unhandled TX completion type %u\n", type);
			break;
		}
	}
done:

	if (clear && avail) {
		cpr->cons = last_cons;
		cpr->v_bit = last_v_bit;
		BNXT_CP_IDX_DISABLE_DB(&cpr->ring, cpr->cons);
	}

	return avail;
}