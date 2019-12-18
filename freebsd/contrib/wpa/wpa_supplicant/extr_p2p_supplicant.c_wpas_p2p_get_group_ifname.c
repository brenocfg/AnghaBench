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
struct wpa_supplicant {char* ifname; int /*<<< orphan*/  p2p_group_idx; } ;

/* Variables and functions */
 scalar_t__ IFNAMSIZ ; 
 char* P2P_MGMT_DEVICE_PREFIX ; 
 int os_snprintf (char*,size_t,char*,char*,...) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 
 scalar_t__ os_strlen (char*) ; 
 scalar_t__ os_strncmp (char*,char*,scalar_t__) ; 
 char* os_strrchr (char*,char) ; 

__attribute__((used)) static void wpas_p2p_get_group_ifname(struct wpa_supplicant *wpa_s,
				      char *ifname, size_t len)
{
	char *ifname_ptr = wpa_s->ifname;

	if (os_strncmp(wpa_s->ifname, P2P_MGMT_DEVICE_PREFIX,
		       os_strlen(P2P_MGMT_DEVICE_PREFIX)) == 0) {
		ifname_ptr = os_strrchr(wpa_s->ifname, '-') + 1;
	}

	os_snprintf(ifname, len, "p2p-%s-%d", ifname_ptr, wpa_s->p2p_group_idx);
	if (os_strlen(ifname) >= IFNAMSIZ &&
	    os_strlen(wpa_s->ifname) < IFNAMSIZ) {
		int res;

		/* Try to avoid going over the IFNAMSIZ length limit */
		res = os_snprintf(ifname, len, "p2p-%d", wpa_s->p2p_group_idx);
		if (os_snprintf_error(len, res) && len)
			ifname[len - 1] = '\0';
	}
}