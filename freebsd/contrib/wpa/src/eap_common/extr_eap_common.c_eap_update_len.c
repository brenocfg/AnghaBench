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
struct eap_hdr {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  host_to_be16 (int) ; 
 int wpabuf_len (struct wpabuf*) ; 
 struct eap_hdr* wpabuf_mhead (struct wpabuf*) ; 

void eap_update_len(struct wpabuf *msg)
{
	struct eap_hdr *hdr;
	hdr = wpabuf_mhead(msg);
	if (wpabuf_len(msg) < sizeof(*hdr))
		return;
	hdr->length = host_to_be16(wpabuf_len(msg));
}