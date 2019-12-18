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
struct p2p_data {int /*<<< orphan*/ ** wps_vendor_ext; } ;

/* Variables and functions */
 int P2P_MAX_WPS_VENDOR_EXT ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

void p2p_remove_wps_vendor_extensions(struct p2p_data *p2p)
{
	int i;

	for (i = 0; i < P2P_MAX_WPS_VENDOR_EXT; i++) {
		wpabuf_free(p2p->wps_vendor_ext[i]);
		p2p->wps_vendor_ext[i] = NULL;
	}
}