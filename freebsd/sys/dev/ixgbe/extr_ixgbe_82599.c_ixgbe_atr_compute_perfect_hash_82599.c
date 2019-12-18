#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int bkt_hash; } ;
union ixgbe_atr_input {int* dword_stream; TYPE_1__ formatted; } ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_COMPUTE_BKT_HASH_ITERATION (int) ; 
 int IXGBE_NTOHL (int) ; 

void ixgbe_atr_compute_perfect_hash_82599(union ixgbe_atr_input *input,
					  union ixgbe_atr_input *input_mask)
{

	u32 hi_hash_dword, lo_hash_dword, flow_vm_vlan;
	u32 bucket_hash = 0;
	u32 hi_dword = 0;
	u32 i = 0;

	/* Apply masks to input data */
	for (i = 0; i < 14; i++)
		input->dword_stream[i]  &= input_mask->dword_stream[i];

	/* record the flow_vm_vlan bits as they are a key part to the hash */
	flow_vm_vlan = IXGBE_NTOHL(input->dword_stream[0]);

	/* generate common hash dword */
	for (i = 1; i <= 13; i++)
		hi_dword ^= input->dword_stream[i];
	hi_hash_dword = IXGBE_NTOHL(hi_dword);

	/* low dword is word swapped version of common */
	lo_hash_dword = (hi_hash_dword >> 16) | (hi_hash_dword << 16);

	/* apply flow ID/VM pool/VLAN ID bits to hash words */
	hi_hash_dword ^= flow_vm_vlan ^ (flow_vm_vlan >> 16);

	/* Process bits 0 and 16 */
	IXGBE_COMPUTE_BKT_HASH_ITERATION(0);

	/*
	 * apply flow ID/VM pool/VLAN ID bits to lo hash dword, we had to
	 * delay this because bit 0 of the stream should not be processed
	 * so we do not add the VLAN until after bit 0 was processed
	 */
	lo_hash_dword ^= flow_vm_vlan ^ (flow_vm_vlan << 16);

	/* Process remaining 30 bit of the key */
	for (i = 1; i <= 15; i++)
		IXGBE_COMPUTE_BKT_HASH_ITERATION(i);

	/*
	 * Limit hash to 13 bits since max bucket count is 8K.
	 * Store result at the end of the input stream.
	 */
	input->formatted.bkt_hash = bucket_hash & 0x1FFF;
}