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
struct lev_stats_visitor_ext64 {long long cnt_id; int user_id; int sex_age; int m_status; int polit_views; int section; int city; int country; int geoip_country; int source; } ;
struct lev_stats_visitor_ext {int user_id; int sex_age; int m_status; int polit_views; int section; int city; int country; int geoip_country; int source; } ;
struct lev_stats_visitor64 {long long cnt_id; int user_id; } ;
struct lev_stats_visitor {int user_id; } ;
struct counter {int unique_visitors; struct counter* commit_next; int /*<<< orphan*/  views_uncommitted; int /*<<< orphan*/  visitors_geoip_countries; int /*<<< orphan*/  visitors_countries; int /*<<< orphan*/  visitors_cities; int /*<<< orphan*/  visitors_source; int /*<<< orphan*/  visitors_sex_age; int /*<<< orphan*/  visitors_section; int /*<<< orphan*/  visitors_polit; int /*<<< orphan*/  visitors_mstatus; int /*<<< orphan*/  visitors_age; int /*<<< orphan*/ * visitors_sex; int /*<<< orphan*/  visitors; int /*<<< orphan*/  deletes; int /*<<< orphan*/  views; } ;

/* Variables and functions */
 scalar_t__ LEV_STATS_VISITOR ; 
 scalar_t__ LEV_STATS_VISITOR_64 ; 
 scalar_t__ LEV_STATS_VISITOR_EXT ; 
 scalar_t__ LEV_STATS_VISITOR_EXT_64 ; 
 int MAX_AGE ; 
 int /*<<< orphan*/  MAX_CITIES ; 
 int /*<<< orphan*/  MAX_COUNTRIES ; 
 int /*<<< orphan*/  MAX_GEOIP_COUNTRIES ; 
 int MAX_MSTATUS ; 
 int MAX_POLIT ; 
 int MAX_SECTION ; 
 int MAX_SEX ; 
 int MAX_SEX_AGE ; 
 int MAX_SOURCE ; 
 int MAX_SUBCNT ; 
 int /*<<< orphan*/  MIN_CITIES ; 
 int /*<<< orphan*/  MIN_COUNTRIES ; 
 int /*<<< orphan*/  MIN_GEOIP_COUNTRIES ; 
 int /*<<< orphan*/  add_list (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* alloc_log_event (scalar_t__,int,long long) ; 
 int cnt_incr (int /*<<< orphan*/ *,int,int) ; 
 struct counter* counters_commit_head ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct counter* get_counter_f (long long,int) ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  mode_ignore_user_id ; 
 scalar_t__ monthly_stat ; 
 scalar_t__ now ; 
 int packed_subcnt_increment (struct counter*,int,int) ; 
 int /*<<< orphan*/  set_perm (struct counter*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ today_start ; 
 int /*<<< orphan*/  tot_deletes ; 
 int /*<<< orphan*/  tot_views ; 
 int /*<<< orphan*/  tree_insert (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_lookup (int /*<<< orphan*/ ,int) ; 
 int verbosity ; 

int counter_incr_ext (long long counter_id, int user_id, int replaying, int op, int subcnt, int sex, int age, int m_status, int polit_views, int section, int city, int geoip_country,int country, int source) {
  int subcnt_value = 0;
  if (verbosity >= 4) {
    fprintf (stderr, "counter_incr_ext (%lld, %d, %d, %d, %d)\n", counter_id, user_id, replaying, op, subcnt);
  }

  int sex_age = 16*sex + age;
  struct counter *C = get_counter_f (counter_id, replaying ? 3 : 1);
  if (!C) { return -1; }
  set_perm (C);

  if (-1 > subcnt || subcnt >= MAX_SUBCNT) {
    if (verbosity >= 1) {
      fprintf (stderr, "Unknown subcounter (%d). Skipping.\n", subcnt);
    }
    subcnt = -1;
  }

  if (op == 0) {
    tot_views++;
  } else {
    tot_deletes++;
  }
  
  if (subcnt == -1) {
    if (op == 0) {
      C->views++;  
    } else {
      C->deletes++;
    }
  } else {
    /*
    if (C->subcnt_number != types[C->type].field_number) {
      int *t = (int *)zzrealloc0 ((char *)C->subcnt, sizeof (int) * C->subcnt_number, sizeof (int) * types[C->type].field_number);
      if (!t) {
        if (verbosity >= 1) {
          fprintf (stderr, "Can not realloc data for subcounters: not enough mem\n");
        }
      } else {
        C->subcnt = t;
        C->subcnt_number = types[C->type].field_number;
      }
    } 
    if (subcnt >= C->subcnt_number) {
      return -1;
    }
    */
    subcnt_value = packed_subcnt_increment(C, subcnt, (op == 0) ? 1 : (-1));
  }

  if (verbosity >= 4) {
    fprintf (stderr, "Starting\n");
  }

  
  if (subcnt != -1 || !tree_lookup (C->visitors, user_id)) {
    if (subcnt == -1) {
      if ((now >= today_start && !mode_ignore_user_id) || monthly_stat) {
        //assert (!tree_lookup (C->visitors, user_id));
        //assert (check_tree (C->visitors));
        C->visitors = tree_insert (C->visitors, user_id, lrand48());
      }
      if (verbosity >= 4) {
        fprintf (stderr, "Inserted to tree\n");
      }
      C->unique_visitors++;
      if (sex > 0 && sex <= MAX_SEX) { C->visitors_sex[sex-1]++; } else { sex = 0; }
      age = cnt_incr (&C->visitors_age, age, MAX_AGE);
      m_status = cnt_incr (&C->visitors_mstatus, m_status, MAX_MSTATUS);
      polit_views = cnt_incr (&C->visitors_polit, polit_views, MAX_POLIT);
      section = cnt_incr (&C->visitors_section, section, MAX_SECTION);
      if (age > 0 && sex > 0) {
        cnt_incr (&C->visitors_sex_age, (sex-1)*MAX_AGE+age, MAX_SEX_AGE);
      }
      source = cnt_incr (&C->visitors_source, source, MAX_SOURCE);
      if (city > 0) {
        add_list (&C->visitors_cities, city, MIN_CITIES, MAX_CITIES);
      }
      if (country > 0) {
        add_list (&C->visitors_countries, country, MIN_COUNTRIES, MAX_COUNTRIES);
      }
      if (geoip_country > 0) {
        add_list (&C->visitors_geoip_countries, geoip_country, MIN_GEOIP_COUNTRIES, MAX_GEOIP_COUNTRIES);
      }
    }
    if (verbosity >= 4) {
      fprintf (stderr, "Creating logevent\n");
    }
    if (!replaying) {
      if (sex | age | m_status | polit_views | section | city | country | geoip_country | source) {
        if (counter_id == (int)counter_id) {
          struct lev_stats_visitor_ext *LV = 
            alloc_log_event (LEV_STATS_VISITOR_EXT + (op << 7) + subcnt + 1, sizeof (struct lev_stats_visitor_ext), counter_id);
          LV->user_id = user_id;
          LV->sex_age = sex_age;
          LV->m_status = m_status;
          LV->polit_views = polit_views;
          LV->section = section;
          LV->city = city;
          LV->country = country;
          LV->geoip_country = geoip_country;
          LV->source = source;
        } else {
          struct lev_stats_visitor_ext64 *LV = 
            alloc_log_event (LEV_STATS_VISITOR_EXT_64 + (op << 7) + subcnt + 1, sizeof (struct lev_stats_visitor_ext64), counter_id);
          LV->cnt_id = counter_id;
          LV->user_id = user_id;
          LV->sex_age = sex_age;
          LV->m_status = m_status;
          LV->polit_views = polit_views;
          LV->section = section;
          LV->city = city;
          LV->country = country;
          LV->geoip_country = geoip_country;
          LV->source = source;
        }
      } else {
        if (counter_id == (int)counter_id) {
          struct lev_stats_visitor *LV = 
            alloc_log_event (LEV_STATS_VISITOR + (op << 7) + subcnt + 1, sizeof (struct lev_stats_visitor), counter_id);
          LV->user_id = user_id;
        } else {
          struct lev_stats_visitor64 *LV = 
            alloc_log_event (LEV_STATS_VISITOR_64 + (op << 7) + subcnt + 1, sizeof (struct lev_stats_visitor64), counter_id);
          LV->cnt_id = counter_id;
          LV->user_id = user_id;
        }
      }
    }
  } else if (!replaying && !C->views_uncommitted++) {
    C->commit_next = counters_commit_head;
    counters_commit_head = C;
  }
  if (verbosity >= 4) {
    fprintf (stderr, "Incr done\n");
  }
  if (subcnt == -1) {
    return C->unique_visitors;
  } else {
    return subcnt_value;
  }
}