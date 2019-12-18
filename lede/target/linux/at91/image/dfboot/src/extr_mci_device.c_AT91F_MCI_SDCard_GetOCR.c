#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int* MCI_RSPR; } ;
struct TYPE_7__ {TYPE_1__* pMCI_DeviceFeatures; } ;
struct TYPE_6__ {int Relative_Card_Address; } ;
typedef  TYPE_2__* AT91PS_MciDevice ;

/* Variables and functions */
 TYPE_5__* AT91C_BASE_MCI ; 
 unsigned int AT91C_CARD_POWER_UP_BUSY ; 
 unsigned int AT91C_CMD_SEND_OK ; 
 int AT91C_INIT_ERROR ; 
 int /*<<< orphan*/  AT91C_MMC_HOST_VOLTAGE_RANGE ; 
 int /*<<< orphan*/  AT91C_SDCARD_APP_OP_COND_CMD ; 
 unsigned int AT91F_MCI_SDCard_SendAppCommand (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int AT91F_MCI_SDCard_GetOCR (AT91PS_MciDevice pMCI_Device)
{
	unsigned int	response =0x0;

	// The RCA to be used for CMD55 in Idle state shall be the card's default RCA=0x0000.
	pMCI_Device->pMCI_DeviceFeatures->Relative_Card_Address = 0x0;
 	
 	while( (response & AT91C_CARD_POWER_UP_BUSY) != AT91C_CARD_POWER_UP_BUSY )
    {
    	response = AT91F_MCI_SDCard_SendAppCommand(pMCI_Device,
  										AT91C_SDCARD_APP_OP_COND_CMD,
  										AT91C_MMC_HOST_VOLTAGE_RANGE);
		if (response != AT91C_CMD_SEND_OK)
			return AT91C_INIT_ERROR;
		
		response = AT91C_BASE_MCI->MCI_RSPR[0];
	}
	
	return(AT91C_BASE_MCI->MCI_RSPR[0]);
}