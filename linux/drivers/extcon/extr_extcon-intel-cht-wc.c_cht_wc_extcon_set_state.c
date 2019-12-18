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
struct cht_wc_extcon_data {int /*<<< orphan*/  edev; } ;

/* Variables and functions */
 unsigned int EXTCON_CHG_USB_SDP ; 
 unsigned int EXTCON_USB ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static void cht_wc_extcon_set_state(struct cht_wc_extcon_data *ext,
				    unsigned int cable, bool state)
{
	extcon_set_state_sync(ext->edev, cable, state);
	if (cable == EXTCON_CHG_USB_SDP)
		extcon_set_state_sync(ext->edev, EXTCON_USB, state);
}