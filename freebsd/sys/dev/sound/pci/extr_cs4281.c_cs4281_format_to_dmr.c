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
typedef  int u_int32_t ;

/* Variables and functions */
 int AFMT_8BIT ; 
 int AFMT_BIGENDIAN ; 
 int AFMT_CHANNEL (int) ; 
 int AFMT_SIGNED ; 
 int CS4281PCI_DMR_BEND ; 
 int CS4281PCI_DMR_MONO ; 
 int CS4281PCI_DMR_SIZE8 ; 
 int CS4281PCI_DMR_USIGN ; 

__attribute__((used)) static inline u_int32_t
cs4281_format_to_dmr(u_int32_t format)
{
    u_int32_t dmr = 0;
    if (AFMT_8BIT & format)      dmr |= CS4281PCI_DMR_SIZE8;
    if (AFMT_CHANNEL(format) < 2) dmr |= CS4281PCI_DMR_MONO;
    if (AFMT_BIGENDIAN & format) dmr |= CS4281PCI_DMR_BEND;
    if (!(AFMT_SIGNED & format)) dmr |= CS4281PCI_DMR_USIGN;
    return dmr;
}