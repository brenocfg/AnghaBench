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
struct tlv_buffer_size {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct channel_tlv {size_t type; scalar_t__ length; } ;

/* Variables and functions */
 size_t CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,size_t,scalar_t__) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 size_t* ecore_channel_tlvs_string ; 
 scalar_t__ ecore_iov_tlv_supported (size_t) ; 

void ecore_dp_tlv_list(struct ecore_hwfn *p_hwfn, void *tlvs_list)
{
	u16 i = 1, total_length = 0;
	struct channel_tlv *tlv;

	do {
		/* cast current tlv list entry to channel tlv header*/
		tlv = (struct channel_tlv *)((u8 *)tlvs_list + total_length);

		/* output tlv */
		if (ecore_iov_tlv_supported(tlv->type))
			DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
				   "TLV number %d: type %s, length %d\n",
				   i, ecore_channel_tlvs_string[tlv->type],
				   tlv->length);
		else
			DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
				   "TLV number %d: type %d, length %d\n",
				   i, tlv->type, tlv->length);

		if (tlv->type == CHANNEL_TLV_LIST_END)
			return;

		/* Validate entry - protect against malicious VFs */
		if (!tlv->length) {
			DP_NOTICE(p_hwfn, false, "TLV of length 0 found\n");
			return;
		}

		total_length += tlv->length;

		if (total_length >= sizeof(struct tlv_buffer_size)) {
			DP_NOTICE(p_hwfn, false, "TLV ==> Buffer overflow\n");
			return;
		}

		i++;
	} while (1);
}