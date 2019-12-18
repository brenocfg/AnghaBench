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
struct hostapd_channel_data {int flag; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
#define  HOSTAPD_CHAN_DFS_AVAILABLE 131 
 int HOSTAPD_CHAN_DFS_MASK ; 
#define  HOSTAPD_CHAN_DFS_UNAVAILABLE 130 
#define  HOSTAPD_CHAN_DFS_UNKNOWN 129 
#define  HOSTAPD_CHAN_DFS_USABLE 128 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static char * dfs_info(struct hostapd_channel_data *chan)
{
	static char info[256];
	char *state;

	switch (chan->flag & HOSTAPD_CHAN_DFS_MASK) {
	case HOSTAPD_CHAN_DFS_UNKNOWN:
		state = "unknown";
		break;
	case HOSTAPD_CHAN_DFS_USABLE:
		state = "usable";
		break;
	case HOSTAPD_CHAN_DFS_UNAVAILABLE:
		state = "unavailable";
		break;
	case HOSTAPD_CHAN_DFS_AVAILABLE:
		state = "available";
		break;
	default:
		return "";
	}
	os_snprintf(info, sizeof(info), " (DFS state = %s)", state);
	info[sizeof(info) - 1] = '\0';

	return info;
}