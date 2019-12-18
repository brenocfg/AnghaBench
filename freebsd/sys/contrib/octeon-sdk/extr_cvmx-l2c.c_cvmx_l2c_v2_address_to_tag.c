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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int CVMX_L2C_TAG_ADDR_ALIAS_SHIFT ; 
 int DR0_END ; 
 int DR1_START ; 
 int L2_HOLE ; 

uint32_t cvmx_l2c_v2_address_to_tag(uint64_t addr)
{
#define DR0_END   ( (256 * 1024 * 1024) -1)
#define DR1_START (512 * 1024 * 1024)
#define L2_HOLE   (256 * 1024 * 1024)

    if ( (addr > DR0_END) && (addr < DR1_START) ) return (uint32_t) (-1);
    if (addr > DR1_START) addr = addr - L2_HOLE ;
    addr = addr & 0x7FFFFFFFFULL;
    return (uint32_t )(addr >> CVMX_L2C_TAG_ADDR_ALIAS_SHIFT);
}