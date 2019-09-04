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
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeCnt ; 
 int MAX_RECORD_WORDS ; 
 int /*<<< orphan*/ * NewAllocations ; 
 int /*<<< orphan*/  SplitBlocks ; 
 int /*<<< orphan*/  UsedCnt ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  exec_get_count (struct connection*,char*,int,char const*) ; 
 int /*<<< orphan*/  exec_get_counts (struct connection*,char*,int,char const*) ; 
 int /*<<< orphan*/  exec_get_datedistr (struct connection*,char*,int,char const*,int) ; 
 int /*<<< orphan*/  exec_get_entry (struct connection*,char*,int,char const*) ; 
 int /*<<< orphan*/  exec_get_entry_pos (struct connection*,char*,int,char const*) ; 
 int /*<<< orphan*/  exec_get_entry_sublist_pos (struct connection*,char*,int,char const*) ; 
 int /*<<< orphan*/  exec_get_flags (struct connection*,char*,int,char const*) ; 
 int /*<<< orphan*/  exec_get_incr_value (struct connection*,char*,int,char const*) ; 
 int /*<<< orphan*/  exec_get_intersect (struct connection*,char*,int,int,char const*,int) ; 
 int /*<<< orphan*/  exec_get_list (struct connection*,char*,int,char const*,int) ; 
 int /*<<< orphan*/  exec_get_sorted_list (struct connection*,char*,int,char const*,int) ; 
 int /*<<< orphan*/  exec_get_text (struct connection*,char*,int,char const*) ; 
 int /*<<< orphan*/  exec_get_value (struct connection*,char*,int,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int lists_prepare_stats (struct connection*) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_one_key_list (struct connection*,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int verbosity ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  if (verbosity > 1) {
    fprintf (stderr, "memcache_get: key='%s'\n", key);
  }

  char *new_key;
  int new_len;

  eat_at (key, key_len, &new_key, &new_len);

  if (new_len >= 9 && !strncmp (new_key, "datedistr", 9)) {
    exec_get_datedistr (c, new_key, new_len, key, key_len);
    return 0;
  }

  if (new_len >= 9 && !strncmp (new_key, "intersect", 9)) {
    exec_get_intersect (c, new_key, new_len, 9, key, key_len);
    return 0;
  }

  if (new_len >= 8 && !strncmp (new_key, "subtract", 8)) {
    exec_get_intersect (c, new_key, new_len, 8, key, key_len);
    return 0;
  }

  if (new_len >= 7 && !strncmp (new_key, "sumlist", 7)) {
    exec_get_intersect (c, new_key, new_len, 7, key, key_len);
    return 0;
  }

  if (new_len >= 4 && !strncmp (new_key, "list", 4)) {
    exec_get_list (c, new_key, new_len, key, key_len);
    return 0;
  }

  if (new_len >= 10 && !strncmp (new_key, "sortedlist", 10)) {
    exec_get_sorted_list (c, new_key, new_len, key, key_len);
    return 0;
  }

  if (new_len >= 9 && !strncmp (new_key, "entry_pos", 9)) {
    exec_get_entry_pos (c, new_key, new_len, key);
    return 0;
  }

  if (new_len >= 17 && !strncmp (new_key, "entry_sublist_pos", 17)) {
    exec_get_entry_sublist_pos (c, new_key, new_len, key);
    return 0;
  }

  if (new_len >= 5 && !strncmp (new_key, "entry", 5)) {
    exec_get_entry (c, new_key, new_len, key);
    return 0;
  }

  if (new_len >= 5 && !strncmp (new_key, "flags", 5)) {
    exec_get_flags (c, new_key, new_len, key);
    return 0;
  }

  if (new_len >= 5 && !strncmp (new_key, "value", 5)) {
    exec_get_value (c, new_key, new_len, key);
    return 0;
  }

  if (new_len >= 4 && !strncmp (new_key, "text", 4)) {
    exec_get_text (c, new_key, new_len, key);
    return 0;
  }

  if (new_len >= 6 && !strncmp (new_key, "counts", 6)) {
    exec_get_counts (c, new_key, new_len, key);
    return 0;
  }

  if (new_len >= 5 && !strncmp (new_key, "count", 5)) {
    exec_get_count (c, new_key, new_len, key);
    return 0;
  }

  if (new_len >= 10 && !strncmp (new_key, "incr_value", 10)) {
    exec_get_incr_value (c, new_key, new_len, key);
  }

  if (new_len >= 16 && !strncmp (new_key, "free_block_stats", 16)) {
    return_one_key_list (c, key, key_len, MAX_RECORD_WORDS, 0, FreeCnt, MAX_RECORD_WORDS);
    return 0;
  }

  if (new_len >= 16 && !strncmp (new_key, "used_block_stats", 16)) {
    return_one_key_list (c, key, key_len, MAX_RECORD_WORDS, 0, UsedCnt, MAX_RECORD_WORDS);
    return 0;
  }

  if (new_len >= 16 && !strncmp (new_key, "allocation_stats", 16)) {
    return_one_key_list (c, key, key_len, MAX_RECORD_WORDS, 0, NewAllocations[0], MAX_RECORD_WORDS * 4);
    return 0;
  }

  if (new_len >= 17 && !strncmp (new_key, "split_block_stats", 17)) {
    return_one_key_list (c, key, key_len, MAX_RECORD_WORDS, 0, SplitBlocks, MAX_RECORD_WORDS);
    return 0;
  }

  if (new_len >= 5 && !strncmp (new_key, "stats", 5)) {
    int len = lists_prepare_stats (c);
    return_one_key (c, key, stats_buff, len);
    return 0;
  }

  return 0;
}