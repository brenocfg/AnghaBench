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
 scalar_t__ R ; 
 scalar_t__ R_end ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int prepare_friends (int,int,int) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_one_key_list (struct connection*,char const*,int,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int sscanf (char const*,char*,int*,int*,...) ; 
 int /*<<< orphan*/  stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

void exec_get_friends (struct connection *c, const char *str, int len, int offs) {
  int user_id, cat_mask = -1, mode = 0;
  if (sscanf (str+offs, "%d_%d#%d", &user_id, &cat_mask, &mode) >= 2 ||
      sscanf (str+offs, "%d#%d", &user_id, &mode) >= 1) {
    if (offs != 7) {
      mode = 0;
    }
    int res = prepare_friends (user_id, cat_mask, mode);
    if (verbosity > 1) {
      fprintf (stderr, "prepare_friends(%d,%d,%d) = %d\n", user_id, cat_mask, mode, res);
    }
    if (res >= 0) {
      if (offs == 7) {
        return_one_key_list (c, str, len, res, 0, R, R_end - R);
      } else {
        return_one_key (c, str, stats_buff, sprintf(stats_buff, "%d", res));
      }
      return;
    }
  }
  return;
}