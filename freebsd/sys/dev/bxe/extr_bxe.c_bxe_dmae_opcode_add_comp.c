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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int DMAE_CMD_C_DST_SHIFT ; 
 int DMAE_CMD_C_TYPE_ENABLE ; 

uint32_t
bxe_dmae_opcode_add_comp(uint32_t opcode,
                         uint8_t  comp_type)
{
    return (opcode | ((comp_type << DMAE_CMD_C_DST_SHIFT) |
                      DMAE_CMD_C_TYPE_ENABLE));
}