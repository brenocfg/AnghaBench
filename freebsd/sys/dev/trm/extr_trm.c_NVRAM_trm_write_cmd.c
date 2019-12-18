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
 int NVR_BITOUT ; 
 int NVR_CLOCK ; 
 int NVR_SELECT ; 
 int /*<<< orphan*/  TRMREG_GEN_NVRAM ; 
 int /*<<< orphan*/  trm_reg_write8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
NVRAM_trm_write_cmd(PACB pACB, u_int8_t bCmd, u_int8_t bAddr)
{
	int		i;
	u_int8_t	bSendData;
					
    	for (i = 0; i < 3; i++, bCmd <<= 1) {
	  /* 
   	   * Program SB+OP code		
   	   */
     		bSendData = NVR_SELECT;
		if (bCmd & 0x04)	
			bSendData |= NVR_BITOUT;
		/* start from bit 2 */
		trm_reg_write8(bSendData, TRMREG_GEN_NVRAM);
		NVRAM_trm_wait_30us(pACB);
		trm_reg_write8((bSendData | NVR_CLOCK), TRMREG_GEN_NVRAM);
		NVRAM_trm_wait_30us(pACB);
	}	
	for (i = 0; i < 7; i++, bAddr <<= 1) {
	  /* 
	   * Program address		
	   */
		bSendData = NVR_SELECT;
		if (bAddr & 0x40)	
		  /* Start from bit 6	*/
			bSendData |= NVR_BITOUT;
		trm_reg_write8(bSendData , TRMREG_GEN_NVRAM);
		NVRAM_trm_wait_30us(pACB);
		trm_reg_write8((bSendData | NVR_CLOCK), TRMREG_GEN_NVRAM);
		NVRAM_trm_wait_30us(pACB);
	}
	trm_reg_write8(NVR_SELECT, TRMREG_GEN_NVRAM);
	NVRAM_trm_wait_30us(pACB);
}