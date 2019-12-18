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
struct p2p_message {int /*<<< orphan*/ * capability; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  os_memset (struct p2p_message*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ p2p_parse_p2p_ie (struct wpabuf const*,struct p2p_message*) ; 

u8 p2p_get_group_capab(const struct wpabuf *p2p_ie)
{
	struct p2p_message msg;

	os_memset(&msg, 0, sizeof(msg));
	if (p2p_parse_p2p_ie(p2p_ie, &msg))
		return 0;

	if (!msg.capability)
		return 0;

	return msg.capability[1];
}