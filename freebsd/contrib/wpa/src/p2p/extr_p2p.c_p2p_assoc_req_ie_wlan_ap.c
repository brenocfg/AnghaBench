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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct p2p_message {scalar_t__ manageability; } ;
struct p2p_data {scalar_t__ num_groups; int dev_capab; scalar_t__ cross_connect; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int P2P_DEV_CAPAB_CONCURRENT_OPER ; 
 int P2P_DEV_CAPAB_INFRA_MANAGED ; 
 int /*<<< orphan*/  P2P_GROUP_CAPAB_CROSS_CONN ; 
 int /*<<< orphan*/  P2P_GROUP_CAPAB_GROUP_OWNER ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  os_memset (struct p2p_message*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p2p_buf_add_capability (struct wpabuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p2p_buf_add_ie_hdr (struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_buf_add_p2p_interface (struct wpabuf*,struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_buf_update_ie_hdr (struct wpabuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,char*) ; 
 scalar_t__ p2p_parse_p2p_ie (struct wpabuf*,struct p2p_message*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static int p2p_assoc_req_ie_wlan_ap(struct p2p_data *p2p, const u8 *bssid,
				    u8 *buf, size_t len, struct wpabuf *p2p_ie)
{
	struct wpabuf *tmp;
	u8 *lpos;
	size_t tmplen;
	int res;
	u8 group_capab;
	struct p2p_message msg;

	if (p2p_ie == NULL)
		return 0; /* WLAN AP is not a P2P manager */

	os_memset(&msg, 0, sizeof(msg));
	if (p2p_parse_p2p_ie(p2p_ie, &msg) < 0)
		return 0;

	p2p_dbg(p2p, "BSS P2P manageability %s",
		msg.manageability ? "enabled" : "disabled");

	if (!msg.manageability)
		return 0;

	/*
	 * (Re)Association Request - P2P IE
	 * P2P Capability attribute (shall be present)
	 * P2P Interface attribute (present if concurrent device and
	 *	P2P Management is enabled)
	 */
	tmp = wpabuf_alloc(200);
	if (tmp == NULL)
		return -1;

	lpos = p2p_buf_add_ie_hdr(tmp);
	group_capab = 0;
	if (p2p->num_groups > 0) {
		group_capab |= P2P_GROUP_CAPAB_GROUP_OWNER;
		if ((p2p->dev_capab & P2P_DEV_CAPAB_CONCURRENT_OPER) &&
		    (p2p->dev_capab & P2P_DEV_CAPAB_INFRA_MANAGED) &&
		    p2p->cross_connect)
			group_capab |= P2P_GROUP_CAPAB_CROSS_CONN;
	}
	p2p_buf_add_capability(tmp, p2p->dev_capab, group_capab);
	if ((p2p->dev_capab & P2P_DEV_CAPAB_CONCURRENT_OPER) &&
	    (p2p->dev_capab & P2P_DEV_CAPAB_INFRA_MANAGED))
		p2p_buf_add_p2p_interface(tmp, p2p);
	p2p_buf_update_ie_hdr(tmp, lpos);

	tmplen = wpabuf_len(tmp);
	if (tmplen > len)
		res = -1;
	else {
		os_memcpy(buf, wpabuf_head(tmp), tmplen);
		res = tmplen;
	}
	wpabuf_free(tmp);

	return res;
}