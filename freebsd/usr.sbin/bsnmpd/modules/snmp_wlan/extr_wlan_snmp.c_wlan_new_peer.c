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
typedef  int /*<<< orphan*/  uint8_t ;
struct wlan_peer {int /*<<< orphan*/  pmac; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct wlan_peer*,int /*<<< orphan*/ ,int) ; 

struct wlan_peer *
wlan_new_peer(const uint8_t *pmac)
{
	struct wlan_peer *wip;

	if ((wip = (struct wlan_peer *)malloc(sizeof(*wip))) == NULL)
		return (NULL);

	memset(wip, 0, sizeof(struct wlan_peer));
	memcpy(wip->pmac, pmac, IEEE80211_ADDR_LEN);

	return (wip);
}