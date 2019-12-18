#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hostapd_config {TYPE_2__* wmm_ac_params; TYPE_1__* tx_queue; } ;
struct TYPE_4__ {int cwmin; int cwmax; } ;
struct TYPE_3__ {int cwmin; int cwmax; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int hostapd_config_check_cw(struct hostapd_config *conf, int queue)
{
	int tx_cwmin = conf->tx_queue[queue].cwmin;
	int tx_cwmax = conf->tx_queue[queue].cwmax;
	int ac_cwmin = conf->wmm_ac_params[queue].cwmin;
	int ac_cwmax = conf->wmm_ac_params[queue].cwmax;

	if (tx_cwmin > tx_cwmax) {
		wpa_printf(MSG_ERROR,
			   "Invalid TX queue cwMin/cwMax values. cwMin(%d) greater than cwMax(%d)",
			   tx_cwmin, tx_cwmax);
		return -1;
	}
	if (ac_cwmin > ac_cwmax) {
		wpa_printf(MSG_ERROR,
			   "Invalid WMM AC cwMin/cwMax values. cwMin(%d) greater than cwMax(%d)",
			   ac_cwmin, ac_cwmax);
		return -1;
	}
	return 0;
}