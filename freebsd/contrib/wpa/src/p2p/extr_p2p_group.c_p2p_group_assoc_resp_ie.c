#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct p2p_group {TYPE_1__* p2p; scalar_t__ wfd_ie; } ;
struct TYPE_2__ {scalar_t__* vendor_elem; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_SC_SUCCESS ; 
 size_t VENDOR_ELEM_P2P_ASSOC_RESP ; 
 int /*<<< orphan*/ * p2p_buf_add_ie_hdr (struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_buf_add_status (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_buf_update_ie_hdr (struct wpabuf*,int /*<<< orphan*/ *) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 size_t wpabuf_len (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,scalar_t__) ; 

struct wpabuf * p2p_group_assoc_resp_ie(struct p2p_group *group, u8 status)
{
	struct wpabuf *resp;
	u8 *rlen;
	size_t extra = 0;

#ifdef CONFIG_WIFI_DISPLAY
	if (group->wfd_ie)
		extra = wpabuf_len(group->wfd_ie);
#endif /* CONFIG_WIFI_DISPLAY */

	if (group->p2p->vendor_elem &&
	    group->p2p->vendor_elem[VENDOR_ELEM_P2P_ASSOC_RESP])
		extra += wpabuf_len(group->p2p->vendor_elem[VENDOR_ELEM_P2P_ASSOC_RESP]);

	/*
	 * (Re)Association Response - P2P IE
	 * Status attribute (shall be present when association request is
	 *	denied)
	 * Extended Listen Timing (may be present)
	 */
	resp = wpabuf_alloc(20 + extra);
	if (resp == NULL)
		return NULL;

#ifdef CONFIG_WIFI_DISPLAY
	if (group->wfd_ie)
		wpabuf_put_buf(resp, group->wfd_ie);
#endif /* CONFIG_WIFI_DISPLAY */

	if (group->p2p->vendor_elem &&
	    group->p2p->vendor_elem[VENDOR_ELEM_P2P_ASSOC_RESP])
		wpabuf_put_buf(resp,
			       group->p2p->vendor_elem[VENDOR_ELEM_P2P_ASSOC_RESP]);

	rlen = p2p_buf_add_ie_hdr(resp);
	if (status != P2P_SC_SUCCESS)
		p2p_buf_add_status(resp, status);
	p2p_buf_update_ie_hdr(resp, rlen);

	return resp;
}