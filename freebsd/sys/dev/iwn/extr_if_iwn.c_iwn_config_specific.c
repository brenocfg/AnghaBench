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
typedef  int uint16_t ;
struct iwn_softc {char* fwname; int /*<<< orphan*/  hw_type; int /*<<< orphan*/  subdevice_id; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * base_params; int /*<<< orphan*/ * limits; void* rxchainmask; void* txchainmask; int /*<<< orphan*/  sc_flags; } ;

/* Variables and functions */
 int ENOTSUP ; 
 void* IWN_ANT_AB ; 
 void* IWN_ANT_ABC ; 
 void* IWN_ANT_B ; 
 void* IWN_ANT_BC ; 
#define  IWN_DID_1000_1 314 
#define  IWN_DID_1000_2 313 
#define  IWN_DID_100_1 312 
#define  IWN_DID_100_2 311 
#define  IWN_DID_105_1 310 
#define  IWN_DID_105_2 309 
#define  IWN_DID_130_1 308 
#define  IWN_DID_130_2 307 
#define  IWN_DID_135_1 306 
#define  IWN_DID_135_2 305 
#define  IWN_DID_2x00_1 304 
#define  IWN_DID_2x00_2 303 
#define  IWN_DID_2x30_1 302 
#define  IWN_DID_2x30_2 301 
#define  IWN_DID_4965_1 300 
#define  IWN_DID_4965_2 299 
#define  IWN_DID_4965_3 298 
#define  IWN_DID_4965_4 297 
#define  IWN_DID_5x00_1 296 
#define  IWN_DID_5x00_2 295 
#define  IWN_DID_5x00_3 294 
#define  IWN_DID_5x00_4 293 
#define  IWN_DID_5x50_1 292 
#define  IWN_DID_5x50_2 291 
#define  IWN_DID_5x50_3 290 
#define  IWN_DID_5x50_4 289 
#define  IWN_DID_6035_1 288 
#define  IWN_DID_6035_2 287 
#define  IWN_DID_6050_1 286 
#define  IWN_DID_6050_2 285 
#define  IWN_DID_6150_1 284 
#define  IWN_DID_6150_2 283 
#define  IWN_DID_6x00_1 282 
#define  IWN_DID_6x00_2 281 
#define  IWN_DID_6x00_3 280 
#define  IWN_DID_6x00_4 279 
#define  IWN_DID_6x05_1 278 
#define  IWN_DID_6x05_2 277 
#define  IWN_DID_x030_1 276 
#define  IWN_DID_x030_2 275 
#define  IWN_DID_x030_3 274 
#define  IWN_DID_x030_4 273 
 int /*<<< orphan*/  IWN_FLAG_BTCOEX ; 
 int /*<<< orphan*/  IWN_FLAG_INTERNAL_PA ; 
