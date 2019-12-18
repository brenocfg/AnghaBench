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
struct if_ath_ant_comb_state {int quick_scan_cnt; void* main_conf; void* first_quick_scan_conf; void* second_quick_scan_conf; int rssi_first; int rssi_second; int total_pkt_count; int rssi_third; int rssi_lna1; int rssi_lna2; void* second_ratio; void* first_ratio; void* scan; void* scan_not_start; void* alt_good; } ;
struct TYPE_3__ {void* main_lna_conf; void* alt_lna_conf; } ;
typedef  TYPE_1__ HAL_ANT_COMB_CONFIG ;

/* Variables and functions */
 void* AH_FALSE ; 
 void* AH_TRUE ; 
 int ATH_ANT_DIV_COMB_ALT_ANT_RATIO2 ; 
 int /*<<< orphan*/  ATH_ANT_DIV_COMB_LNA1_DELTA_HI ; 
 int /*<<< orphan*/  ATH_ANT_DIV_COMB_LNA1_DELTA_LOW ; 
 int /*<<< orphan*/  ATH_ANT_DIV_COMB_LNA1_DELTA_MID ; 
 int ATH_ANT_DIV_COMB_LNA1_LNA2_SWITCH_DELTA ; 
 void* HAL_ANT_DIV_COMB_LNA1 ; 
 void* HAL_ANT_DIV_COMB_LNA1_PLUS_LNA2 ; 
 void* HAL_ANT_DIV_COMB_LNA2 ; 
 int /*<<< orphan*/  ath_is_alt_ant_ratio_better (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
ath_select_ant_div_from_quick_scan(struct if_ath_ant_comb_state *antcomb,
    HAL_ANT_COMB_CONFIG *div_ant_conf, int main_rssi_avg,
    int alt_rssi_avg, int alt_ratio)
{
	/* alt_good */
	switch (antcomb->quick_scan_cnt) {
	case 0:
		/* set alt to main, and alt to first conf */
		div_ant_conf->main_lna_conf = antcomb->main_conf;
		div_ant_conf->alt_lna_conf = antcomb->first_quick_scan_conf;
		break;
	case 1:
		/* set alt to main, and alt to first conf */
		div_ant_conf->main_lna_conf = antcomb->main_conf;
		div_ant_conf->alt_lna_conf = antcomb->second_quick_scan_conf;
		antcomb->rssi_first = main_rssi_avg;
		antcomb->rssi_second = alt_rssi_avg;

		if (antcomb->main_conf == HAL_ANT_DIV_COMB_LNA1) {
			/* main is LNA1 */
			if (ath_is_alt_ant_ratio_better(alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_HI,
						ATH_ANT_DIV_COMB_LNA1_DELTA_LOW,
						main_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->first_ratio = AH_TRUE;
			else
				antcomb->first_ratio = AH_FALSE;
		} else if (antcomb->main_conf == HAL_ANT_DIV_COMB_LNA2) {
			if (ath_is_alt_ant_ratio_better(alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_MID,
						ATH_ANT_DIV_COMB_LNA1_DELTA_LOW,
						main_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->first_ratio = AH_TRUE;
			else
				antcomb->first_ratio = AH_FALSE;
		} else {
			if ((((alt_ratio >= ATH_ANT_DIV_COMB_ALT_ANT_RATIO2) &&
			    (alt_rssi_avg > main_rssi_avg +
			    ATH_ANT_DIV_COMB_LNA1_DELTA_HI)) ||
			    (alt_rssi_avg > main_rssi_avg)) &&
			    (antcomb->total_pkt_count > 50))
				antcomb->first_ratio = AH_TRUE;
			else
				antcomb->first_ratio = AH_FALSE;
		}
		break;
	case 2:
		antcomb->alt_good = AH_FALSE;
		antcomb->scan_not_start = AH_FALSE;
		antcomb->scan = AH_FALSE;
		antcomb->rssi_first = main_rssi_avg;
		antcomb->rssi_third = alt_rssi_avg;

		if (antcomb->second_quick_scan_conf == HAL_ANT_DIV_COMB_LNA1)
			antcomb->rssi_lna1 = alt_rssi_avg;
		else if (antcomb->second_quick_scan_conf ==
			 HAL_ANT_DIV_COMB_LNA2)
			antcomb->rssi_lna2 = alt_rssi_avg;
		else if (antcomb->second_quick_scan_conf ==
			 HAL_ANT_DIV_COMB_LNA1_PLUS_LNA2) {
			if (antcomb->main_conf == HAL_ANT_DIV_COMB_LNA2)
				antcomb->rssi_lna2 = main_rssi_avg;
			else if (antcomb->main_conf == HAL_ANT_DIV_COMB_LNA1)
				antcomb->rssi_lna1 = main_rssi_avg;
		}

		if (antcomb->rssi_lna2 > antcomb->rssi_lna1 +
		    ATH_ANT_DIV_COMB_LNA1_LNA2_SWITCH_DELTA)
			div_ant_conf->main_lna_conf = HAL_ANT_DIV_COMB_LNA2;
		else
			div_ant_conf->main_lna_conf = HAL_ANT_DIV_COMB_LNA1;

		if (antcomb->main_conf == HAL_ANT_DIV_COMB_LNA1) {
			if (ath_is_alt_ant_ratio_better(alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_HI,
						ATH_ANT_DIV_COMB_LNA1_DELTA_LOW,
						main_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->second_ratio = AH_TRUE;
			else
				antcomb->second_ratio = AH_FALSE;
		} else if (antcomb->main_conf == HAL_ANT_DIV_COMB_LNA2) {
			if (ath_is_alt_ant_ratio_better(alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_MID,
						ATH_ANT_DIV_COMB_LNA1_DELTA_LOW,
						main_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->second_ratio = AH_TRUE;
			else
				antcomb->second_ratio = AH_FALSE;
		} else {
			if ((((alt_ratio >= ATH_ANT_DIV_COMB_ALT_ANT_RATIO2) &&
			    (alt_rssi_avg > main_rssi_avg +
			    ATH_ANT_DIV_COMB_LNA1_DELTA_HI)) ||
			    (alt_rssi_avg > main_rssi_avg)) &&
			    (antcomb->total_pkt_count > 50))
				antcomb->second_ratio = AH_TRUE;
			else
				antcomb->second_ratio = AH_FALSE;
		}

		/* set alt to the conf with maximun ratio */
		if (antcomb->first_ratio && antcomb->second_ratio) {
			if (antcomb->rssi_second > antcomb->rssi_third) {
				/* first alt*/
				if ((antcomb->first_quick_scan_conf ==
				    HAL_ANT_DIV_COMB_LNA1) ||
				    (antcomb->first_quick_scan_conf ==
				    HAL_ANT_DIV_COMB_LNA2))
					/* Set alt LNA1 or LNA2*/
					if (div_ant_conf->main_lna_conf ==
					    HAL_ANT_DIV_COMB_LNA2)
						div_ant_conf->alt_lna_conf =
							HAL_ANT_DIV_COMB_LNA1;
					else
						div_ant_conf->alt_lna_conf =
							HAL_ANT_DIV_COMB_LNA2;
				else
					/* Set alt to A+B or A-B */
					div_ant_conf->alt_lna_conf =
						antcomb->first_quick_scan_conf;
			} else if ((antcomb->second_quick_scan_conf ==
				   HAL_ANT_DIV_COMB_LNA1) ||
				   (antcomb->second_quick_scan_conf ==
				   HAL_ANT_DIV_COMB_LNA2)) {
				/* Set alt LNA1 or LNA2 */
				if (div_ant_conf->main_lna_conf ==
				    HAL_ANT_DIV_COMB_LNA2)
					div_ant_conf->alt_lna_conf =
						HAL_ANT_DIV_COMB_LNA1;
				else
					div_ant_conf->alt_lna_conf =
						HAL_ANT_DIV_COMB_LNA2;
			} else {
				/* Set alt to A+B or A-B */
				div_ant_conf->alt_lna_conf =
					antcomb->second_quick_scan_conf;
			}
		} else if (antcomb->first_ratio) {
			/* first alt */
			if ((antcomb->first_quick_scan_conf ==
			    HAL_ANT_DIV_COMB_LNA1) ||
			    (antcomb->first_quick_scan_conf ==
			    HAL_ANT_DIV_COMB_LNA2))
					/* Set alt LNA1 or LNA2 */
				if (div_ant_conf->main_lna_conf ==
				    HAL_ANT_DIV_COMB_LNA2)
					div_ant_conf->alt_lna_conf =
							HAL_ANT_DIV_COMB_LNA1;
				else
					div_ant_conf->alt_lna_conf =
							HAL_ANT_DIV_COMB_LNA2;
			else
				/* Set alt to A+B or A-B */
				div_ant_conf->alt_lna_conf =
						antcomb->first_quick_scan_conf;
		} else if (antcomb->second_ratio) {
				/* second alt */
			if ((antcomb->second_quick_scan_conf ==
			    HAL_ANT_DIV_COMB_LNA1) ||
			    (antcomb->second_quick_scan_conf ==
			    HAL_ANT_DIV_COMB_LNA2))
				/* Set alt LNA1 or LNA2 */
				if (div_ant_conf->main_lna_conf ==
				    HAL_ANT_DIV_COMB_LNA2)
					div_ant_conf->alt_lna_conf =
						HAL_ANT_DIV_COMB_LNA1;
				else
					div_ant_conf->alt_lna_conf =
						HAL_ANT_DIV_COMB_LNA2;
			else
				/* Set alt to A+B or A-B */
				div_ant_conf->alt_lna_conf =
						antcomb->second_quick_scan_conf;
		} else {
			/* main is largest */
			if ((antcomb->main_conf == HAL_ANT_DIV_COMB_LNA1) ||
			    (antcomb->main_conf == HAL_ANT_DIV_COMB_LNA2))
				/* Set alt LNA1 or LNA2 */
				if (div_ant_conf->main_lna_conf ==
				    HAL_ANT_DIV_COMB_LNA2)
					div_ant_conf->alt_lna_conf =
							HAL_ANT_DIV_COMB_LNA1;
				else
					div_ant_conf->alt_lna_conf =
							HAL_ANT_DIV_COMB_LNA2;
			else
				/* Set alt to A+B or A-B */
				div_ant_conf->alt_lna_conf = antcomb->main_conf;
		}
		break;
	default:
		break;
	}
}