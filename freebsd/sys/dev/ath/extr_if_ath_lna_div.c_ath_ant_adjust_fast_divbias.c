#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct if_ath_ant_comb_state {int /*<<< orphan*/  scan; } ;
struct TYPE_3__ {int main_lna_conf; int alt_lna_conf; int fast_div_bias; int /*<<< orphan*/  alt_gaintb; int /*<<< orphan*/  main_gaintb; } ;
typedef  TYPE_1__ HAL_ANT_COMB_CONFIG ;

/* Variables and functions */
 int ATH_ANT_DIV_COMB_ALT_ANT_RATIO ; 
 scalar_t__ HAL_ANTDIV_CONFIG_GROUP_1 ; 
 scalar_t__ HAL_ANTDIV_CONFIG_GROUP_2 ; 

__attribute__((used)) static void
ath_ant_adjust_fast_divbias(struct if_ath_ant_comb_state *antcomb,
    int alt_ratio, int alt_ant_ratio_th, u_int config_group,
    HAL_ANT_COMB_CONFIG *pdiv_ant_conf)
{

	if (config_group == HAL_ANTDIV_CONFIG_GROUP_1) {
		switch ((pdiv_ant_conf->main_lna_conf << 4)
		    | pdiv_ant_conf->alt_lna_conf) {
		case (0x01): //A-B LNA2
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x02): //A-B LNA1
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x03): //A-B A+B
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x10): //LNA2 A-B
			if ((antcomb->scan == 0)
			    && (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO)) {
				pdiv_ant_conf->fast_div_bias = 0x3f;
			} else {
				pdiv_ant_conf->fast_div_bias = 0x1;
			}
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x12): //LNA2 LNA1
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
			case (0x13): //LNA2 A+B
			if ((antcomb->scan == 0)
			    && (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO)) {
				pdiv_ant_conf->fast_div_bias = 0x3f;
			} else {
				pdiv_ant_conf->fast_div_bias = 0x1;
			}
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x20): //LNA1 A-B
			if ((antcomb->scan == 0)
			    && (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO)) {
				pdiv_ant_conf->fast_div_bias = 0x3f;
			} else {
				pdiv_ant_conf->fast_div_bias = 0x1;
			}
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x21): //LNA1 LNA2
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x23): //LNA1 A+B
			if ((antcomb->scan == 0)
			    && (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO)) {
				pdiv_ant_conf->fast_div_bias = 0x3f;
			} else {
				pdiv_ant_conf->fast_div_bias = 0x1;
			}
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x30): //A+B A-B
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x31): //A+B LNA2
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x32): //A+B LNA1
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		default:
			break;
		}
	} else if (config_group == HAL_ANTDIV_CONFIG_GROUP_2) {
		switch ((pdiv_ant_conf->main_lna_conf << 4)
		    | pdiv_ant_conf->alt_lna_conf) {
		case (0x01): //A-B LNA2
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x02): //A-B LNA1
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x03): //A-B A+B
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x10): //LNA2 A-B
			if ((antcomb->scan == 0)
			    && (alt_ratio > alt_ant_ratio_th)) {
				pdiv_ant_conf->fast_div_bias = 0x1;
			} else {
				pdiv_ant_conf->fast_div_bias = 0x2;
			}
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x12): //LNA2 LNA1
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x13): //LNA2 A+B
			if ((antcomb->scan == 0)
			    && (alt_ratio > alt_ant_ratio_th)) {
				pdiv_ant_conf->fast_div_bias = 0x1;
			} else {
				pdiv_ant_conf->fast_div_bias = 0x2;
			}
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x20): //LNA1 A-B
			if ((antcomb->scan == 0)
			    && (alt_ratio > alt_ant_ratio_th)) {
				pdiv_ant_conf->fast_div_bias = 0x1;
			} else {
				pdiv_ant_conf->fast_div_bias = 0x2;
			}
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x21): //LNA1 LNA2
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x23): //LNA1 A+B
			if ((antcomb->scan == 0)
			    && (alt_ratio > alt_ant_ratio_th)) {
				pdiv_ant_conf->fast_div_bias = 0x1;
			} else {
				pdiv_ant_conf->fast_div_bias = 0x2;
			}
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x30): //A+B A-B
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x31): //A+B LNA2
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		case (0x32): //A+B LNA1
			pdiv_ant_conf->fast_div_bias = 0x1;
			pdiv_ant_conf->main_gaintb   = 0;
			pdiv_ant_conf->alt_gaintb    = 0;
			break;
		default:
			break;
		}
	} else { /* DEFAULT_ANTDIV_CONFIG_GROUP */
		switch ((pdiv_ant_conf->main_lna_conf << 4) | pdiv_ant_conf->alt_lna_conf) {
		case (0x01): //A-B LNA2
			pdiv_ant_conf->fast_div_bias = 0x3b;
			break;
		case (0x02): //A-B LNA1
			pdiv_ant_conf->fast_div_bias = 0x3d;
			break;
		case (0x03): //A-B A+B
			pdiv_ant_conf->fast_div_bias = 0x1;
			break;
		case (0x10): //LNA2 A-B
			pdiv_ant_conf->fast_div_bias = 0x7;
			break;
		case (0x12): //LNA2 LNA1
			pdiv_ant_conf->fast_div_bias = 0x2;
			break;
		case (0x13): //LNA2 A+B
			pdiv_ant_conf->fast_div_bias = 0x7;
			break;
		case (0x20): //LNA1 A-B
			pdiv_ant_conf->fast_div_bias = 0x6;
			break;
		case (0x21): //LNA1 LNA2
			pdiv_ant_conf->fast_div_bias = 0x0;
			break;
		case (0x23): //LNA1 A+B
			pdiv_ant_conf->fast_div_bias = 0x6;
			break;
		case (0x30): //A+B A-B
			pdiv_ant_conf->fast_div_bias = 0x1;
			break;
		case (0x31): //A+B LNA2
			pdiv_ant_conf->fast_div_bias = 0x3b;
			break;
		case (0x32): //A+B LNA1
			pdiv_ant_conf->fast_div_bias = 0x3d;
			break;
		default:
			break;
		}
	}
}