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
struct wlan_iface {int /*<<< orphan*/  status; int /*<<< orphan*/  index; } ;
struct TYPE_3__ {scalar_t__ ifi_type; } ;
struct TYPE_4__ {TYPE_1__ ifmd_data; } ;
struct mibif {int /*<<< orphan*/  index; int /*<<< orphan*/  name; TYPE_2__ mib; } ;

/* Variables and functions */
 scalar_t__ IFM_IEEE80211 ; 
 scalar_t__ IFT_ETHER ; 
 int /*<<< orphan*/  RowStatus_active ; 
 scalar_t__ wlan_check_media (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_get_opmode (struct wlan_iface*) ; 
 struct wlan_iface* wlan_new_wif (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_update_interface (struct wlan_iface*) ; 

__attribute__((used)) static int
wlan_attach_newif(struct mibif *mif)
{
	struct wlan_iface *wif;

	if (mif->mib.ifmd_data.ifi_type != IFT_ETHER ||
	    wlan_check_media(mif->name) != IFM_IEEE80211)
		return (0);

	if ((wif = wlan_new_wif(mif->name)) == NULL)
		return (-1);

	(void)wlan_get_opmode(wif);
	wif->index = mif->index;
	wif->status = RowStatus_active;
	(void)wlan_update_interface(wif);

	return (0);
}