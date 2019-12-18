#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_8__ {int /*<<< orphan*/  ant_div_control; } ;
struct TYPE_6__ {int op_flags; } ;
struct TYPE_9__ {int* reg_dmn; int device_cap; int rf_silent; int eeprom_version; int txrx_mask; int fast_clk5g; int rx_gain_type; int misc_configuration; int feature_enable; int swreg; int device_type; TYPE_1__ op_cap_flags; } ;
struct TYPE_7__ {int* mac_addr; TYPE_3__ base_ext1; TYPE_4__ base_eep_header; } ;
struct ath_hal_9300 {TYPE_2__ ah_eeprom; } ;
typedef  TYPE_2__ ar9300_eeprom_t ;
struct TYPE_10__ {int* noise_floor_thresh_ch; int ob; int db; } ;
typedef  TYPE_3__ OSPREY_BASE_EXTENSION_1 ;
typedef  TYPE_4__ OSPREY_BASE_EEP_HEADER ;
typedef  int EEPROM_PARAM ;

/* Variables and functions */
 int AR9300_EEP_BASE_DRIVE_STRENGTH ; 
 int AR9300_EEP_VER_MINOR_MASK ; 
#define  EEP_ANTDIV_control 154 
#define  EEP_CHAIN_MASK_REDUCE 153 
#define  EEP_DB_2 152 
#define  EEP_DB_5 151 
#define  EEP_DEV_TYPE 150 
#define  EEP_DRIVE_STRENGTH 149 
#define  EEP_FSTCLK_5G 148 
#define  EEP_INTERNAL_REGULATOR 147 
#define  EEP_MAC_LSW 146 
#define  EEP_MAC_MID 145 
#define  EEP_MAC_MSW 144 
#define  EEP_MINOR_REV 143 
#define  EEP_NFTHRESH_2 142 
#define  EEP_NFTHRESH_5 141 
#define  EEP_OB_2 140 
#define  EEP_OB_5 139 
#define  EEP_OL_PWRCTRL 138 
#define  EEP_OP_CAP 137 
#define  EEP_OP_MODE 136 
#define  EEP_PAPRD_ENABLED 135 
#define  EEP_REG_0 134 
#define  EEP_REG_1 133 
#define  EEP_RF_SILENT 132 
#define  EEP_RXGAIN_TYPE 131 
#define  EEP_RX_MASK 130 
#define  EEP_SWREG 129 
#define  EEP_TX_MASK 128 
 int /*<<< orphan*/  HALASSERT (int /*<<< orphan*/ ) ; 
 TYPE_5__* p_modal ; 

u_int32_t
ar9300_eeprom_get(struct ath_hal_9300 *ahp, EEPROM_PARAM param)
{
    ar9300_eeprom_t *eep = &ahp->ah_eeprom;
    OSPREY_BASE_EEP_HEADER *p_base = &eep->base_eep_header;
    OSPREY_BASE_EXTENSION_1 *base_ext1 = &eep->base_ext1;

    switch (param) {
#ifdef NOTYET
    case EEP_NFTHRESH_5:
        return p_modal[0].noise_floor_thresh_ch[0];
    case EEP_NFTHRESH_2:
        return p_modal[1].noise_floor_thresh_ch[0];
#endif
    case EEP_MAC_LSW:
        return eep->mac_addr[0] << 8 | eep->mac_addr[1];
    case EEP_MAC_MID:
        return eep->mac_addr[2] << 8 | eep->mac_addr[3];
    case EEP_MAC_MSW:
        return eep->mac_addr[4] << 8 | eep->mac_addr[5];
    case EEP_REG_0:
        return p_base->reg_dmn[0];
    case EEP_REG_1:
        return p_base->reg_dmn[1];
    case EEP_OP_CAP:
        return p_base->device_cap;
    case EEP_OP_MODE:
        return p_base->op_cap_flags.op_flags;
    case EEP_RF_SILENT:
        return p_base->rf_silent;
#ifdef NOTYET
    case EEP_OB_5:
        return p_modal[0].ob;
    case EEP_DB_5:
        return p_modal[0].db;
    case EEP_OB_2:
        return p_modal[1].ob;
    case EEP_DB_2:
        return p_modal[1].db;
    case EEP_MINOR_REV:
        return p_base->eeprom_version & AR9300_EEP_VER_MINOR_MASK;
#endif
    case EEP_TX_MASK:
        return (p_base->txrx_mask >> 4) & 0xf;
    case EEP_RX_MASK:
        return p_base->txrx_mask & 0xf;
#ifdef NOTYET
    case EEP_FSTCLK_5G:
        return p_base->fast_clk5g;
    case EEP_RXGAIN_TYPE:
        return p_base->rx_gain_type;
#endif
    case EEP_DRIVE_STRENGTH:
#define AR9300_EEP_BASE_DRIVE_STRENGTH    0x1 
        return p_base->misc_configuration & AR9300_EEP_BASE_DRIVE_STRENGTH;
    case EEP_INTERNAL_REGULATOR:
        /* Bit 4 is internal regulator flag */
        return ((p_base->feature_enable & 0x10) >> 4);
    case EEP_SWREG:
        return (p_base->swreg);
    case EEP_PAPRD_ENABLED:
        /* Bit 5 is paprd flag */
        return ((p_base->feature_enable & 0x20) >> 5);
    case EEP_ANTDIV_control:
        return (u_int32_t)(base_ext1->ant_div_control);
    case EEP_CHAIN_MASK_REDUCE:
        return ((p_base->misc_configuration >> 3) & 0x1);
    case EEP_OL_PWRCTRL:
        return 0;
     case EEP_DEV_TYPE:
        return p_base->device_type;
    default:
        HALASSERT(0);
        return 0;
    }
}