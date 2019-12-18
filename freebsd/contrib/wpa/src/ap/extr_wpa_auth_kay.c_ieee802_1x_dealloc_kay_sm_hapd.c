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
struct hostapd_data {int /*<<< orphan*/ * kay; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee802_1x_kay_deinit (int /*<<< orphan*/ *) ; 

void ieee802_1x_dealloc_kay_sm_hapd(struct hostapd_data *hapd)
{
	if (!hapd->kay)
		return;

	ieee802_1x_kay_deinit(hapd->kay);
	hapd->kay = NULL;
}