#define  IWN_SDID_1000_1 272 
#define  IWN_SDID_1000_10 271 
#define  IWN_SDID_1000_11 270 
#define  IWN_SDID_1000_12 269 
#define  IWN_SDID_1000_2 268 
#define  IWN_SDID_1000_3 267 
#define  IWN_SDID_1000_4 266 
#define  IWN_SDID_1000_5 265 
#define  IWN_SDID_1000_6 264 
#define  IWN_SDID_1000_7 263 
#define  IWN_SDID_1000_8 262 
#define  IWN_SDID_1000_9 261 
#define  IWN_SDID_100_1 260 
#define  IWN_SDID_100_2 259 
#define  IWN_SDID_100_3 258 
#define  IWN_SDID_100_4 257 
#define  IWN_SDID_100_5 256 
#define  IWN_SDID_100_6 255 
#define  IWN_SDID_105_1 254 
#define  IWN_SDID_105_2 253 
#define  IWN_SDID_105_3 252 
#define  IWN_SDID_105_4 251 
#define  IWN_SDID_130_1 250 
#define  IWN_SDID_130_2 249 
#define  IWN_SDID_130_3 248 
#define  IWN_SDID_130_4 247 
#define  IWN_SDID_130_5 246 
#define  IWN_SDID_130_6 245 
#define  IWN_SDID_135_1 244 
#define  IWN_SDID_135_2 243 
#define  IWN_SDID_135_3 242 
#define  IWN_SDID_2x00_1 241 
#define  IWN_SDID_2x00_2 240 
#define  IWN_SDID_2x00_3 239 
#define  IWN_SDID_2x00_4 238 
#define  IWN_SDID_2x30_1 237 
#define  IWN_SDID_2x30_2 236 
#define  IWN_SDID_2x30_3 235 
#define  IWN_SDID_2x30_4 234 
#define  IWN_SDID_2x30_5 233 
#define  IWN_SDID_2x30_6 232 
#define  IWN_SDID_5x00_1 231 
#define  IWN_SDID_5x00_10 230 
#define  IWN_SDID_5x00_11 229 
#define  IWN_SDID_5x00_12 228 
#define  IWN_SDID_5x00_13 227 
#define  IWN_SDID_5x00_14 226 
#define  IWN_SDID_5x00_15 225 
#define  IWN_SDID_5x00_16 224 
#define  IWN_SDID_5x00_17 223 
#define  IWN_SDID_5x00_18 222 
#define  IWN_SDID_5x00_19 221 
#define  IWN_SDID_5x00_2 220 
#define  IWN_SDID_5x00_20 219 
#define  IWN_SDID_5x00_21 218 
#define  IWN_SDID_5x00_22 217 
#define  IWN_SDID_5x00_23 216 
#define  IWN_SDID_5x00_24 215 
#define  IWN_SDID_5x00_25 214 
#define  IWN_SDID_5x00_26 213 
#define  IWN_SDID_5x00_27 212 
#define  IWN_SDID_5x00_28 211 
#define  IWN_SDID_5x00_29 210 
#define  IWN_SDID_5x00_3 209 
#define  IWN_SDID_5x00_30 208 
#define  IWN_SDID_5x00_31 207 
#define  IWN_SDID_5x00_32 206 
#define  IWN_SDID_5x00_33 205 
#define  IWN_SDID_5x00_34 204 
#define  IWN_SDID_5x00_35 203 
#define  IWN_SDID_5x00_36 202 
#define  IWN_SDID_5x00_4 201 
#define  IWN_SDID_5x00_5 200 
#define  IWN_SDID_5x00_6 199 
#define  IWN_SDID_5x00_7 198 
#define  IWN_SDID_5x00_8 197 
#define  IWN_SDID_5x00_9 196 
#define  IWN_SDID_5x50_1 195 
#define  IWN_SDID_5x50_10 194 
#define  IWN_SDID_5x50_11 193 
#define  IWN_SDID_5x50_12 192 
#define  IWN_SDID_5x50_13 191 
#define  IWN_SDID_5x50_2 190 
#define  IWN_SDID_5x50_3 189 
#define  IWN_SDID_5x50_4 188 
#define  IWN_SDID_5x50_5 187 
#define  IWN_SDID_5x50_6 186 
#define  IWN_SDID_5x50_7 185 
#define  IWN_SDID_5x50_8 184 
#define  IWN_SDID_5x50_9 183 
#define  IWN_SDID_6035_1 182 
#define  IWN_SDID_6035_2 181 
#define  IWN_SDID_6035_3 180 
#define  IWN_SDID_6035_4 179 
#define  IWN_SDID_6035_5 178 
#define  IWN_SDID_6050_1 177 
#define  IWN_SDID_6050_2 176 
#define  IWN_SDID_6050_3 175 
#define  IWN_SDID_6050_4 174 
#define  IWN_SDID_6050_5 173 
#define  IWN_SDID_6050_6 172 
#define  IWN_SDID_6150_1 171 
#define  IWN_SDID_6150_2 170 
#define  IWN_SDID_6150_3 169 
#define  IWN_SDID_6150_4 168 
#define  IWN_SDID_6150_5 167 
#define  IWN_SDID_6150_6 166 
#define  IWN_SDID_6x00_1 165 
#define  IWN_SDID_6x00_10 164 
#define  IWN_SDID_6x00_2 163 
#define  IWN_SDID_6x00_3 162 
#define  IWN_SDID_6x00_4 161 
#define  IWN_SDID_6x00_5 160 
#define  IWN_SDID_6x00_6 159 
#define  IWN_SDID_6x00_7 158 
#define  IWN_SDID_6x00_8 157 
#define  IWN_SDID_6x00_9 156 
#define  IWN_SDID_6x05_1 155 
#define  IWN_SDID_6x05_10 154 
#define  IWN_SDID_6x05_11 153 
#define  IWN_SDID_6x05_12 152 
#define  IWN_SDID_6x05_2 151 
#define  IWN_SDID_6x05_3 150 
#define  IWN_SDID_6x05_4 149 
#define  IWN_SDID_6x05_5 148 
#define  IWN_SDID_6x05_6 147 
#define  IWN_SDID_6x05_7 146 
#define  IWN_SDID_6x05_8 145 
#define  IWN_SDID_6x05_9 144 
#define  IWN_SDID_x030_1 143 
#define  IWN_SDID_x030_10 142 
#define  IWN_SDID_x030_11 141 
#define  IWN_SDID_x030_12 140 
#define  IWN_SDID_x030_13 139 
#define  IWN_SDID_x030_14 138 
#define  IWN_SDID_x030_15 137 
#define  IWN_SDID_x030_16 136 
#define  IWN_SDID_x030_2 135 
#define  IWN_SDID_x030_3 134 
#define  IWN_SDID_x030_4 133 
#define  IWN_SDID_x030_5 132 
#define  IWN_SDID_x030_6 131 
#define  IWN_SDID_x030_7 130 
#define  IWN_SDID_x030_8 129 
#define  IWN_SDID_x030_9 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwn1000_base_params ; 
 int /*<<< orphan*/  iwn1000_sensitivity_limits ; 
 int /*<<< orphan*/  iwn2000_base_params ; 
 int /*<<< orphan*/  iwn2030_base_params ; 
 int /*<<< orphan*/  iwn2030_sensitivity_limits ; 
 int /*<<< orphan*/  iwn4965_base_params ; 
 int /*<<< orphan*/  iwn4965_sensitivity_limits ; 
 int /*<<< orphan*/  iwn5000_base_params ; 
 int /*<<< orphan*/  iwn5000_sensitivity_limits ; 
 int /*<<< orphan*/  iwn6000_sensitivity_limits ; 
 int /*<<< orphan*/  iwn6235_sensitivity_limits ; 
 int /*<<< orphan*/  iwn_5x50_base_params ; 
 int /*<<< orphan*/  iwn_6000_base_params ; 
 int /*<<< orphan*/  iwn_6000g2_base_params ; 
 int /*<<< orphan*/  iwn_6000g2b_base_params ; 
 int /*<<< orphan*/  iwn_6000i_base_params ; 
 int /*<<< orphan*/  iwn_6050_base_params ; 
 int /*<<< orphan*/  iwn_6150_base_params ; 
 int /*<<< orphan*/  iwn_6235_base_params ; 

