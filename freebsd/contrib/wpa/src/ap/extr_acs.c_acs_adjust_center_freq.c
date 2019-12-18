#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hostapd_iface {TYPE_1__* conf; } ;
struct TYPE_3__ {int secondary_channel; scalar_t__ channel; } ;

/* Variables and functions */
#define  CHANWIDTH_160MHZ 130 
#define  CHANWIDTH_80MHZ 129 
#define  CHANWIDTH_USE_HT 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int hostapd_get_oper_chwidth (TYPE_1__*) ; 
 int /*<<< orphan*/  hostapd_set_oper_centr_freq_seg0_idx (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void acs_adjust_center_freq(struct hostapd_iface *iface)
{
	int offset;

	wpa_printf(MSG_DEBUG, "ACS: Adjusting VHT center frequency");

	switch (hostapd_get_oper_chwidth(iface->conf)) {
	case CHANWIDTH_USE_HT:
		offset = 2 * iface->conf->secondary_channel;
		break;
	case CHANWIDTH_80MHZ:
		offset = 6;
		break;
	case CHANWIDTH_160MHZ:
		offset = 14;
		break;
	default:
		/* TODO: How can this be calculated? Adjust
		 * acs_find_ideal_chan() */
		wpa_printf(MSG_INFO,
			   "ACS: Only VHT20/40/80/160 is supported now");
		return;
	}

	hostapd_set_oper_centr_freq_seg0_idx(iface->conf,
					     iface->conf->channel + offset);
}