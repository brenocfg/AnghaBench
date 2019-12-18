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
struct hostapd_data {int dpp_allowed_roles; int dpp_init_done; } ;

/* Variables and functions */
 int DPP_CAPAB_CONFIGURATOR ; 
 int DPP_CAPAB_ENROLLEE ; 
 int hostapd_dpp_add_controllers (struct hostapd_data*) ; 

int hostapd_dpp_init(struct hostapd_data *hapd)
{
	hapd->dpp_allowed_roles = DPP_CAPAB_CONFIGURATOR | DPP_CAPAB_ENROLLEE;
	hapd->dpp_init_done = 1;
	return hostapd_dpp_add_controllers(hapd);
}