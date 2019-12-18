#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct p2p_group {int /*<<< orphan*/  noa; TYPE_2__* p2p; } ;
struct TYPE_4__ {TYPE_1__* cfg; scalar_t__* vendor_elem; scalar_t__ wfd_ie_beacon; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 size_t VENDOR_ELEM_BEACON_P2P_GO ; 
 int /*<<< orphan*/  p2p_buf_add_device_id (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p2p_buf_add_ie_hdr (struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_buf_update_ie_hdr (struct wpabuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_group_add_common_ies (struct p2p_group*,struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_group_add_noa (struct wpabuf*,int /*<<< orphan*/ ) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 size_t wpabuf_len (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,scalar_t__) ; 

__attribute__((used)) static struct wpabuf * p2p_group_build_beacon_ie(struct p2p_group *group)
{
	struct wpabuf *ie;
	u8 *len;
	size_t extra = 0;

#ifdef CONFIG_WIFI_DISPLAY
	if (group->p2p->wfd_ie_beacon)
		extra = wpabuf_len(group->p2p->wfd_ie_beacon);
#endif /* CONFIG_WIFI_DISPLAY */

	if (group->p2p->vendor_elem &&
	    group->p2p->vendor_elem[VENDOR_ELEM_BEACON_P2P_GO])
		extra += wpabuf_len(group->p2p->vendor_elem[VENDOR_ELEM_BEACON_P2P_GO]);

	ie = wpabuf_alloc(257 + extra);
	if (ie == NULL)
		return NULL;

#ifdef CONFIG_WIFI_DISPLAY
	if (group->p2p->wfd_ie_beacon)
		wpabuf_put_buf(ie, group->p2p->wfd_ie_beacon);
#endif /* CONFIG_WIFI_DISPLAY */

	if (group->p2p->vendor_elem &&
	    group->p2p->vendor_elem[VENDOR_ELEM_BEACON_P2P_GO])
		wpabuf_put_buf(ie,
			       group->p2p->vendor_elem[VENDOR_ELEM_BEACON_P2P_GO]);

	len = p2p_buf_add_ie_hdr(ie);
	p2p_group_add_common_ies(group, ie);
	p2p_buf_add_device_id(ie, group->p2p->cfg->dev_addr);
	p2p_group_add_noa(ie, group->noa);
	p2p_buf_update_ie_hdr(ie, len);

	return ie;
}