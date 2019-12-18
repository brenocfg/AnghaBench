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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum chan_width { ____Placeholder_chan_width } chan_width ;

/* Variables and functions */
 int CHANWIDTH_160MHZ ; 
 int CHANWIDTH_80MHZ ; 
 int CHANWIDTH_80P80MHZ ; 
 int CHANWIDTH_USE_HT ; 
#define  CHAN_WIDTH_160 134 
#define  CHAN_WIDTH_20 133 
#define  CHAN_WIDTH_20_NOHT 132 
#define  CHAN_WIDTH_40 131 
#define  CHAN_WIDTH_80 130 
#define  CHAN_WIDTH_80P80 129 
#define  CHAN_WIDTH_UNKNOWN 128 
 int /*<<< orphan*/  MSG_WARNING ; 
 scalar_t__ NUM_HOSTAPD_MODES ; 
 scalar_t__ ieee80211_freq_to_channel_ext (unsigned int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned int,int,int) ; 

int ieee80211_chaninfo_to_channel(unsigned int freq, enum chan_width chanwidth,
				  int sec_channel, u8 *op_class, u8 *channel)
{
	int vht = CHAN_WIDTH_UNKNOWN;

	switch (chanwidth) {
	case CHAN_WIDTH_UNKNOWN:
	case CHAN_WIDTH_20_NOHT:
	case CHAN_WIDTH_20:
	case CHAN_WIDTH_40:
		vht = CHANWIDTH_USE_HT;
		break;
	case CHAN_WIDTH_80:
		vht = CHANWIDTH_80MHZ;
		break;
	case CHAN_WIDTH_80P80:
		vht = CHANWIDTH_80P80MHZ;
		break;
	case CHAN_WIDTH_160:
		vht = CHANWIDTH_160MHZ;
		break;
	}

	if (ieee80211_freq_to_channel_ext(freq, sec_channel, vht, op_class,
					  channel) == NUM_HOSTAPD_MODES) {
		wpa_printf(MSG_WARNING,
			   "Cannot determine operating class and channel (freq=%u chanwidth=%d sec_channel=%d)",
			   freq, chanwidth, sec_channel);
		return -1;
	}

	return 0;
}