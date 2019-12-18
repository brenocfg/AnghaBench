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

/* Variables and functions */
 int /*<<< orphan*/  P2P_IE_VENDOR_TYPE ; 
 struct wpabuf* ieee802_11_vendor_ie_concat (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 int p2p_parse_dev_addr_in_p2p_ie (struct wpabuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

int p2p_parse_dev_addr(const u8 *ies, size_t ies_len, u8 *dev_addr)
{
	struct wpabuf *p2p_ie;
	int ret;

	p2p_ie = ieee802_11_vendor_ie_concat(ies, ies_len,
					     P2P_IE_VENDOR_TYPE);
	if (p2p_ie == NULL)
		return -1;
	ret = p2p_parse_dev_addr_in_p2p_ie(p2p_ie, dev_addr);
	wpabuf_free(p2p_ie);
	return ret;
}