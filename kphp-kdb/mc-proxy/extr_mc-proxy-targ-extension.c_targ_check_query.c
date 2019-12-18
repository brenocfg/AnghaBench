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

/* Variables and functions */
 int eat_at (char const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char const*,int) ; 
 int mct_add ; 
 int mct_get ; 
 int mct_replace ; 
 int mct_set ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static int targ_check_query (int type, const char *key, int key_len) {
  if (verbosity) {
    fprintf (stderr, "targ_check: type = %d, key = %s, key_len = %d\n", type, key, key_len);
  }
  int l = eat_at (key, key_len);
  key += l;
  key_len -= l;
  if (type == mct_get) {
    return (key_len >= 6 && !strncmp (key, "target", 6)) || 
           (key_len >= 6 && !strncmp (key, "search", 6)) ||
           (key_len >= 6 && !strncmp (key, "prices", 6)) ||
           (key_len >= 11 && !strncmp (key, "deletegroup", 11)) ||
           (key_len >= 10 && !strncmp (key, "ad_pricing", 10)) ||
           (key_len >= 13 && !strncmp (key, "targ_audience", 13)) ||
           (key_len >= 8 && !strncmp (key, "audience", 8)) ||
           ((key_len >= 3 && !strncmp (key, "ad_", 3)) && !(key_len >= 8 && !strncmp (key, "ad_query", 8)) && !(key_len >= 7 && !strncmp (key, "ad_info", 7))) ||
           (key_len >= 18 && !strncmp (key, "recent_views_stats", 18)) ||
           (key_len >= 17 && !strncmp (key, "recent_ad_viewers", 17));
  } else if (type == mct_set || type == mct_replace || type == mct_add) {
    return (key_len >= 4 && !strncmp (key, "temp", 4)) || (key_len >= 5 && !strncmp (key, "xtemp", 5));
  } else {
    return 1;
  }
}