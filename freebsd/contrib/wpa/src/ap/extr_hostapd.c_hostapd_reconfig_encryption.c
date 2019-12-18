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
struct hostapd_data {TYPE_1__* conf; scalar_t__ wpa_auth; } ;
struct TYPE_2__ {int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_set_privacy (struct hostapd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_setup_encryption (int /*<<< orphan*/ ,struct hostapd_data*) ; 

void hostapd_reconfig_encryption(struct hostapd_data *hapd)
{
	if (hapd->wpa_auth)
		return;

	hostapd_set_privacy(hapd, 0);
	hostapd_setup_encryption(hapd->conf->iface, hapd);
}