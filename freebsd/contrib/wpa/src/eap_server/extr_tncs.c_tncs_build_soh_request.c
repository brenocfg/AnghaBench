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
 int EAP_TLV_VENDOR_SPECIFIC_TLV ; 
 int /*<<< orphan*/  EAP_VENDOR_MICROSOFT ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,int /*<<< orphan*/ ) ; 

struct wpabuf * tncs_build_soh_request(void)
{
	struct wpabuf *buf;

	/*
	 * Build a SoH Request TLV (to be used inside SoH EAP Extensions
	 * Method)
	 */

	buf = wpabuf_alloc(8 + 4);
	if (buf == NULL)
		return NULL;

	/* Vendor-Specific TLV (Microsoft) - SoH Request */
	wpabuf_put_be16(buf, EAP_TLV_VENDOR_SPECIFIC_TLV); /* TLV Type */
	wpabuf_put_be16(buf, 8); /* Length */

	wpabuf_put_be32(buf, EAP_VENDOR_MICROSOFT); /* Vendor_Id */

	wpabuf_put_be16(buf, 0x02); /* TLV Type - SoH Request TLV */
	wpabuf_put_be16(buf, 0); /* Length */

	return buf;
}