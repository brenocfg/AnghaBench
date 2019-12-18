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
typedef  int uint32_t ;
struct port_info {int port_type; int /*<<< orphan*/  mod_type; } ;

/* Variables and functions */
#define  FW_PORT_CAP32_SPEED_100G 169 
#define  FW_PORT_CAP32_SPEED_100M 168 
#define  FW_PORT_CAP32_SPEED_10G 167 
#define  FW_PORT_CAP32_SPEED_1G 166 
#define  FW_PORT_CAP32_SPEED_25G 165 
#define  FW_PORT_CAP32_SPEED_40G 164 
#define  FW_PORT_CAP32_SPEED_50G 163 
#define  FW_PORT_MOD_TYPE_ER 162 
#define  FW_PORT_MOD_TYPE_ERROR 161 
#define  FW_PORT_MOD_TYPE_LR 160 
#define  FW_PORT_MOD_TYPE_LRM 159 
#define  FW_PORT_MOD_TYPE_NA 158 
#define  FW_PORT_MOD_TYPE_NONE 157 
#define  FW_PORT_MOD_TYPE_NOTSUPPORTED 156 
#define  FW_PORT_MOD_TYPE_SR 155 
#define  FW_PORT_MOD_TYPE_TWINAX_ACTIVE 154 
#define  FW_PORT_MOD_TYPE_TWINAX_PASSIVE 153 
#define  FW_PORT_MOD_TYPE_UNKNOWN 152 
#define  FW_PORT_TYPE_BP40_BA 151 
#define  FW_PORT_TYPE_BP4_AP 150 
#define  FW_PORT_TYPE_BP_AP 149 
#define  FW_PORT_TYPE_BT_SGMII 148 
#define  FW_PORT_TYPE_BT_XAUI 147 
#define  FW_PORT_TYPE_BT_XFI 146 
#define  FW_PORT_TYPE_CR2_QSFP 145 
#define  FW_PORT_TYPE_CR4_QSFP 144 
#define  FW_PORT_TYPE_CR_QSFP 143 
#define  FW_PORT_TYPE_CX4 142 
#define  FW_PORT_TYPE_FIBER_XAUI 141 
#define  FW_PORT_TYPE_FIBER_XFI 140 
#define  FW_PORT_TYPE_KR 139 
#define  FW_PORT_TYPE_KR4_100G 138 
#define  FW_PORT_TYPE_KR_SFP28 137 
#define  FW_PORT_TYPE_KR_XLAUI 136 
#define  FW_PORT_TYPE_KX 135 
#define  FW_PORT_TYPE_KX4 134 
#define  FW_PORT_TYPE_NONE 133 
#define  FW_PORT_TYPE_QSA 132 
#define  FW_PORT_TYPE_QSFP 131 
#define  FW_PORT_TYPE_QSFP_10G 130 
#define  FW_PORT_TYPE_SFP 129 
#define  FW_PORT_TYPE_SFP28 128 
 int IFM_1000_CX ; 
 int IFM_1000_KX ; 
 int IFM_1000_LX ; 
 int IFM_1000_SX ; 
 int IFM_1000_T ; 
 int IFM_100G_CR4 ; 
 int IFM_100G_KR4 ; 
 int IFM_100G_LR4 ; 
 int IFM_100G_SR4 ; 
 int IFM_100_T ; 
 int IFM_10G_CX4 ; 
 int IFM_10G_ER ; 
 int IFM_10G_KR ; 
 int IFM_10G_KX4 ; 
 int IFM_10G_LR ; 
 int IFM_10G_LRM ; 
 int IFM_10G_SR ; 
 int IFM_10G_T ; 
 int IFM_10G_TWINAX ; 
 int IFM_25G_CR ; 
 int IFM_25G_KR ; 
 int IFM_25G_LR ; 
 int IFM_25G_SR ; 
 int IFM_40G_CR4 ; 
 int IFM_40G_KR4 ; 
 int IFM_40G_LR4 ; 
 int IFM_40G_SR4 ; 
 int IFM_50G_CR2 ; 
 int IFM_50G_KR2 ; 
 int IFM_50G_LR2 ; 
 int IFM_50G_SR2 ; 
 int IFM_NONE ; 
 int IFM_UNKNOWN ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int M_FW_PORT_CAP32_SPEED ; 
 int powerof2 (int) ; 

