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

int news_comm_check_query (int type, const char *key, int key_len) {
  if (verbosity) {
    fprintf (stderr, "news_comm_check: type = %d, key = %s, key_len = %d\n", type, key, key_len);
  }
  int l = eat_at (key, key_len);
  key += l;
  key_len -= l;
  if (type == mct_get) {
    return (key_len >= 17 && (!strncmp (key, "raw_comm_updates", 16) || !strncmp (key, "%raw_comm_updates", 17))) ||
           (key_len >= 13 && (!strncmp (key, "comm_updates", 12) || !strncmp (key, "%comm_updates", 13))) ||
           (key_len >= 21 && !strncmp (key, "raw_user_comm_updates", 21)) || (key_len >= 17 && !strncmp (key, "user_comm_updates", 17)) || 
           (key_len >= 22 && !strncmp (key, "%raw_user_comm_updates", 22)) || (key_len >= 18 && !strncmp (key, "%user_comm_updates", 18)) ||
           (key_len >= 23 && (!strncmp (key, "raw_user_comm_bookmarks", 23) || !strncmp (key, "%raw_user_comm_bookmarks", 23)));
  } else if (type == mct_set || type == mct_replace || type == mct_add) {
    return (key_len >= 10 && !strncmp (key, "objectlist", 10));
  } else {
    return 1;
  }
}