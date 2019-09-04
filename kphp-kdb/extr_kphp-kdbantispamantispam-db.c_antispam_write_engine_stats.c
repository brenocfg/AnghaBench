#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int chain_len_sum; double chain_cnt; int chain_len_max; } ;
typedef  TYPE_1__ st_hash_map_stats_t ;

/* Variables and functions */
 double ST_HASH_SET_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  id_to_pattern ; 
 TYPE_1__ id_to_pattern_get_stats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 double stats_all_matches_cnt ; 
 double stats_matches_cnt ; 
 int stats_matches_max ; 
 double stats_matches_sum ; 
 int /*<<< orphan*/  triple_to_pattern ; 
 TYPE_1__ triple_to_patterns_get_stats (int /*<<< orphan*/ ) ; 

void antispam_write_engine_stats (char** first, char* last) {
  st_hash_map_stats_t hm1_stats = id_to_pattern_get_stats (id_to_pattern);
  st_hash_map_stats_t hm2_stats = triple_to_patterns_get_stats (triple_to_pattern);

  #define WSL(name, format, value)  \
    assert (last - *first >= 1000); \
    *first += sprintf (*first, "%s\t" format, name, value); \

  #define W_HT_STATS(name, stats)                                                        \
    WSL (#name "_filled", "%.4f%%\n", 100.0 * (stats).chain_len_sum / ST_HASH_SET_SIZE); \
    *first += sprintf (*first, "%s\t%.4f/%d\n", #name"_chains",                          \
      (stats).chain_cnt == 0 ? 0.0 : (double)(stats).chain_len_sum / (stats).chain_cnt,  \
      (stats).chain_len_max);

  WSL ("patterns_cnt",  "%d\n", hm1_stats.chain_len_sum);
  WSL ("matching_probability", "%.4f%%\n", stats_all_matches_cnt == 0 ? 0.0 :
    100.0 * stats_matches_cnt / stats_all_matches_cnt);
  *first += sprintf (*first, "matches_cnt(mean/max)\t%.4f/%d\n",
    stats_matches_cnt == 0 ? 0.0 : stats_matches_sum / stats_matches_cnt,
    stats_matches_max);
  W_HT_STATS (id_to_pattern, hm1_stats);
  W_HT_STATS (triple_to_patterns, hm2_stats);

  #undef WSL
  #undef W_HT_STATS
}