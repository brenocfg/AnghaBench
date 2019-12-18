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
struct sta_info {TYPE_2__* eapol_sm; } ;
struct hostapd_data {int dummy; } ;
struct TYPE_4__ {TYPE_1__* eap_if; } ;
struct TYPE_3__ {int /*<<< orphan*/  eapKeyAvailable; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  eapol_auth_step (TYPE_2__*) ; 

__attribute__((used)) static int ieee802_1x_sta_key_available(struct hostapd_data *hapd,
					struct sta_info *sta, void *ctx)
{
	if (sta->eapol_sm) {
		sta->eapol_sm->eap_if->eapKeyAvailable = TRUE;
		eapol_auth_step(sta->eapol_sm);
	}
	return 0;
}