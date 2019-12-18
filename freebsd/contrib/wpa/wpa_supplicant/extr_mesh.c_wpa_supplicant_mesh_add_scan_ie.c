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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_MESH_ID ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpabuf_resize (struct wpabuf**,size_t) ; 

void wpa_supplicant_mesh_add_scan_ie(struct wpa_supplicant *wpa_s,
				     struct wpabuf **extra_ie)
{
	/* EID + 0-length (wildcard) mesh-id */
	size_t ielen = 2;

	if (wpabuf_resize(extra_ie, ielen) == 0) {
		wpabuf_put_u8(*extra_ie, WLAN_EID_MESH_ID);
		wpabuf_put_u8(*extra_ie, 0);
	}
}