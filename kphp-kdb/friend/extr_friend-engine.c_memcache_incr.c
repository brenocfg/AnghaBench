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
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int binlog_disabled ; 
 int do_add_friend (int,int,long long,long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  reverse_friends_mode ; 
 int sprintf (char*,char*,int) ; 
 int sscanf (char const*,char*,int*,int*) ; 
 char* stats_buff ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_incr (struct connection *c, int op, const char *key, int len, long long arg) {
  int user_id, friend_id;

  if (len >= 7 && !memcmp (key, "friend", 6) && !reverse_friends_mode) {
    int res = -1;
    if (binlog_disabled != 2 && sscanf (key, "friend%d_%d", &user_id, &friend_id) >= 2) {
      res = do_add_friend (user_id, friend_id, op ? 0 : arg, ~arg, 0);
    }
    if (res > 0) {
      write_out (&c->Out, stats_buff, sprintf(stats_buff, "%d\r\n", res));
    } else {
      write_out (&c->Out, "NOT_FOUND\r\n", 11);
    }
    return 0;
  }

  write_out (&c->Out, "NOT_FOUND\r\n", 11);
  return 0;
}