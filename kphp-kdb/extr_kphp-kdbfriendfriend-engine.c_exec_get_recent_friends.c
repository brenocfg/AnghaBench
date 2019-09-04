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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int prepare_recent_friends (int,int) ; 
 int /*<<< orphan*/  return_one_key_list (struct connection*,char const*,int,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int sscanf (char const*,char*,int*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

void exec_get_recent_friends (struct connection *c, const char *str, int len) {
  int user_id, num;
  if (sscanf (str+14, "%d#%d", &user_id, &num) >= 2) {
    int res = prepare_recent_friends (user_id, num);
    if (verbosity > 1) {
      fprintf (stderr, "prepare_recent_friends(%d,%d) = %d\n", user_id, num, res);
    }
    if (res >= 0) {
      return_one_key_list (c, str, len, res, 0, R, R_end - R);
      return;
    }
  }
  return;
}