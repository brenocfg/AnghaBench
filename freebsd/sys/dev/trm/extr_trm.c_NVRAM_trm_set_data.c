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
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  PACB ;

/* Variables and functions */
 int /*<<< orphan*/  NVRAM_trm_wait_30us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVRAM_trm_write_cmd (int /*<<< orphan*/ ,int,int) ; 
 int NVR_BITIN ; 
 int NVR_BITOUT ; 
 int NVR_CLOCK ; 
 int NVR_SELECT ; 
 int /*<<< orphan*/  TRMREG_GEN_NVRAM ; 
 int trm_reg_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
NVRAM_trm_set_data(PACB pACB, u_int8_t bAddr, u_int8_t bData)
{
	int		i;
	u_int8_t	bSendData;
	/* 
	 * Send write command & address	
	 */
	
	NVRAM_trm_write_cmd(pACB, 0x05, bAddr);
	/* 
	 * Write data 
	 */
	for (i = 0; i < 8; i++, bData <<= 1) {
		bSendData = NVR_SELECT;
		if (bData & 0x80)
		  /* Start from bit 7	*/
			bSendData |= NVR_BITOUT;
		trm_reg_write8(bSendData , TRMREG_GEN_NVRAM);
		NVRAM_trm_wait_30us(pACB);
		trm_reg_write8((bSendData | NVR_CLOCK), TRMREG_GEN_NVRAM);
		NVRAM_trm_wait_30us(pACB);
	}
	trm_reg_write8(NVR_SELECT , TRMREG_GEN_NVRAM);
	NVRAM_trm_wait_30us(pACB);
	/*
	 * Disable chip select 
	 */
	trm_reg_write8(0 , TRMREG_GEN_NVRAM);
	NVRAM_trm_wait_30us(pACB);
	trm_reg_write8(NVR_SELECT ,TRMREG_GEN_NVRAM);
	NVRAM_trm_wait_30us(pACB);
	/* 
	 * Wait for write ready	
	 */
	while (1) {
		trm_reg_write8((NVR_SELECT | NVR_CLOCK), TRMREG_GEN_NVRAM);
		NVRAM_trm_wait_30us(pACB);
		trm_reg_write8(NVR_SELECT, TRMREG_GEN_NVRAM);
		NVRAM_trm_wait_30us(pACB);
		if (trm_reg_read8(TRMREG_GEN_NVRAM) & NVR_BITIN) {
			break;
		}
	}
	/* 
	 * Disable chip select 
	 */
	trm_reg_write8(0, TRMREG_GEN_NVRAM);
	return;
}