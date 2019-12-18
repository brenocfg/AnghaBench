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
struct wlan_iface {int /*<<< orphan*/  mode; int /*<<< orphan*/  state; int /*<<< orphan*/  status; int /*<<< orphan*/  wname; scalar_t__ internal; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  RowStatus_notReady ; 
 int /*<<< orphan*/  WlanIfaceOperatingModeType_station ; 
 int /*<<< orphan*/  free (struct wlan_iface*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct wlan_iface*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlanIfaceState_down ; 
 scalar_t__ wlan_add_wif (struct wlan_iface*) ; 
 struct wlan_iface* wlan_first_interface () ; 
 struct wlan_iface* wlan_next_interface (struct wlan_iface*) ; 

__attribute__((used)) static struct wlan_iface *
wlan_new_wif(char *wname)
{
	struct wlan_iface *wif;

	/* Make sure it's not in the list. */
	for (wif = wlan_first_interface(); wif != NULL;
	    wif = wlan_next_interface(wif))
		if (strcmp(wname, wif->wname) == 0) {
			wif->internal = 0;
			return (wif);
		}

	if ((wif = (struct wlan_iface *)malloc(sizeof(*wif))) == NULL)
		return (NULL);

	memset(wif, 0, sizeof(struct wlan_iface));
	strlcpy(wif->wname, wname, IFNAMSIZ);
	wif->status = RowStatus_notReady;
	wif->state = wlanIfaceState_down;
	wif->mode = WlanIfaceOperatingModeType_station;

	if (wlan_add_wif(wif) < 0) {
		free(wif);
		return (NULL);
	}

	return (wif);
}