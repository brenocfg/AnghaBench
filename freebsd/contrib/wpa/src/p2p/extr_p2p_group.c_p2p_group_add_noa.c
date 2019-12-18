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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_ATTR_NOTICE_OF_ABSENCE ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_group_add_noa(struct wpabuf *ie, struct wpabuf *noa)
{
	if (noa == NULL)
		return;
	/* Notice of Absence */
	wpabuf_put_u8(ie, P2P_ATTR_NOTICE_OF_ABSENCE);
	wpabuf_put_le16(ie, wpabuf_len(noa));
	wpabuf_put_buf(ie, noa);
}