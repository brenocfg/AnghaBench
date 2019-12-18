#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
typedef  int u_int16_t ;
struct TYPE_11__ {scalar_t__** ctl_freqbin_2G; scalar_t__** ctl_freqbin_5G; TYPE_4__* ctl_power_data_5g; TYPE_2__* ctl_power_data_2g; } ;
typedef  TYPE_5__ ar9300_eeprom_t ;
struct TYPE_10__ {TYPE_3__* ctl_edges; } ;
struct TYPE_9__ {int t_power; scalar_t__ flag; } ;
struct TYPE_8__ {TYPE_1__* ctl_edges; } ;
struct TYPE_7__ {int t_power; scalar_t__ flag; } ;
typedef  int HAL_BOOL ;

/* Variables and functions */
 scalar_t__ AR9300_BCHAN_UNUSED ; 
 int AR9300_MAX_RATE_POWER ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int OSPREY_NUM_BAND_EDGES_2G ; 
 int OSPREY_NUM_BAND_EDGES_5G ; 
 int fbin2freq (scalar_t__,int) ; 

__attribute__((used)) static inline u_int16_t
ar9300_eep_def_get_max_edge_power(ar9300_eeprom_t *p_eep_data, u_int16_t freq,
    int idx, HAL_BOOL is_2ghz)
{
    u_int16_t twice_max_edge_power = AR9300_MAX_RATE_POWER;
    u_int8_t *ctl_freqbin = is_2ghz ?
        &p_eep_data->ctl_freqbin_2G[idx][0] :
        &p_eep_data->ctl_freqbin_5G[idx][0];
    u_int16_t num_edges = is_2ghz ?
        OSPREY_NUM_BAND_EDGES_2G : OSPREY_NUM_BAND_EDGES_5G;
    int i;

    /* Get the edge power */
    for (i = 0; (i < num_edges) && (ctl_freqbin[i] != AR9300_BCHAN_UNUSED); i++)
    {
        /*
         * If there's an exact channel match or an inband flag set
         * on the lower channel use the given rd_edge_power
         */
        if (freq == fbin2freq(ctl_freqbin[i], is_2ghz)) {
            if (is_2ghz) {
                twice_max_edge_power =
                    p_eep_data->ctl_power_data_2g[idx].ctl_edges[i].t_power;
            } else {       
                twice_max_edge_power =
                    p_eep_data->ctl_power_data_5g[idx].ctl_edges[i].t_power;
            }
            break;
        } else if ((i > 0) && (freq < fbin2freq(ctl_freqbin[i], is_2ghz))) {
            if (is_2ghz) {
                if (fbin2freq(ctl_freqbin[i - 1], 1) < freq &&
                    p_eep_data->ctl_power_data_2g[idx].ctl_edges[i - 1].flag)
                {
                    twice_max_edge_power =
                        p_eep_data->ctl_power_data_2g[idx].
                            ctl_edges[i - 1].t_power;
                }
            } else {
                if (fbin2freq(ctl_freqbin[i - 1], 0) < freq &&
                    p_eep_data->ctl_power_data_5g[idx].ctl_edges[i - 1].flag)
                {
                    twice_max_edge_power =
                        p_eep_data->ctl_power_data_5g[idx].
                            ctl_edges[i - 1].t_power;
                }
            }
            /*
             * Leave loop - no more affecting edges possible
             * in this monotonic increasing list
             */
            break;
        }
    }
    /*
     * EV89475: EEPROM might contain 0 txpower in CTL table for certain
     * 2.4GHz channels. We workaround it by overwriting 60 (30 dBm) here.
     */
    if (is_2ghz && (twice_max_edge_power == 0)) {
        twice_max_edge_power = 60;
    }

    HALASSERT(twice_max_edge_power > 0);
    return twice_max_edge_power;
}