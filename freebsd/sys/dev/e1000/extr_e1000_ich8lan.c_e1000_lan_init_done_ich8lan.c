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
typedef  scalar_t__ u32 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ E1000_ICH8_LAN_INIT_TIMEOUT ; 
 scalar_t__ E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 scalar_t__ E1000_STATUS_LAN_INIT_DONE ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static void e1000_lan_init_done_ich8lan(struct e1000_hw *hw)
{
	u32 data, loop = E1000_ICH8_LAN_INIT_TIMEOUT;

	DEBUGFUNC("e1000_lan_init_done_ich8lan");

	/* Wait for basic configuration completes before proceeding */
	do {
		data = E1000_READ_REG(hw, E1000_STATUS);
		data &= E1000_STATUS_LAN_INIT_DONE;
		usec_delay(100);
	} while ((!data) && --loop);

	/* If basic configuration is incomplete before the above loop
	 * count reaches 0, loading the configuration from NVM will
	 * leave the PHY in a bad state possibly resulting in no link.
	 */
	if (loop == 0)
		DEBUGOUT("LAN_INIT_DONE not set, increase timeout\n");

	/* Clear the Init Done bit for the next init event */
	data = E1000_READ_REG(hw, E1000_STATUS);
	data &= ~E1000_STATUS_LAN_INIT_DONE;
	E1000_WRITE_REG(hw, E1000_STATUS, data);
}