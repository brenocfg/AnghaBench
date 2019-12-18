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
typedef  int u8 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ wpabuf_put (struct wpabuf*,int /*<<< orphan*/ ) ; 

void p2p_buf_update_ie_hdr(struct wpabuf *buf, u8 *len)
{
	/* Update P2P IE Length */
	*len = (u8 *) wpabuf_put(buf, 0) - len - 1;
}