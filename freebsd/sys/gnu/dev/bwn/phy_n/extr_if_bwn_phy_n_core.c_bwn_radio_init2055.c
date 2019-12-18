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
struct bwn_mac {scalar_t__ mac_status; } ;

/* Variables and functions */
 scalar_t__ BWN_BAND_5G ; 
 scalar_t__ BWN_MAC_STATUS_INITED ; 
 int /*<<< orphan*/  b2055_upload_inittab (struct bwn_mac*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_radio_init2055_post (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_radio_init2055_pre (struct bwn_mac*) ; 

__attribute__((used)) static void bwn_radio_init2055(struct bwn_mac *mac)
{
	bwn_radio_init2055_pre(mac);
	if (mac->mac_status < BWN_MAC_STATUS_INITED) {
		/* Follow wl, not specs. Do not force uploading all regs */
		b2055_upload_inittab(mac, 0, 0);
	} else {
		bool ghz5 = bwn_current_band(mac) == BWN_BAND_5G;
		b2055_upload_inittab(mac, ghz5, 0);
	}
	bwn_radio_init2055_post(mac);
}