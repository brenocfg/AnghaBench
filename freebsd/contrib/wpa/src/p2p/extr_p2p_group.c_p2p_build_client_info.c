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
typedef  scalar_t__ u8 ;
struct wpabuf {int dummy; } ;
struct p2p_message {int p2p_device_info_len; scalar_t__* capability; scalar_t__* p2p_device_info; int /*<<< orphan*/  p2p_device_addr; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_memset (struct p2p_message*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ p2p_parse_p2p_ie (struct wpabuf*,struct p2p_message*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 
 scalar_t__* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,scalar_t__) ; 

__attribute__((used)) static struct wpabuf * p2p_build_client_info(const u8 *addr,
					     struct wpabuf *p2p_ie,
					     u8 *dev_capab, u8 *dev_addr)
{
	const u8 *spos;
	struct p2p_message msg;
	u8 *len_pos;
	struct wpabuf *buf;

	if (p2p_ie == NULL)
		return NULL;

	os_memset(&msg, 0, sizeof(msg));
	if (p2p_parse_p2p_ie(p2p_ie, &msg) ||
	    msg.capability == NULL || msg.p2p_device_info == NULL)
		return NULL;

	buf = wpabuf_alloc(ETH_ALEN + 1 + 1 + msg.p2p_device_info_len);
	if (buf == NULL)
		return NULL;

	*dev_capab = msg.capability[0];
	os_memcpy(dev_addr, msg.p2p_device_addr, ETH_ALEN);

	spos = msg.p2p_device_info; /* P2P Device address */

	/* P2P Client Info Descriptor */
	/* Length to be set */
	len_pos = wpabuf_put(buf, 1);
	/* P2P Device address */
	wpabuf_put_data(buf, spos, ETH_ALEN);
	/* P2P Interface address */
	wpabuf_put_data(buf, addr, ETH_ALEN);
	/* Device Capability Bitmap */
	wpabuf_put_u8(buf, msg.capability[0]);
	/*
	 * Config Methods, Primary Device Type, Number of Secondary Device
	 * Types, Secondary Device Type List, Device Name copied from
	 * Device Info
	 */
	wpabuf_put_data(buf, spos + ETH_ALEN,
			msg.p2p_device_info_len - ETH_ALEN);

	*len_pos = wpabuf_len(buf) - 1;


	return buf;
}