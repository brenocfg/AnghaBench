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
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int DATA_BUFFER_ALIGNMENT ; 
 scalar_t__ MAX_TX_PACKET_ALIGN_BYTES ; 
 scalar_t__ MAX_TX_PACKET_PADDING_BYTES ; 
 scalar_t__ TX_INBAND_HEADER_LENGTH ; 
 struct sk_buff* dev_alloc_skb (unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static inline struct sk_buff* alloc_skb_tx(unsigned int size)
{
	struct sk_buff *skb;

	/*  allocate memory including header and padding    */
	size += TX_INBAND_HEADER_LENGTH + MAX_TX_PACKET_ALIGN_BYTES + MAX_TX_PACKET_PADDING_BYTES;
	size &= ~(DATA_BUFFER_ALIGNMENT - 1);
	skb = dev_alloc_skb(size + DATA_BUFFER_ALIGNMENT);
	/*  must be burst length alignment  */
	if ( skb != NULL )
		skb_reserve(skb, (~((unsigned int)skb->data + (DATA_BUFFER_ALIGNMENT - 1)) & (DATA_BUFFER_ALIGNMENT - 1)) + TX_INBAND_HEADER_LENGTH);
	return skb;
}