__attribute__((used)) static int
port_mword(struct port_info *pi, uint32_t speed)
{

	MPASS(speed & M_FW_PORT_CAP32_SPEED);
	MPASS(powerof2(speed));

	switch(pi->port_type) {
	case FW_PORT_TYPE_BT_SGMII:
	case FW_PORT_TYPE_BT_XFI:
	case FW_PORT_TYPE_BT_XAUI:
		/* BaseT */
		switch (speed) {
		case FW_PORT_CAP32_SPEED_100M:
			return (IFM_100_T);
		case FW_PORT_CAP32_SPEED_1G:
			return (IFM_1000_T);
		case FW_PORT_CAP32_SPEED_10G:
			return (IFM_10G_T);
		}
		break;
	case FW_PORT_TYPE_KX4:
		if (speed == FW_PORT_CAP32_SPEED_10G)
			return (IFM_10G_KX4);
		break;
	case FW_PORT_TYPE_CX4:
		if (speed == FW_PORT_CAP32_SPEED_10G)
			return (IFM_10G_CX4);
		break;
	case FW_PORT_TYPE_KX:
		if (speed == FW_PORT_CAP32_SPEED_1G)
			return (IFM_1000_KX);
		break;
	case FW_PORT_TYPE_KR:
	case FW_PORT_TYPE_BP_AP:
	case FW_PORT_TYPE_BP4_AP:
	case FW_PORT_TYPE_BP40_BA:
	case FW_PORT_TYPE_KR4_100G:
	case FW_PORT_TYPE_KR_SFP28:
	case FW_PORT_TYPE_KR_XLAUI:
		switch (speed) {
		case FW_PORT_CAP32_SPEED_1G:
			return (IFM_1000_KX);
		case FW_PORT_CAP32_SPEED_10G:
			return (IFM_10G_KR);
		case FW_PORT_CAP32_SPEED_25G:
			return (IFM_25G_KR);
		case FW_PORT_CAP32_SPEED_40G:
			return (IFM_40G_KR4);
		case FW_PORT_CAP32_SPEED_50G:
			return (IFM_50G_KR2);
		case FW_PORT_CAP32_SPEED_100G:
			return (IFM_100G_KR4);
		}
		break;
	case FW_PORT_TYPE_FIBER_XFI:
	case FW_PORT_TYPE_FIBER_XAUI:
	case FW_PORT_TYPE_SFP:
	case FW_PORT_TYPE_QSFP_10G:
	case FW_PORT_TYPE_QSA:
	case FW_PORT_TYPE_QSFP:
	case FW_PORT_TYPE_CR4_QSFP:
	case FW_PORT_TYPE_CR_QSFP:
	case FW_PORT_TYPE_CR2_QSFP:
	case FW_PORT_TYPE_SFP28:
		/* Pluggable transceiver */
		switch (pi->mod_type) {
		case FW_PORT_MOD_TYPE_LR:
			switch (speed) {
			case FW_PORT_CAP32_SPEED_1G:
				return (IFM_1000_LX);
			case FW_PORT_CAP32_SPEED_10G:
				return (IFM_10G_LR);
			case FW_PORT_CAP32_SPEED_25G:
				return (IFM_25G_LR);
			case FW_PORT_CAP32_SPEED_40G:
				return (IFM_40G_LR4);
			case FW_PORT_CAP32_SPEED_50G:
				return (IFM_50G_LR2);
			case FW_PORT_CAP32_SPEED_100G:
				return (IFM_100G_LR4);
			}
			break;
		case FW_PORT_MOD_TYPE_SR:
			switch (speed) {
			case FW_PORT_CAP32_SPEED_1G:
				return (IFM_1000_SX);
			case FW_PORT_CAP32_SPEED_10G:
				return (IFM_10G_SR);
			case FW_PORT_CAP32_SPEED_25G:
				return (IFM_25G_SR);
			case FW_PORT_CAP32_SPEED_40G:
				return (IFM_40G_SR4);
			case FW_PORT_CAP32_SPEED_50G:
				return (IFM_50G_SR2);
			case FW_PORT_CAP32_SPEED_100G:
				return (IFM_100G_SR4);
			}
			break;
		case FW_PORT_MOD_TYPE_ER:
			if (speed == FW_PORT_CAP32_SPEED_10G)
				return (IFM_10G_ER);
			break;
		case FW_PORT_MOD_TYPE_TWINAX_PASSIVE:
		case FW_PORT_MOD_TYPE_TWINAX_ACTIVE:
			switch (speed) {
			case FW_PORT_CAP32_SPEED_1G:
				return (IFM_1000_CX);
			case FW_PORT_CAP32_SPEED_10G:
				return (IFM_10G_TWINAX);
			case FW_PORT_CAP32_SPEED_25G:
				return (IFM_25G_CR);
			case FW_PORT_CAP32_SPEED_40G:
				return (IFM_40G_CR4);
			case FW_PORT_CAP32_SPEED_50G:
				return (IFM_50G_CR2);
			case FW_PORT_CAP32_SPEED_100G:
				return (IFM_100G_CR4);
			}
			break;
		case FW_PORT_MOD_TYPE_LRM:
			if (speed == FW_PORT_CAP32_SPEED_10G)
				return (IFM_10G_LRM);
			break;
		case FW_PORT_MOD_TYPE_NA:
			MPASS(0);	/* Not pluggable? */
			/* fall throough */
		case FW_PORT_MOD_TYPE_ERROR:
		case FW_PORT_MOD_TYPE_UNKNOWN:
		case FW_PORT_MOD_TYPE_NOTSUPPORTED:
			break;
		case FW_PORT_MOD_TYPE_NONE:
			return (IFM_NONE);
		}
		break;
	case FW_PORT_TYPE_NONE:
		return (IFM_NONE);
	}

	return (IFM_UNKNOWN);
}