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
struct wpa_supplicant {unsigned int mac_addr_rand_enable; int /*<<< orphan*/ * mac_addr_pno; int /*<<< orphan*/ * mac_addr_sched_scan; int /*<<< orphan*/ * mac_addr_scan; } ;

/* Variables and functions */
 unsigned int MAC_ADDR_RAND_ALL ; 
 unsigned int MAC_ADDR_RAND_PNO ; 
 unsigned int MAC_ADDR_RAND_SCAN ; 
 unsigned int MAC_ADDR_RAND_SCHED_SCAN ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

void wpas_mac_addr_rand_scan_clear(struct wpa_supplicant *wpa_s,
				    unsigned int type)
{
	type &= MAC_ADDR_RAND_ALL;
	wpa_s->mac_addr_rand_enable &= ~type;

	if (type & MAC_ADDR_RAND_SCAN) {
		os_free(wpa_s->mac_addr_scan);
		wpa_s->mac_addr_scan = NULL;
	}

	if (type & MAC_ADDR_RAND_SCHED_SCAN) {
		os_free(wpa_s->mac_addr_sched_scan);
		wpa_s->mac_addr_sched_scan = NULL;
	}

	if (type & MAC_ADDR_RAND_PNO) {
		os_free(wpa_s->mac_addr_pno);
		wpa_s->mac_addr_pno = NULL;
	}
}