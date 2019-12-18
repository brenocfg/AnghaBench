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
struct wlan_scan_result {int dummy; } ;
struct wlan_iface {int /*<<< orphan*/  scanlist; } ;

/* Variables and functions */
 struct wlan_scan_result* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct wlan_scan_result*) ; 
 int /*<<< orphan*/  wsr ; 

__attribute__((used)) static void
wlan_scan_free_results(struct wlan_iface *wif)
{
	struct wlan_scan_result *sr;

	while ((sr = SLIST_FIRST(&wif->scanlist)) != NULL) {
		SLIST_REMOVE_HEAD(&wif->scanlist, wsr);
		free(sr);
	}

	SLIST_INIT(&wif->scanlist);
}