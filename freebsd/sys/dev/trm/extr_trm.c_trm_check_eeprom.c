#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  void* u_int8_t ;
typedef  int u_int16_t ;
struct TYPE_5__ {int NvramSubClass; int NvramReserved; int NvramCheckSum; scalar_t__ NvramTarget; void** NvramDeviceID; void** NvramVendorID; void** NvramSubSysID; void** NvramSubVendorID; } ;
typedef  TYPE_1__* PNVRAMTYPE ;
typedef  int /*<<< orphan*/  PACB ;

/* Variables and functions */
 int /*<<< orphan*/  NVRAM_trm_read_all (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVRAM_trm_write_all (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int PCI_Device_ID_TRM_S1040 ; 
 int PCI_Vendor_ID_TEKRAM ; 

__attribute__((used)) static void
trm_check_eeprom(PNVRAMTYPE pEEpromBuf, PACB pACB)
{
	u_int16_t	*wpEeprom = (u_int16_t *) pEEpromBuf;
	u_int16_t	wAddr, wCheckSum;
	u_long	dAddr, *dpEeprom;

	NVRAM_trm_read_all(pEEpromBuf,pACB);
	wCheckSum = 0;
	for (wAddr = 0, wpEeprom = (u_int16_t *) pEEpromBuf;
	    wAddr < 64; wAddr++, wpEeprom++) {
		wCheckSum += *wpEeprom;
	}
	if (wCheckSum != 0x1234) {
	  /* 
   	   * Checksum error, load default	
	   */
		pEEpromBuf->NvramSubVendorID[0]	= (u_int8_t) PCI_Vendor_ID_TEKRAM;
		pEEpromBuf->NvramSubVendorID[1]	=
		  (u_int8_t) (PCI_Vendor_ID_TEKRAM >> 8);
		pEEpromBuf->NvramSubSysID[0] = (u_int8_t) PCI_Device_ID_TRM_S1040;
		pEEpromBuf->NvramSubSysID[1] = 
		  (u_int8_t) (PCI_Device_ID_TRM_S1040 >> 8);
		pEEpromBuf->NvramSubClass = 0x00;
		pEEpromBuf->NvramVendorID[0] = (u_int8_t) PCI_Vendor_ID_TEKRAM;
		pEEpromBuf->NvramVendorID[1] =
		  (u_int8_t) (PCI_Vendor_ID_TEKRAM >> 8);
		pEEpromBuf->NvramDeviceID[0] = (u_int8_t) PCI_Device_ID_TRM_S1040;
		pEEpromBuf->NvramDeviceID[1] = 
		  (u_int8_t) (PCI_Device_ID_TRM_S1040 >> 8);
		pEEpromBuf->NvramReserved = 0x00;

		for (dAddr = 0, dpEeprom = (u_long *) pEEpromBuf->NvramTarget;
		    dAddr < 16; dAddr++, dpEeprom++) {
			*dpEeprom = 0x00000077;
			/* NvmTarCfg3,NvmTarCfg2,NvmTarPeriod,NvmTarCfg0 */
		}

		*dpEeprom++ = 0x04000F07;
		/* NvramMaxTag,NvramDelayTime,NvramChannelCfg,NvramScsiId */
		*dpEeprom++ = 0x00000015;
		/* NvramReserved1,NvramBootLun,NvramBootTarget,NvramReserved0 */
		for (dAddr = 0; dAddr < 12; dAddr++, dpEeprom++)
			*dpEeprom = 0x00;
		pEEpromBuf->NvramCheckSum = 0x00;
		for (wAddr = 0, wCheckSum = 0, wpEeprom = (u_int16_t *) pEEpromBuf;
		    wAddr < 63; wAddr++, wpEeprom++)
	      		wCheckSum += *wpEeprom;
		*wpEeprom = 0x1234 - wCheckSum;
		NVRAM_trm_write_all(pEEpromBuf,pACB);
	}
	return;
}