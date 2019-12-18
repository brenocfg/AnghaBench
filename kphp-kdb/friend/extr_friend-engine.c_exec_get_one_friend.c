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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int get_friend_cat (int,int) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int sscanf (char const*,char*,int*,int*) ; 
 int /*<<< orphan*/  stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

void exec_get_one_friend (struct connection *c, const char *str, int len) {
  int user_id, friend_id;
  if (sscanf (str, "friend%d_%d", &user_id, &friend_id) >= 2) {
    int res = get_friend_cat (user_id, friend_id);
    if (verbosity > 1) {
      fprintf (stderr, "get_friend(%d,%d) = %d\n", user_id, friend_id, res);
    }
    if (res >= 0) {
      return_one_key (c, str, stats_buff, sprintf(stats_buff, "%d", res));
      return;
    }
  }
  return;
}