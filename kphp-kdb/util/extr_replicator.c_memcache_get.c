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
 scalar_t__ STATS_BUFF_SIZE ; 
 int prepare_slaves_stats (scalar_t__,int) ; 
 int prepare_stats (struct connection*,scalar_t__,scalar_t__) ; 
 int replicator_prepare_stats () ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,scalar_t__,int) ; 
 scalar_t__ stats_buff ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int len = replicator_prepare_stats ();
    int len2 = prepare_stats (c, stats_buff + len, STATS_BUFF_SIZE - len);
    return_one_key (c, key, stats_buff, len + len2);
    return 0;
  }
  if (key_len >= 13 && !strncmp (key, "slaves_broken", 13)) {
    return_one_key (c, key, stats_buff, prepare_slaves_stats (stats_buff, 1));
    return 0;
  }
  if (key_len >= 14 && !strncmp (key, "slaves_notconn", 14)) {
    return_one_key (c, key, stats_buff, prepare_slaves_stats (stats_buff, 2));
    return 0;
  }
  if (key_len >= 11 && !strncmp (key, "slaves_late", 11)) {
    return_one_key (c, key, stats_buff, prepare_slaves_stats (stats_buff, 4));
    return 0;
  }
  if (key_len >= 15 && !strncmp (key, "slaves_uptodate", 15)) {
    return_one_key (c, key, stats_buff, prepare_slaves_stats (stats_buff, 8));
    return 0;
  }
  if (key_len >= 10 && !strncmp (key, "slaves_all", 10)) {
    return_one_key (c, key, stats_buff, prepare_slaves_stats (stats_buff, -1));
    return 0;
  }
  if (key_len >= 10 && !strncmp (key, "slaves_bad", 10)) {
    return_one_key (c, key, stats_buff, prepare_slaves_stats (stats_buff, ~24));
    return 0;
  }
  return 0;
}