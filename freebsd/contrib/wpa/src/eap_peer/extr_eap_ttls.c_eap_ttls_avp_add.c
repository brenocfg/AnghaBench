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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AVP_PAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * eap_ttls_avp_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static u8 * eap_ttls_avp_add(u8 *start, u8 *avphdr, u32 avp_code,
			     u32 vendor_id, int mandatory,
			     const u8 *data, size_t len)
{
	u8 *pos;
	pos = eap_ttls_avp_hdr(avphdr, avp_code, vendor_id, mandatory, len);
	os_memcpy(pos, data, len);
	pos += len;
	AVP_PAD(start, pos);
	return pos;
}