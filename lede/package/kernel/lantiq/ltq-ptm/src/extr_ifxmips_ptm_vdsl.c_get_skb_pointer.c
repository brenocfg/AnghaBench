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
 int /*<<< orphan*/  ASSERT (int,char*,unsigned int,unsigned int,...) ; 
 int DATA_BUFFER_ALIGNMENT ; 
 unsigned int KSEG0 ; 
 unsigned int KSEG1 ; 
 int /*<<< orphan*/  dbg (char*) ; 

__attribute__((used)) static inline struct sk_buff *get_skb_pointer(unsigned int dataptr)
{
    unsigned int skb_dataptr;
    struct sk_buff *skb;

    //  usually, CPE memory is less than 256M bytes
    //  so NULL means invalid pointer
    if ( dataptr == 0 ) {
        dbg("dataptr is 0, it's supposed to be invalid pointer");
        return NULL;
    }

    skb_dataptr = (dataptr - 4) | KSEG1;
    skb = *(struct sk_buff **)skb_dataptr;

    ASSERT((unsigned int)skb >= KSEG0, "invalid skb - skb = %#08x, dataptr = %#08x", (unsigned int)skb, dataptr);
    ASSERT((((unsigned int)skb->data & (0x0FFFFFFF ^ (DATA_BUFFER_ALIGNMENT - 1))) | KSEG1) == (dataptr | KSEG1), "invalid skb - skb = %#08x, skb->data = %#08x, dataptr = %#08x", (unsigned int)skb, (unsigned int)skb->data, dataptr);

    return skb;
}