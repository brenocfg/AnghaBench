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
struct p2p_data {int /*<<< orphan*/ ** wps_vendor_ext; } ;

/* Variables and functions */
 int P2P_MAX_WPS_VENDOR_EXT ; 
 int /*<<< orphan*/ * wpabuf_dup (struct wpabuf const*) ; 

int p2p_add_wps_vendor_extension(struct p2p_data *p2p,
				 const struct wpabuf *vendor_ext)
{
	int i;

	if (vendor_ext == NULL)
		return -1;

	for (i = 0; i < P2P_MAX_WPS_VENDOR_EXT; i++) {
		if (p2p->wps_vendor_ext[i] == NULL)
			break;
	}
	if (i >= P2P_MAX_WPS_VENDOR_EXT)
		return -1;

	p2p->wps_vendor_ext[i] = wpabuf_dup(vendor_ext);
	if (p2p->wps_vendor_ext[i] == NULL)
		return -1;

	return 0;
}