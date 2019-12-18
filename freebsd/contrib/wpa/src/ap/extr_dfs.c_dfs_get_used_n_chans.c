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
struct hostapd_iface {TYPE_1__* conf; } ;
struct TYPE_2__ {scalar_t__ ieee80211ax; scalar_t__ ieee80211ac; scalar_t__ secondary_channel; scalar_t__ ieee80211n; } ;

/* Variables and functions */
#define  CHANWIDTH_160MHZ 131 
#define  CHANWIDTH_80MHZ 130 
#define  CHANWIDTH_80P80MHZ 129 
#define  CHANWIDTH_USE_HT 128 
 int hostapd_get_oper_chwidth (TYPE_1__*) ; 

__attribute__((used)) static int dfs_get_used_n_chans(struct hostapd_iface *iface, int *seg1)
{
	int n_chans = 1;

	*seg1 = 0;

	if (iface->conf->ieee80211n && iface->conf->secondary_channel)
		n_chans = 2;

	if (iface->conf->ieee80211ac || iface->conf->ieee80211ax) {
		switch (hostapd_get_oper_chwidth(iface->conf)) {
		case CHANWIDTH_USE_HT:
			break;
		case CHANWIDTH_80MHZ:
			n_chans = 4;
			break;
		case CHANWIDTH_160MHZ:
			n_chans = 8;
			break;
		case CHANWIDTH_80P80MHZ:
			n_chans = 4;
			*seg1 = 4;
			break;
		default:
			break;
		}
	}

	return n_chans;
}