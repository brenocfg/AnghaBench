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
struct hostapd_neighbor_entry {scalar_t__ stationary; int /*<<< orphan*/  ssid; int /*<<< orphan*/ * bssid; int /*<<< orphan*/ * civic; int /*<<< orphan*/ * lci; int /*<<< orphan*/ * nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hostapd_neighbor_clear_entry(struct hostapd_neighbor_entry *nr)
{
	wpabuf_free(nr->nr);
	nr->nr = NULL;
	wpabuf_free(nr->lci);
	nr->lci = NULL;
	wpabuf_free(nr->civic);
	nr->civic = NULL;
	os_memset(nr->bssid, 0, sizeof(nr->bssid));
	os_memset(&nr->ssid, 0, sizeof(nr->ssid));
	nr->stationary = 0;
}