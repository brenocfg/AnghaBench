#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct macio_chip {int dummy; } ;

/* Variables and functions */
 int HEATHROW_FCR ; 
 int HRW_BMAC_IO_ENABLE ; 
 int HRW_BMAC_RESET ; 
 int /*<<< orphan*/  HRW_GPIO_MODEM_RESET ; 
 int HRW_IDE0_RESET_N ; 
 int HRW_IOBUS_ENABLE ; 
 int HRW_SCC_ENABLE ; 
 int /*<<< orphan*/  HRW_SCC_TRANS_EN_N ; 
 int HRW_SOUND_CLK_ENABLE ; 
 int /*<<< orphan*/  HRW_SOUND_POWER_N ; 
 int /*<<< orphan*/  MACIO_BIC (int,int) ; 
 int /*<<< orphan*/  MACIO_BIS (int,int /*<<< orphan*/ ) ; 
 void* MACIO_IN32 (int) ; 
 int MACIO_IN8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_OUT8 (int /*<<< orphan*/ ,int) ; 
 int OH_SCCA_IO ; 
 int OH_SCCB_IO ; 
 int /*<<< orphan*/  dbdma_save (struct macio_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_alt_dbdma ; 
 int /*<<< orphan*/  save_dbdma ; 
 void** save_fcr ; 
 void* save_mbcr ; 

__attribute__((used)) static void heathrow_sleep(struct macio_chip *macio, int secondary)
{
	if (secondary) {
		dbdma_save(macio, save_alt_dbdma);
		save_fcr[2] = MACIO_IN32(0x38);
		save_fcr[3] = MACIO_IN32(0x3c);
	} else {
		dbdma_save(macio, save_dbdma);
		save_fcr[0] = MACIO_IN32(0x38);
		save_fcr[1] = MACIO_IN32(0x3c);
		save_mbcr = MACIO_IN32(0x34);
		/* Make sure sound is shut down */
		MACIO_BIS(HEATHROW_FCR, HRW_SOUND_POWER_N);
		MACIO_BIC(HEATHROW_FCR, HRW_SOUND_CLK_ENABLE);
		/* This seems to be necessary as well or the fan
		 * keeps coming up and battery drains fast */
		MACIO_BIC(HEATHROW_FCR, HRW_IOBUS_ENABLE);
		MACIO_BIC(HEATHROW_FCR, HRW_IDE0_RESET_N);
		/* Make sure eth is down even if module or sleep
		 * won't work properly */
		MACIO_BIC(HEATHROW_FCR, HRW_BMAC_IO_ENABLE | HRW_BMAC_RESET);
	}
	/* Make sure modem is shut down */
	MACIO_OUT8(HRW_GPIO_MODEM_RESET,
		MACIO_IN8(HRW_GPIO_MODEM_RESET) & ~1);
	MACIO_BIS(HEATHROW_FCR, HRW_SCC_TRANS_EN_N);
	MACIO_BIC(HEATHROW_FCR, OH_SCCA_IO|OH_SCCB_IO|HRW_SCC_ENABLE);

	/* Let things settle */
	(void)MACIO_IN32(HEATHROW_FCR);
}