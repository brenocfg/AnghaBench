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
struct p2p_data {scalar_t__* vendor_elem; scalar_t__ wfd_ie_probe_req; } ;

/* Variables and functions */
 size_t VENDOR_ELEM_PROBE_REQ_P2P ; 
 scalar_t__ wpabuf_len (scalar_t__) ; 

size_t p2p_scan_ie_buf_len(struct p2p_data *p2p)
{
	size_t len = 100;

#ifdef CONFIG_WIFI_DISPLAY
	if (p2p && p2p->wfd_ie_probe_req)
		len += wpabuf_len(p2p->wfd_ie_probe_req);
#endif /* CONFIG_WIFI_DISPLAY */

	if (p2p && p2p->vendor_elem &&
	    p2p->vendor_elem[VENDOR_ELEM_PROBE_REQ_P2P])
		len += wpabuf_len(p2p->vendor_elem[VENDOR_ELEM_PROBE_REQ_P2P]);

	return len;
}