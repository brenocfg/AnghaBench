#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  size_t u_int16_t ;
struct TYPE_6__ {int Config; } ;
struct TYPE_5__ {int NvramChannelCfg; int NvramScsiId; } ;
typedef  TYPE_1__* PNVRAMTYPE ;
typedef  TYPE_2__* PACB ;

/* Variables and functions */
 int BLOCKRST ; 
 int DMA_ENHANCE ; 
 size_t DO_RSTMODULE ; 
 int EN_SCSIINTR ; 
 int HCC_AUTOTERM ; 
 int HCC_PARITY ; 
 int HCC_SCSI_RESET ; 
 int HCC_WIDE_CARD ; 
 int INITIATOR ; 
 int NAC_POWERON_SCSI_RESET ; 
 int PARITYCHECK ; 
 int PHASELATCH ; 
 int SEL_TIMEOUT ; 
 int /*<<< orphan*/  TRMREG_DMA_CONFIG ; 
 int /*<<< orphan*/  TRMREG_DMA_INTEN ; 
 int /*<<< orphan*/  TRMREG_GEN_CONTROL ; 
 int /*<<< orphan*/  TRMREG_GEN_STATUS ; 
 int /*<<< orphan*/  TRMREG_SCSI_CONFIG0 ; 
 int /*<<< orphan*/  TRMREG_SCSI_CONFIG1 ; 
 int /*<<< orphan*/  TRMREG_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRMREG_SCSI_HOSTID ; 
 int /*<<< orphan*/  TRMREG_SCSI_INTEN ; 
 int /*<<< orphan*/  TRMREG_SCSI_INTSTATUS ; 
 int /*<<< orphan*/  TRMREG_SCSI_OFFSET ; 
 int /*<<< orphan*/  TRMREG_SCSI_TIMEOUT ; 
 int WIDESCSI ; 
 TYPE_1__* trm_eepromBuf ; 
 int trm_reg_read16 (int /*<<< orphan*/ ) ; 
 int trm_reg_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write16 (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
trm_initAdapter(PACB pACB, u_int16_t unit)
{
	PNVRAMTYPE	pEEpromBuf;
	u_int16_t	wval;
	u_int8_t	bval;

	pEEpromBuf = &trm_eepromBuf[unit];

	/* 250ms selection timeout */
	trm_reg_write8(SEL_TIMEOUT, TRMREG_SCSI_TIMEOUT);
	/* Mask all the interrupt */
	trm_reg_write8(0x00, TRMREG_DMA_INTEN);    
	trm_reg_write8(0x00, TRMREG_SCSI_INTEN);     
	/* Reset SCSI module */
	trm_reg_write16(DO_RSTMODULE, TRMREG_SCSI_CONTROL); 
	/* program configuration 0 */
	pACB->Config = HCC_AUTOTERM | HCC_PARITY;
	if (trm_reg_read8(TRMREG_GEN_STATUS) & WIDESCSI)
		pACB->Config |= HCC_WIDE_CARD;
	if (pEEpromBuf->NvramChannelCfg & NAC_POWERON_SCSI_RESET)
		pACB->Config |= HCC_SCSI_RESET;
	if (pACB->Config & HCC_PARITY)
		bval = PHASELATCH | INITIATOR | BLOCKRST | PARITYCHECK;
	else
		bval = PHASELATCH | INITIATOR | BLOCKRST ;
	trm_reg_write8(bval,TRMREG_SCSI_CONFIG0); 
	/* program configuration 1 */
	trm_reg_write8(0x13, TRMREG_SCSI_CONFIG1); 
	/* program Host ID */
	bval = pEEpromBuf->NvramScsiId;
	trm_reg_write8(bval, TRMREG_SCSI_HOSTID); 
	/* set ansynchronous transfer */
	trm_reg_write8(0x00, TRMREG_SCSI_OFFSET); 
	/* Trun LED control off*/
	wval = trm_reg_read16(TRMREG_GEN_CONTROL) & 0x7F;
	trm_reg_write16(wval, TRMREG_GEN_CONTROL); 
	/* DMA config */
	wval = trm_reg_read16(TRMREG_DMA_CONFIG) | DMA_ENHANCE;
	trm_reg_write16(wval, TRMREG_DMA_CONFIG); 
	/* Clear pending interrupt status */
	trm_reg_read8(TRMREG_SCSI_INTSTATUS);
	/* Enable SCSI interrupt */
	trm_reg_write8(0x7F, TRMREG_SCSI_INTEN); 
	trm_reg_write8(EN_SCSIINTR, TRMREG_DMA_INTEN); 
	return (0);
}