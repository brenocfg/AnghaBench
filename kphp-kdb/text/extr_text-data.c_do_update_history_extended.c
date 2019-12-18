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
typedef  int /*<<< orphan*/  user_t ;

/* Variables and functions */
 int /*<<< orphan*/ * get_user_f (int) ; 
 long strlen (char const*) ; 
 int /*<<< orphan*/  update_history_extended (int /*<<< orphan*/ *,char const*,long,int) ; 

int do_update_history_extended (int user_id, const char *string, long len, int op) {
  if (op < 100 || op >= 200 || !string) {
    return -1;
  }
  if (len < 0) {
    len = strlen (string);
  }
  if (len & (-1 << 16)) {
    return -1;
  }
  user_t *U = get_user_f (user_id);
  if (!U) {
    return -1;
  }
  update_history_extended (U, string, len, op);
  return 1;
}