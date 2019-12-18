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
struct ikev2_hdr {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_PUT_BE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 struct ikev2_hdr* wpabuf_mhead (struct wpabuf*) ; 

void ikev2_update_hdr(struct wpabuf *msg)
{
	struct ikev2_hdr *hdr;

	/* Update lenth field in HDR */
	hdr = wpabuf_mhead(msg);
	WPA_PUT_BE32(hdr->length, wpabuf_len(msg));
}