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
struct p2p_message {scalar_t__ device_id; scalar_t__ p2p_device_addr; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct p2p_message*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ p2p_parse_p2p_ie (struct wpabuf*,struct p2p_message*) ; 

int p2p_parse_dev_addr_in_p2p_ie(struct wpabuf *p2p_ie, u8 *dev_addr)
{
	struct p2p_message msg;

	os_memset(&msg, 0, sizeof(msg));
	if (p2p_parse_p2p_ie(p2p_ie, &msg))
		return -1;

	if (msg.p2p_device_addr) {
		os_memcpy(dev_addr, msg.p2p_device_addr, ETH_ALEN);
		return 0;
	} else if (msg.device_id) {
		os_memcpy(dev_addr, msg.device_id, ETH_ALEN);
		return 0;
	}
	return -1;
}