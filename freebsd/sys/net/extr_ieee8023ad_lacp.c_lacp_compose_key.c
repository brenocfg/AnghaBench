#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int u_int ;
struct lagg_softc {TYPE_2__* sc_ifp; } ;
struct lagg_port {struct lagg_softc* lp_softc; } ;
struct lacp_port {int lp_media; int lp_state; TYPE_1__* lp_ifp; struct lagg_port* lp_lagg; } ;
struct TYPE_4__ {int if_index; } ;
struct TYPE_3__ {int if_index; } ;

/* Variables and functions */
#define  IFM_1000_CX 238 
#define  IFM_1000_CX_SGMII 237 
#define  IFM_1000_KX 236 
#define  IFM_1000_LX 235 
#define  IFM_1000_SGMII 234 
#define  IFM_1000_SX 233 
#define  IFM_1000_T 232 
#define  IFM_100G_AUI2 231 
#define  IFM_100G_AUI2_AC 230 
#define  IFM_100G_AUI4 229 
#define  IFM_100G_AUI4_AC 228 
#define  IFM_100G_CAUI2 227 
#define  IFM_100G_CAUI2_AC 226 
#define  IFM_100G_CAUI4 225 
#define  IFM_100G_CAUI4_AC 224 
#define  IFM_100G_CP2 223 
#define  IFM_100G_CR4 222 
#define  IFM_100G_CR_PAM4 221 
#define  IFM_100G_DR 220 
#define  IFM_100G_KR2_PAM4 219 
#define  IFM_100G_KR4 218 
#define  IFM_100G_KR_PAM4 217 
#define  IFM_100G_LR4 216 
#define  IFM_100G_SR2 215 
#define  IFM_100G_SR4 214 
#define  IFM_100_FX 213 
#define  IFM_100_SGMII 212 
#define  IFM_100_T 211 
#define  IFM_100_T2 210 
#define  IFM_100_T4 209 
#define  IFM_100_TX 208 
#define  IFM_100_VG 207 
#define  IFM_10G_AOC 206 
#define  IFM_10G_CR1 205 
#define  IFM_10G_CX4 204 
#define  IFM_10G_ER 203 
#define  IFM_10G_KR 202 
#define  IFM_10G_KX4 201 
#define  IFM_10G_LR 200 
#define  IFM_10G_LRM 199 
#define  IFM_10G_SFI 198 
#define  IFM_10G_SR 197 
#define  IFM_10G_T 196 
#define  IFM_10G_TWINAX 195 
#define  IFM_10G_TWINAX_LONG 194 
#define  IFM_10_2 193 
#define  IFM_10_5 192 
#define  IFM_10_FL 191 
#define  IFM_10_STP 190 
#define  IFM_10_T 189 
#define  IFM_200G_AUI4 188 
#define  IFM_200G_AUI4_AC 187 
#define  IFM_200G_AUI8 186 
#define  IFM_200G_AUI8_AC 185 
#define  IFM_200G_CR4_PAM4 184 
#define  IFM_200G_DR4 183 
#define  IFM_200G_FR4 182 
#define  IFM_200G_KR4_PAM4 181 
#define  IFM_200G_LR4 180 
#define  IFM_200G_SR4 179 
#define  IFM_20G_KR2 178 
#define  IFM_2500_KX 177 
#define  IFM_2500_T 176 
#define  IFM_2500_X 175 
#define  IFM_25G_ACC 174 
#define  IFM_25G_AOC 173 
#define  IFM_25G_AUI 172 
#define  IFM_25G_CR 171 
#define  IFM_25G_CR1 170 
#define  IFM_25G_CR_S 169 
#define  IFM_25G_KR 168 
#define  IFM_25G_KR1 167 
#define  IFM_25G_KR_S 166 
#define  IFM_25G_LR 165 
#define  IFM_25G_PCIE 164 
#define  IFM_25G_SR 163 
#define  IFM_25G_T 162 
#define  IFM_400G_AUI8 161 
#define  IFM_400G_AUI8_AC 160 
#define  IFM_400G_DR4 159 
#define  IFM_400G_FR8 158 
#define  IFM_400G_LR8 157 
#define  IFM_40G_CR4 156 
#define  IFM_40G_ER4 155 
#define  IFM_40G_KR4 154 
#define  IFM_40G_LR4 153 
#define  IFM_40G_SR4 152 
#define  IFM_40G_XLAUI 151 
#define  IFM_40G_XLAUI_AC 150 
#define  IFM_40G_XLPPI 149 
#define  IFM_5000_KR 148 
#define  IFM_5000_KR1 147 
#define  IFM_5000_KR_S 146 
#define  IFM_5000_T 145 
#define  IFM_50G_AUI1 144 
#define  IFM_50G_AUI1_AC 143 
#define  IFM_50G_AUI2 142 
#define  IFM_50G_AUI2_AC 141 
#define  IFM_50G_CP 140 
#define  IFM_50G_CR2 139 
#define  IFM_50G_FR 138 
#define  IFM_50G_KR2 137 
#define  IFM_50G_KR_PAM4 136 
#define  IFM_50G_LAUI2 135 
#define  IFM_50G_LAUI2_AC 134 
#define  IFM_50G_LR 133 
#define  IFM_50G_LR2 132 
#define  IFM_50G_PCIE 131 
#define  IFM_50G_SR 130 
#define  IFM_50G_SR2 129 
#define  IFM_56G_R4 128 
 scalar_t__ IFM_ETHER ; 
 int IFM_FDX ; 
 int IFM_SUBTYPE (int) ; 
 scalar_t__ IFM_TYPE (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LACP_STATE_AGGREGATION ; 
 int htons (int) ; 

__attribute__((used)) static uint16_t
lacp_compose_key(struct lacp_port *lp)
{
	struct lagg_port *lgp = lp->lp_lagg;
	struct lagg_softc *sc = lgp->lp_softc;
	u_int media = lp->lp_media;
	uint16_t key;

	if ((lp->lp_state & LACP_STATE_AGGREGATION) == 0) {

		/*
		 * non-aggregatable links should have unique keys.
		 *
		 * XXX this isn't really unique as if_index is 16 bit.
		 */

		/* bit 0..14:	(some bits of) if_index of this port */
		key = lp->lp_ifp->if_index;
		/* bit 15:	1 */
		key |= 0x8000;
	} else {
		u_int subtype = IFM_SUBTYPE(media);

		KASSERT(IFM_TYPE(media) == IFM_ETHER, ("invalid media type"));
		KASSERT((media & IFM_FDX) != 0, ("aggregating HDX interface"));

		/* bit 0..4:	IFM_SUBTYPE modulo speed */
		switch (subtype) {
		case IFM_10_T:
		case IFM_10_2:
		case IFM_10_5:
		case IFM_10_STP:
		case IFM_10_FL:
			key = IFM_10_T;
			break;
		case IFM_100_TX:
		case IFM_100_FX:
		case IFM_100_T4:
		case IFM_100_VG:
		case IFM_100_T2:
		case IFM_100_T:
		case IFM_100_SGMII:
			key = IFM_100_TX;
			break;
		case IFM_1000_SX:
		case IFM_1000_LX:
		case IFM_1000_CX:
		case IFM_1000_T:
		case IFM_1000_KX:
		case IFM_1000_SGMII:
		case IFM_1000_CX_SGMII:
			key = IFM_1000_SX;
			break;
		case IFM_10G_LR:
		case IFM_10G_SR:
		case IFM_10G_CX4:
		case IFM_10G_TWINAX:
		case IFM_10G_TWINAX_LONG:
		case IFM_10G_LRM:
		case IFM_10G_T:
		case IFM_10G_KX4:
		case IFM_10G_KR:
		case IFM_10G_CR1:
		case IFM_10G_ER:
		case IFM_10G_SFI:
		case IFM_10G_AOC:
			key = IFM_10G_LR;
			break;
		case IFM_20G_KR2:
			key = IFM_20G_KR2;
			break;
		case IFM_2500_KX:
		case IFM_2500_T:
		case IFM_2500_X:
			key = IFM_2500_KX;
			break;
		case IFM_5000_T:
		case IFM_5000_KR:
		case IFM_5000_KR_S:
		case IFM_5000_KR1:
			key = IFM_5000_T;
			break;
		case IFM_50G_PCIE:
		case IFM_50G_CR2:
		case IFM_50G_KR2:
		case IFM_50G_SR2:
		case IFM_50G_LR2:
		case IFM_50G_LAUI2_AC:
		case IFM_50G_LAUI2:
		case IFM_50G_AUI2_AC:
		case IFM_50G_AUI2:
		case IFM_50G_CP:
		case IFM_50G_SR:
		case IFM_50G_LR:
		case IFM_50G_FR:
		case IFM_50G_KR_PAM4:
		case IFM_50G_AUI1_AC:
		case IFM_50G_AUI1:
			key = IFM_50G_PCIE;
			break;
		case IFM_56G_R4:
			key = IFM_56G_R4;
			break;
		case IFM_25G_PCIE:
		case IFM_25G_CR:
		case IFM_25G_KR:
		case IFM_25G_SR:
		case IFM_25G_LR:
		case IFM_25G_ACC:
		case IFM_25G_AOC:
		case IFM_25G_T:
		case IFM_25G_CR_S:
		case IFM_25G_CR1:
		case IFM_25G_KR_S:
		case IFM_25G_AUI:
		case IFM_25G_KR1:
			key = IFM_25G_PCIE;
			break;
		case IFM_40G_CR4:
		case IFM_40G_SR4:
		case IFM_40G_LR4:
		case IFM_40G_XLPPI:
		case IFM_40G_KR4:
		case IFM_40G_XLAUI:
		case IFM_40G_XLAUI_AC:
		case IFM_40G_ER4:
			key = IFM_40G_CR4;
			break;
		case IFM_100G_CR4:
		case IFM_100G_SR4:
		case IFM_100G_KR4:
		case IFM_100G_LR4:
		case IFM_100G_CAUI4_AC:
		case IFM_100G_CAUI4:
		case IFM_100G_AUI4_AC:
		case IFM_100G_AUI4:
		case IFM_100G_CR_PAM4:
		case IFM_100G_KR_PAM4:
		case IFM_100G_CP2:
		case IFM_100G_SR2:
		case IFM_100G_DR:
		case IFM_100G_KR2_PAM4:
		case IFM_100G_CAUI2_AC:
		case IFM_100G_CAUI2:
		case IFM_100G_AUI2_AC:
		case IFM_100G_AUI2:
			key = IFM_100G_CR4;
			break;
		case IFM_200G_CR4_PAM4:
		case IFM_200G_SR4:
		case IFM_200G_FR4:
		case IFM_200G_LR4:
		case IFM_200G_DR4:
		case IFM_200G_KR4_PAM4:
		case IFM_200G_AUI4_AC:
		case IFM_200G_AUI4:
		case IFM_200G_AUI8_AC:
		case IFM_200G_AUI8:
			key = IFM_200G_CR4_PAM4;
			break;
		case IFM_400G_FR8:
		case IFM_400G_LR8:
		case IFM_400G_DR4:
		case IFM_400G_AUI8_AC:
		case IFM_400G_AUI8:
			key = IFM_400G_FR8;
			break;
		default:
			key = subtype;
			break;
		}
		/* bit 5..14:	(some bits of) if_index of lagg device */
		key |= 0x7fe0 & ((sc->sc_ifp->if_index) << 5);
		/* bit 15:	0 */
	}
	return (htons(key));
}