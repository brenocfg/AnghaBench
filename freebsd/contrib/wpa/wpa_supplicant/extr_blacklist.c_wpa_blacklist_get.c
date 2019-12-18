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
struct wpa_supplicant {struct wpa_blacklist* blacklist; } ;
struct wpa_blacklist {struct wpa_blacklist* next; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

struct wpa_blacklist * wpa_blacklist_get(struct wpa_supplicant *wpa_s,
					 const u8 *bssid)
{
	struct wpa_blacklist *e;

	if (wpa_s == NULL || bssid == NULL)
		return NULL;

	e = wpa_s->blacklist;
	while (e) {
		if (os_memcmp(e->bssid, bssid, ETH_ALEN) == 0)
			return e;
		e = e->next;
	}

	return NULL;
}