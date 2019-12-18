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
typedef  scalar_t__ PNVRAMTYPE ;
typedef  int /*<<< orphan*/  PACB ;

/* Variables and functions */
 int EN_EEPROM ; 
 int /*<<< orphan*/  NVRAM_trm_set_data (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  NVRAM_trm_wait_30us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVRAM_trm_write_cmd (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  TRMREG_GEN_CONTROL ; 
 int /*<<< orphan*/  TRMREG_GEN_NVRAM ; 
 int trm_reg_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
NVRAM_trm_write_all(PNVRAMTYPE pEEpromBuf,PACB pACB)
{
	u_int8_t	*bpEeprom = (u_int8_t *) pEEpromBuf;
	u_int8_t	bAddr;

	/* Enable SEEPROM */
	trm_reg_write8((trm_reg_read8(TRMREG_GEN_CONTROL) | EN_EEPROM),
	    TRMREG_GEN_CONTROL);
	/*
	 * Write enable
	 */
	NVRAM_trm_write_cmd(pACB, 0x04, 0xFF);
	trm_reg_write8(0, TRMREG_GEN_NVRAM);
	NVRAM_trm_wait_30us(pACB);
	for (bAddr = 0; bAddr < 128; bAddr++, bpEeprom++) { 
		NVRAM_trm_set_data(pACB, bAddr, *bpEeprom);
	}
	/* 
	 * Write disable
	 */
	NVRAM_trm_write_cmd(pACB, 0x04, 0x00);
	trm_reg_write8(0 , TRMREG_GEN_NVRAM);
	NVRAM_trm_wait_30us(pACB);
	/* Disable SEEPROM */
	trm_reg_write8((trm_reg_read8(TRMREG_GEN_CONTROL) & ~EN_EEPROM),
	    TRMREG_GEN_CONTROL);
	return;
}