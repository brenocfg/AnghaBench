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
struct sk_buff {scalar_t__ data; scalar_t__ end; } ;
typedef  int /*<<< orphan*/  skb ;

/* Variables and functions */
 int DATA_BUFFER_ALIGNMENT ; 
 scalar_t__ RX_MAX_BUFFER_SIZE ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dma_cache_inv (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  dma_cache_wback_inv (unsigned long,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline struct sk_buff* alloc_skb_rx(void)
{
    struct sk_buff *skb;

    /*  allocate memroy including trailer and padding   */
    skb = dev_alloc_skb(RX_MAX_BUFFER_SIZE + DATA_BUFFER_ALIGNMENT);
    if ( skb != NULL ) {
        /*  must be burst length alignment and reserve two more bytes for MAC address alignment  */
        if ( ((unsigned int)skb->data & (DATA_BUFFER_ALIGNMENT - 1)) != 0 )
            skb_reserve(skb, ~((unsigned int)skb->data + (DATA_BUFFER_ALIGNMENT - 1)) & (DATA_BUFFER_ALIGNMENT - 1));
        /*  pub skb in reserved area "skb->data - 4"    */
        *((struct sk_buff **)skb->data - 1) = skb;
        wmb();
        /*  write back and invalidate cache    */
        dma_cache_wback_inv((unsigned long)skb->data - sizeof(skb), sizeof(skb));
        /*  invalidate cache    */
        dma_cache_inv((unsigned long)skb->data, (unsigned int)skb->end - (unsigned int)skb->data);
    }

    return skb;
}