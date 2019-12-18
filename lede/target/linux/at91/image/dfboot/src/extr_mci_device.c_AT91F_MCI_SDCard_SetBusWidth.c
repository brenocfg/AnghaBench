#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* pMCI_DeviceDesc; TYPE_1__* pMCI_DeviceFeatures; } ;
struct TYPE_9__ {scalar_t__ SDCard_bus_width; } ;
struct TYPE_8__ {int Relative_Card_Address; } ;
typedef  TYPE_3__* AT91PS_MciDevice ;

/* Variables and functions */
 char AT91C_BUS_WIDTH_1BIT ; 
 char AT91C_BUS_WIDTH_4BITS ; 
 int AT91C_CMD_SEND_ERROR ; 
 scalar_t__ AT91C_CMD_SEND_OK ; 
 scalar_t__ AT91C_MCI_SCDBUS ; 
 int /*<<< orphan*/  AT91C_SDCARD_SET_BUS_WIDTH_CMD ; 
 int /*<<< orphan*/  AT91C_SEL_DESEL_CARD_CMD ; 
 int volatile AT91C_SR_READY_FOR_DATA ; 
 int AT91F_MCI_GetStatus (TYPE_3__*,int) ; 
 scalar_t__ AT91F_MCI_SDCard_SendAppCommand (TYPE_3__*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  AT91F_MCI_SendCommand (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

int AT91F_MCI_SDCard_SetBusWidth(AT91PS_MciDevice pMCI_Device)
{
	volatile int	ret_value;
	char			bus_width;

	do
	{
		ret_value =AT91F_MCI_GetStatus(pMCI_Device,pMCI_Device->pMCI_DeviceFeatures->Relative_Card_Address);
	}
	while((ret_value > 0) && ((ret_value & AT91C_SR_READY_FOR_DATA) == 0));

	// Select Card
    AT91F_MCI_SendCommand(pMCI_Device,
    						AT91C_SEL_DESEL_CARD_CMD,
    						(pMCI_Device->pMCI_DeviceFeatures->Relative_Card_Address)<<16);

	// Set bus width for Sdcard
	if(pMCI_Device->pMCI_DeviceDesc->SDCard_bus_width == AT91C_MCI_SCDBUS)
		 	bus_width = AT91C_BUS_WIDTH_4BITS;
	else	bus_width = AT91C_BUS_WIDTH_1BIT;

	if (AT91F_MCI_SDCard_SendAppCommand(pMCI_Device,AT91C_SDCARD_SET_BUS_WIDTH_CMD,bus_width) != AT91C_CMD_SEND_OK)
		return AT91C_CMD_SEND_ERROR;

	return AT91C_CMD_SEND_OK;
}