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
typedef  int u16 ;
struct eap_tlv_pac_type_tlv {int /*<<< orphan*/  pac_type; int /*<<< orphan*/  length; int /*<<< orphan*/  tlv_type; } ;

/* Variables and functions */
 int PAC_TYPE_PAC_TYPE ; 
 int be_to_host16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_fast_pac_type(u8 *pac, size_t len, u16 type)
{
	struct eap_tlv_pac_type_tlv *tlv;

	if (pac == NULL || len != sizeof(*tlv))
		return 0;

	tlv = (struct eap_tlv_pac_type_tlv *) pac;

	return be_to_host16(tlv->tlv_type) == PAC_TYPE_PAC_TYPE &&
		be_to_host16(tlv->length) == 2 &&
		be_to_host16(tlv->pac_type) == type;
}