__attribute__((used)) static int
iwn_config_specific(struct iwn_softc *sc, uint16_t pid)
{

	switch (pid) {
/* 4965 series */
	case IWN_DID_4965_1:
	case IWN_DID_4965_2:
	case IWN_DID_4965_3:
	case IWN_DID_4965_4:
		sc->base_params = &iwn4965_base_params;
		sc->limits = &iwn4965_sensitivity_limits;
		sc->fwname = "iwn4965fw";
		/* Override chains masks, ROM is known to be broken. */
		sc->txchainmask = IWN_ANT_AB;
		sc->rxchainmask = IWN_ANT_ABC;
		/* Enable normal btcoex */
		sc->sc_flags |= IWN_FLAG_BTCOEX;
		break;
/* 1000 Series */
	case IWN_DID_1000_1:
	case IWN_DID_1000_2:
		switch(sc->subdevice_id) {
			case	IWN_SDID_1000_1:
			case	IWN_SDID_1000_2:
			case	IWN_SDID_1000_3:
			case	IWN_SDID_1000_4:
			case	IWN_SDID_1000_5:
			case	IWN_SDID_1000_6:
			case	IWN_SDID_1000_7:
			case	IWN_SDID_1000_8:
			case	IWN_SDID_1000_9:
			case	IWN_SDID_1000_10:
			case	IWN_SDID_1000_11:
			case	IWN_SDID_1000_12:
				sc->limits = &iwn1000_sensitivity_limits;
				sc->base_params = &iwn1000_base_params;
				sc->fwname = "iwn1000fw";
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;
/* 6x00 Series */
	case IWN_DID_6x00_2:
	case IWN_DID_6x00_4:
	case IWN_DID_6x00_1:
	case IWN_DID_6x00_3:
		sc->fwname = "iwn6000fw";
		sc->limits = &iwn6000_sensitivity_limits;
		switch(sc->subdevice_id) {
			case IWN_SDID_6x00_1:
			case IWN_SDID_6x00_2:
			case IWN_SDID_6x00_8:
				//iwl6000_3agn_cfg
				sc->base_params = &iwn_6000_base_params;
				break;
			case IWN_SDID_6x00_3:
			case IWN_SDID_6x00_6:
			case IWN_SDID_6x00_9:
				////iwl6000i_2agn
			case IWN_SDID_6x00_4:
			case IWN_SDID_6x00_7:
			case IWN_SDID_6x00_10:
				//iwl6000i_2abg_cfg
			case IWN_SDID_6x00_5:
				//iwl6000i_2bg_cfg
				sc->base_params = &iwn_6000i_base_params;
				sc->sc_flags |= IWN_FLAG_INTERNAL_PA;
				sc->txchainmask = IWN_ANT_BC;
				sc->rxchainmask = IWN_ANT_BC;
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;
/* 6x05 Series */
	case IWN_DID_6x05_1:
	case IWN_DID_6x05_2:
		switch(sc->subdevice_id) {
			case IWN_SDID_6x05_1:
			case IWN_SDID_6x05_4:
			case IWN_SDID_6x05_6:
				//iwl6005_2agn_cfg
			case IWN_SDID_6x05_2:
			case IWN_SDID_6x05_5:
			case IWN_SDID_6x05_7:
				//iwl6005_2abg_cfg
			case IWN_SDID_6x05_3:
				//iwl6005_2bg_cfg
			case IWN_SDID_6x05_8:
			case IWN_SDID_6x05_9:
				//iwl6005_2agn_sff_cfg
			case IWN_SDID_6x05_10:
				//iwl6005_2agn_d_cfg
			case IWN_SDID_6x05_11:
				//iwl6005_2agn_mow1_cfg
			case IWN_SDID_6x05_12:
				//iwl6005_2agn_mow2_cfg
				sc->fwname = "iwn6000g2afw";
				sc->limits = &iwn6000_sensitivity_limits;
				sc->base_params = &iwn_6000g2_base_params;
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;
/* 6x35 Series */
	case IWN_DID_6035_1:
	case IWN_DID_6035_2:
		switch(sc->subdevice_id) {
			case IWN_SDID_6035_1:
			case IWN_SDID_6035_2:
			case IWN_SDID_6035_3:
			case IWN_SDID_6035_4:
			case IWN_SDID_6035_5:
				sc->fwname = "iwn6000g2bfw";
				sc->limits = &iwn6235_sensitivity_limits;
				sc->base_params = &iwn_6235_base_params;
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;
/* 6x50 WiFi/WiMax Series */
	case IWN_DID_6050_1:
	case IWN_DID_6050_2:
		switch(sc->subdevice_id) {
			case IWN_SDID_6050_1:
			case IWN_SDID_6050_3:
			case IWN_SDID_6050_5:
				//iwl6050_2agn_cfg
			case IWN_SDID_6050_2:
			case IWN_SDID_6050_4:
			case IWN_SDID_6050_6:
				//iwl6050_2abg_cfg
				sc->fwname = "iwn6050fw";
				sc->txchainmask = IWN_ANT_AB;
				sc->rxchainmask = IWN_ANT_AB;
				sc->limits = &iwn6000_sensitivity_limits;
				sc->base_params = &iwn_6050_base_params;
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;
/* 6150 WiFi/WiMax Series */
	case IWN_DID_6150_1:
	case IWN_DID_6150_2:
		switch(sc->subdevice_id) {
			case IWN_SDID_6150_1:
			case IWN_SDID_6150_3:
			case IWN_SDID_6150_5:
				// iwl6150_bgn_cfg
			case IWN_SDID_6150_2:
			case IWN_SDID_6150_4:
			case IWN_SDID_6150_6:
				//iwl6150_bg_cfg
				sc->fwname = "iwn6050fw";
				sc->limits = &iwn6000_sensitivity_limits;
				sc->base_params = &iwn_6150_base_params;
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;
/* 6030 Series and 1030 Series */
	case IWN_DID_x030_1:
	case IWN_DID_x030_2:
	case IWN_DID_x030_3:
	case IWN_DID_x030_4:
		switch(sc->subdevice_id) {
			case IWN_SDID_x030_1:
			case IWN_SDID_x030_3:
			case IWN_SDID_x030_5:
			// iwl1030_bgn_cfg
			case IWN_SDID_x030_2:
			case IWN_SDID_x030_4:
			case IWN_SDID_x030_6:
			//iwl1030_bg_cfg
			case IWN_SDID_x030_7:
			case IWN_SDID_x030_10:
			case IWN_SDID_x030_14:
			//iwl6030_2agn_cfg
			case IWN_SDID_x030_8:
			case IWN_SDID_x030_11:
			case IWN_SDID_x030_15:
			// iwl6030_2bgn_cfg
			case IWN_SDID_x030_9:
			case IWN_SDID_x030_12:
			case IWN_SDID_x030_16:
			// iwl6030_2abg_cfg
			case IWN_SDID_x030_13:
			//iwl6030_2bg_cfg
				sc->fwname = "iwn6000g2bfw";
				sc->limits = &iwn6000_sensitivity_limits;
				sc->base_params = &iwn_6000g2b_base_params;
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;
/* 130 Series WiFi */
/* XXX: This series will need adjustment for rate.
 * see rx_with_siso_diversity in linux kernel
 */
	case IWN_DID_130_1:
	case IWN_DID_130_2:
		switch(sc->subdevice_id) {
			case IWN_SDID_130_1:
			case IWN_SDID_130_3:
			case IWN_SDID_130_5:
			//iwl130_bgn_cfg
			case IWN_SDID_130_2:
			case IWN_SDID_130_4:
			case IWN_SDID_130_6:
			//iwl130_bg_cfg
				sc->fwname = "iwn6000g2bfw";
				sc->limits = &iwn6000_sensitivity_limits;
				sc->base_params = &iwn_6000g2b_base_params;
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;
/* 100 Series WiFi */
	case IWN_DID_100_1:
	case IWN_DID_100_2:
		switch(sc->subdevice_id) {
			case IWN_SDID_100_1:
			case IWN_SDID_100_2:
			case IWN_SDID_100_3:
			case IWN_SDID_100_4:
			case IWN_SDID_100_5:
			case IWN_SDID_100_6:
				sc->limits = &iwn1000_sensitivity_limits;
				sc->base_params = &iwn1000_base_params;
				sc->fwname = "iwn100fw";
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;

/* 105 Series */
/* XXX: This series will need adjustment for rate.
 * see rx_with_siso_diversity in linux kernel
 */
	case IWN_DID_105_1:
	case IWN_DID_105_2:
		switch(sc->subdevice_id) {
			case IWN_SDID_105_1:
			case IWN_SDID_105_2:
			case IWN_SDID_105_3:
			//iwl105_bgn_cfg
			case IWN_SDID_105_4:
			//iwl105_bgn_d_cfg
				sc->limits = &iwn2030_sensitivity_limits;
				sc->base_params = &iwn2000_base_params;
				sc->fwname = "iwn105fw";
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;

/* 135 Series */
/* XXX: This series will need adjustment for rate.
 * see rx_with_siso_diversity in linux kernel
 */
	case IWN_DID_135_1:
	case IWN_DID_135_2:
		switch(sc->subdevice_id) {
			case IWN_SDID_135_1:
			case IWN_SDID_135_2:
			case IWN_SDID_135_3:
				sc->limits = &iwn2030_sensitivity_limits;
				sc->base_params = &iwn2030_base_params;
				sc->fwname = "iwn135fw";
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;

/* 2x00 Series */
	case IWN_DID_2x00_1:
	case IWN_DID_2x00_2:
		switch(sc->subdevice_id) {
			case IWN_SDID_2x00_1:
			case IWN_SDID_2x00_2:
			case IWN_SDID_2x00_3:
			//iwl2000_2bgn_cfg
			case IWN_SDID_2x00_4:
			//iwl2000_2bgn_d_cfg
				sc->limits = &iwn2030_sensitivity_limits;
				sc->base_params = &iwn2000_base_params;
				sc->fwname = "iwn2000fw";
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice) \n",
				    pid, sc->subdevice_id, sc->hw_type);
				return ENOTSUP;
		}
		break;
/* 2x30 Series */
	case IWN_DID_2x30_1:
	case IWN_DID_2x30_2:
		switch(sc->subdevice_id) {
			case IWN_SDID_2x30_1:
			case IWN_SDID_2x30_3:
			case IWN_SDID_2x30_5:
			//iwl100_bgn_cfg
			case IWN_SDID_2x30_2:
			case IWN_SDID_2x30_4:
			case IWN_SDID_2x30_6:
			//iwl100_bg_cfg
				sc->limits = &iwn2030_sensitivity_limits;
				sc->base_params = &iwn2030_base_params;
				sc->fwname = "iwn2030fw";
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;
/* 5x00 Series */
	case IWN_DID_5x00_1:
	case IWN_DID_5x00_2:
	case IWN_DID_5x00_3:
	case IWN_DID_5x00_4:
		sc->limits = &iwn5000_sensitivity_limits;
		sc->base_params = &iwn5000_base_params;
		sc->fwname = "iwn5000fw";
		switch(sc->subdevice_id) {
			case IWN_SDID_5x00_1:
			case IWN_SDID_5x00_2:
			case IWN_SDID_5x00_3:
			case IWN_SDID_5x00_4:
			case IWN_SDID_5x00_9:
			case IWN_SDID_5x00_10:
			case IWN_SDID_5x00_11:
			case IWN_SDID_5x00_12:
			case IWN_SDID_5x00_17:
			case IWN_SDID_5x00_18:
			case IWN_SDID_5x00_19:
			case IWN_SDID_5x00_20:
			//iwl5100_agn_cfg
				sc->txchainmask = IWN_ANT_B;
				sc->rxchainmask = IWN_ANT_AB;
				break;
			case IWN_SDID_5x00_5:
			case IWN_SDID_5x00_6:
			case IWN_SDID_5x00_13:
			case IWN_SDID_5x00_14:
			case IWN_SDID_5x00_21:
			case IWN_SDID_5x00_22:
			//iwl5100_bgn_cfg
				sc->txchainmask = IWN_ANT_B;
				sc->rxchainmask = IWN_ANT_AB;
				break;
			case IWN_SDID_5x00_7:
			case IWN_SDID_5x00_8:
			case IWN_SDID_5x00_15:
			case IWN_SDID_5x00_16:
			case IWN_SDID_5x00_23:
			case IWN_SDID_5x00_24:
			//iwl5100_abg_cfg
				sc->txchainmask = IWN_ANT_B;
				sc->rxchainmask = IWN_ANT_AB;
				break;
			case IWN_SDID_5x00_25:
			case IWN_SDID_5x00_26:
			case IWN_SDID_5x00_27:
			case IWN_SDID_5x00_28:
			case IWN_SDID_5x00_29:
			case IWN_SDID_5x00_30:
			case IWN_SDID_5x00_31:
			case IWN_SDID_5x00_32:
			case IWN_SDID_5x00_33:
			case IWN_SDID_5x00_34:
			case IWN_SDID_5x00_35:
			case IWN_SDID_5x00_36:
			//iwl5300_agn_cfg
				sc->txchainmask = IWN_ANT_ABC;
				sc->rxchainmask = IWN_ANT_ABC;
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;
/* 5x50 Series */
	case IWN_DID_5x50_1:
	case IWN_DID_5x50_2:
	case IWN_DID_5x50_3:
	case IWN_DID_5x50_4:
		sc->limits = &iwn5000_sensitivity_limits;
		sc->base_params = &iwn5000_base_params;
		sc->fwname = "iwn5000fw";
		switch(sc->subdevice_id) {
			case IWN_SDID_5x50_1:
			case IWN_SDID_5x50_2:
			case IWN_SDID_5x50_3:
			//iwl5350_agn_cfg
				sc->limits = &iwn5000_sensitivity_limits;
				sc->base_params = &iwn5000_base_params;
				sc->fwname = "iwn5000fw";
				break;
			case IWN_SDID_5x50_4:
			case IWN_SDID_5x50_5:
			case IWN_SDID_5x50_8:
			case IWN_SDID_5x50_9:
			case IWN_SDID_5x50_10:
			case IWN_SDID_5x50_11:
			//iwl5150_agn_cfg
			case IWN_SDID_5x50_6:
			case IWN_SDID_5x50_7:
			case IWN_SDID_5x50_12:
			case IWN_SDID_5x50_13:
			//iwl5150_abg_cfg
				sc->limits = &iwn5000_sensitivity_limits;
				sc->fwname = "iwn5150fw";
				sc->base_params = &iwn_5x50_base_params;
				break;
			default:
				device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id :"
				    "0x%04x rev %d not supported (subdevice)\n", pid,
				    sc->subdevice_id,sc->hw_type);
				return ENOTSUP;
		}
		break;
	default:
		device_printf(sc->sc_dev, "adapter type id : 0x%04x sub id : 0x%04x"
		    "rev 0x%08x not supported (device)\n", pid, sc->subdevice_id,
		     sc->hw_type);
		return ENOTSUP;
	}
	return 0;
}