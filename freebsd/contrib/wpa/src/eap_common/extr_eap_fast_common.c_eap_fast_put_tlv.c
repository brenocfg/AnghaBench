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
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_fast_put_tlv_hdr (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,void const*,int /*<<< orphan*/ ) ; 

void eap_fast_put_tlv(struct wpabuf *buf, u16 type, const void *data,
			     u16 len)
{
	eap_fast_put_tlv_hdr(buf, type, len);
	wpabuf_put_data(buf, data, len);
}