#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int32_t ;
typedef  void* u_int16_t ;
struct TYPE_8__ {void** ant_ctrl_chain; void* paprd_rate_mask_ht40; void* paprd_rate_mask_ht20; void* ant_ctrl_common2; void* ant_ctrl_common; } ;
struct TYPE_7__ {void** ant_ctrl_chain; void* paprd_rate_mask_ht40; void* paprd_rate_mask_ht20; void* ant_ctrl_common2; void* ant_ctrl_common; } ;
struct TYPE_6__ {void* swreg; void** reg_dmn; } ;
struct TYPE_9__ {TYPE_3__ modal_header_5g; TYPE_2__ modal_header_2g; TYPE_1__ base_eep_header; } ;
typedef  TYPE_4__ ar9300_eeprom_t ;

/* Variables and functions */
 int OSPREY_MAX_CHAINS ; 
 void* __bswap16 (void*) ; 
 void* __bswap32 (void*) ; 

void
ar9300_swap_eeprom(ar9300_eeprom_t *eep)
{
    u_int32_t dword;
    u_int16_t word;
    int          i;

    word = __bswap16(eep->base_eep_header.reg_dmn[0]);
    eep->base_eep_header.reg_dmn[0] = word;

    word = __bswap16(eep->base_eep_header.reg_dmn[1]);
    eep->base_eep_header.reg_dmn[1] = word;

    dword = __bswap32(eep->base_eep_header.swreg);
    eep->base_eep_header.swreg = dword;

    dword = __bswap32(eep->modal_header_2g.ant_ctrl_common);
    eep->modal_header_2g.ant_ctrl_common = dword;

    dword = __bswap32(eep->modal_header_2g.ant_ctrl_common2);
    eep->modal_header_2g.ant_ctrl_common2 = dword;

    dword = __bswap32(eep->modal_header_2g.paprd_rate_mask_ht20);
    eep->modal_header_2g.paprd_rate_mask_ht20 = dword;

    dword = __bswap32(eep->modal_header_2g.paprd_rate_mask_ht40);
    eep->modal_header_2g.paprd_rate_mask_ht40 = dword;

    dword = __bswap32(eep->modal_header_5g.ant_ctrl_common);
    eep->modal_header_5g.ant_ctrl_common = dword;

    dword = __bswap32(eep->modal_header_5g.ant_ctrl_common2);
    eep->modal_header_5g.ant_ctrl_common2 = dword;

    dword = __bswap32(eep->modal_header_5g.paprd_rate_mask_ht20);
    eep->modal_header_5g.paprd_rate_mask_ht20 = dword;

    dword = __bswap32(eep->modal_header_5g.paprd_rate_mask_ht40);
    eep->modal_header_5g.paprd_rate_mask_ht40 = dword;

    for (i = 0; i < OSPREY_MAX_CHAINS; i++) {
        word = __bswap16(eep->modal_header_2g.ant_ctrl_chain[i]);
        eep->modal_header_2g.ant_ctrl_chain[i] = word;

        word = __bswap16(eep->modal_header_5g.ant_ctrl_chain[i]);
        eep->modal_header_5g.ant_ctrl_chain[i] = word;
    }
}