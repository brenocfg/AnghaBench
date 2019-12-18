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
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ offset; int period; scalar_t__ width; } ;
struct ncr53c9x_tinfo {TYPE_1__ curr; } ;
struct ncr53c9x_softc {int sc_cfg3; int sc_features; int sc_cfg3_fscsi; scalar_t__ sc_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ MSG_EXT_WDTR_BUS_8_BIT ; 
 int NCRAMDCFG3_FSCSI ; 
 int NCRFASCFG3_EWIDE ; 
 int /*<<< orphan*/  NCR_CFG3 ; 
 int NCR_F_FASTSCSI ; 
 int NCR_F_HASCFG3 ; 
 int /*<<< orphan*/  NCR_LOCK_ASSERT (struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCR_SYNCOFF ; 
 int /*<<< orphan*/  NCR_SYNCTP ; 
 scalar_t__ NCR_VARIANT_AM53C974 ; 
 scalar_t__ NCR_VARIANT_FAS366 ; 
 int /*<<< orphan*/  NCR_WRITE_REG (struct ncr53c9x_softc*,int /*<<< orphan*/ ,int) ; 
 int ncr53c9x_stp2cpb (struct ncr53c9x_softc*,int) ; 

__attribute__((used)) static inline void
ncr53c9x_setsync(struct ncr53c9x_softc *sc, struct ncr53c9x_tinfo *ti)
{
	uint8_t cfg3, syncoff, synctp;

	NCR_LOCK_ASSERT(sc, MA_OWNED);

	cfg3 = sc->sc_cfg3;
	if (ti->curr.offset != 0) {
		syncoff = ti->curr.offset;
		synctp = ncr53c9x_stp2cpb(sc, ti->curr.period);
		if (sc->sc_features & NCR_F_FASTSCSI) {
			/*
			 * If the period is 200ns or less (ti->period <= 50),
			 * put the chip in Fast SCSI mode.
			 */
			if (ti->curr.period <= 50)
				/*
				 * There are (at least) 4 variations of the
				 * configuration 3 register.  The drive attach
				 * routine sets the appropriate bit to put the
				 * chip into Fast SCSI mode so that it doesn't
				 * have to be figured out here each time.
				 */
				cfg3 |= sc->sc_cfg3_fscsi;
		}

		/*
		 * Am53c974 requires different SYNCTP values when the
		 * FSCSI bit is off.
		 */
		if (sc->sc_rev == NCR_VARIANT_AM53C974 &&
		    (cfg3 & NCRAMDCFG3_FSCSI) == 0)
			synctp--;
	} else {
		syncoff = 0;
		synctp = 0;
	}

	if (ti->curr.width != MSG_EXT_WDTR_BUS_8_BIT) {
		if (sc->sc_rev == NCR_VARIANT_FAS366)
			cfg3 |= NCRFASCFG3_EWIDE;
	}

	if (sc->sc_features & NCR_F_HASCFG3)
		NCR_WRITE_REG(sc, NCR_CFG3, cfg3);

	NCR_WRITE_REG(sc, NCR_SYNCOFF, syncoff);
	NCR_WRITE_REG(sc, NCR_SYNCTP, synctp);
}