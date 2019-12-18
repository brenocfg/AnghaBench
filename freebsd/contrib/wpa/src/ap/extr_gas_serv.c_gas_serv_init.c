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
struct hostapd_data {struct hostapd_data* public_action_cb2_ctx; int /*<<< orphan*/  public_action_cb2; } ;

/* Variables and functions */
 int /*<<< orphan*/  gas_serv_rx_public_action ; 

int gas_serv_init(struct hostapd_data *hapd)
{
	hapd->public_action_cb2 = gas_serv_rx_public_action;
	hapd->public_action_cb2_ctx = hapd;
	return 0;
}