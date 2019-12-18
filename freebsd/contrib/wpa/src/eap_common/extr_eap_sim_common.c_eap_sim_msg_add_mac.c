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
struct eap_sim_msg {int mac; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_SIM_MAC_LEN ; 
 int /*<<< orphan*/ * eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wpabuf_head_u8 (int /*<<< orphan*/ ) ; 

u8 * eap_sim_msg_add_mac(struct eap_sim_msg *msg, u8 attr)
{
	u8 *pos = eap_sim_msg_add(msg, attr, 0, NULL, EAP_SIM_MAC_LEN);
	if (pos)
		msg->mac = (pos - wpabuf_head_u8(msg->buf)) + 4;
	return pos;
}