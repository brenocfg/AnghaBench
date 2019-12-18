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
struct wpa_ssid {scalar_t__ priority; struct wpa_ssid* pnext; } ;
struct wpa_config {int num_prio; struct wpa_ssid** pssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memmove (struct wpa_ssid**,struct wpa_ssid**,int) ; 
 struct wpa_ssid** os_realloc_array (struct wpa_ssid**,int,int) ; 

int wpa_config_add_prio_network(struct wpa_config *config,
				struct wpa_ssid *ssid)
{
	int prio;
	struct wpa_ssid *prev, **nlist;

	/*
	 * Add to an existing priority list if one is available for the
	 * configured priority level for this network.
	 */
	for (prio = 0; prio < config->num_prio; prio++) {
		prev = config->pssid[prio];
		if (prev->priority == ssid->priority) {
			while (prev->pnext)
				prev = prev->pnext;
			prev->pnext = ssid;
			return 0;
		}
	}

	/* First network for this priority - add a new priority list */
	nlist = os_realloc_array(config->pssid, config->num_prio + 1,
				 sizeof(struct wpa_ssid *));
	if (nlist == NULL)
		return -1;

	for (prio = 0; prio < config->num_prio; prio++) {
		if (nlist[prio]->priority < ssid->priority) {
			os_memmove(&nlist[prio + 1], &nlist[prio],
				   (config->num_prio - prio) *
				   sizeof(struct wpa_ssid *));
			break;
		}
	}

	nlist[prio] = ssid;
	config->num_prio++;
	config->pssid = nlist;

	return 0;
}