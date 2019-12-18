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
struct al_hal_eth_adapter {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ) ; 

int al_eth_adapter_reset(struct al_hal_eth_adapter *adapter)
{
	al_dbg("eth [%s]: reset controller's UDMA\n", adapter->name);

	return -EPERM;
}