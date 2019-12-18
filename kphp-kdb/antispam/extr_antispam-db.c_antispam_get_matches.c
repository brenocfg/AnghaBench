#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uahash_t ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ pattern_t ;
typedef  int /*<<< orphan*/  ip_t ;
typedef  int byte ;
struct TYPE_5__ {TYPE_1__** first; } ;

/* Variables and functions */
 int ANTISPAM_DB_FIELDS_FLAGS ; 
 int ANTISPAM_DB_FIELDS_IDS ; 
 int /*<<< orphan*/  antispam_db_request ; 
 int antispam_get_matches_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int antispam_get_matches_inc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_2__ heap_pattern ; 
 int /*<<< orphan*/  st_relax_max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st_vec_pb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_vec_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int st_vec_size (TYPE_2__) ; 
 int /*<<< orphan*/  stats_all_matches_cnt ; 
 int /*<<< orphan*/  stats_matches_cnt ; 
 int /*<<< orphan*/  stats_matches_max ; 
 int stats_matches_sum ; 

int antispam_get_matches (ip_t ip, uahash_t uahash, const char *text, byte fields, int limit) {
  int matches_cnt = 0;
  if (limit >= 0) {
    matches_cnt = antispam_get_matches_inc (ip, uahash, text, limit);
  } else {
    matches_cnt = antispam_get_matches_dec (ip, uahash, text, -limit);
  }

  st_vec_resize (antispam_db_request, 0);
  pattern_t **first = heap_pattern.first;
  pattern_t **last  = first + st_vec_size (heap_pattern);
  for (; first != last; ++first) {
    if (fields & ANTISPAM_DB_FIELDS_IDS) {
      st_vec_pb (antispam_db_request, (*first)->id);
    }
    if (fields & ANTISPAM_DB_FIELDS_FLAGS) {
      st_vec_pb (antispam_db_request, (*first)->flags);
    }
  }

  ++stats_all_matches_cnt;
  if (matches_cnt != 0) {
    ++stats_matches_cnt;
    stats_matches_sum += matches_cnt;
    st_relax_max (stats_matches_max, matches_cnt);
  }
  return matches_cnt;
}