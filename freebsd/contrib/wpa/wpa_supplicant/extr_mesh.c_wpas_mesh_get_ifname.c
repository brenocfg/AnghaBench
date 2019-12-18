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
struct wpa_supplicant {char* ifname; int /*<<< orphan*/  mesh_if_idx; } ;

/* Variables and functions */
 scalar_t__ IFNAMSIZ ; 
 int os_snprintf (char*,size_t,char*,char*,...) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 
 scalar_t__ os_strlen (char*) ; 

__attribute__((used)) static int wpas_mesh_get_ifname(struct wpa_supplicant *wpa_s, char *ifname,
				size_t len)
{
	char *ifname_ptr = wpa_s->ifname;
	int res;

	res = os_snprintf(ifname, len, "mesh-%s-%d", ifname_ptr,
			  wpa_s->mesh_if_idx);
	if (os_snprintf_error(len, res) ||
	    (os_strlen(ifname) >= IFNAMSIZ &&
	     os_strlen(wpa_s->ifname) < IFNAMSIZ)) {
		/* Try to avoid going over the IFNAMSIZ length limit */
		res = os_snprintf(ifname, len, "mesh-%d", wpa_s->mesh_if_idx);
		if (os_snprintf_error(len, res))
			return -1;
	}
	wpa_s->mesh_if_idx++;
	return 0;
}