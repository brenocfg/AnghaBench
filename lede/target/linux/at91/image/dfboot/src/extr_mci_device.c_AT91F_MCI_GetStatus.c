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
struct TYPE_2__ {int* MCI_RSPR; } ;
typedef  int /*<<< orphan*/  AT91PS_MciDevice ;

/* Variables and functions */
 TYPE_1__* AT91C_BASE_MCI ; 
 int AT91C_CMD_SEND_ERROR ; 
 scalar_t__ AT91C_CMD_SEND_OK ; 
 int /*<<< orphan*/  AT91C_SEND_STATUS_CMD ; 
 scalar_t__ AT91F_MCI_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int AT91F_MCI_GetStatus(AT91PS_MciDevice pMCI_Device,unsigned int relative_card_address)
{
	if (AT91F_MCI_SendCommand(pMCI_Device,
								AT91C_SEND_STATUS_CMD,
								relative_card_address <<16) == AT91C_CMD_SEND_OK)
    	return (AT91C_BASE_MCI->MCI_RSPR[0]);

    return AT91C_CMD_SEND_ERROR;
}