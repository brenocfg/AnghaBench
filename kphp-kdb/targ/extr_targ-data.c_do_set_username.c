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
struct lev_username {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_USERNAME ; 
 struct lev_username* alloc_log_event (scalar_t__,int,int) ; 
 scalar_t__ conv_user_id (int) ; 
 int /*<<< orphan*/  filter_text (int /*<<< orphan*/ ,char const*,int) ; 
 int set_username (struct lev_username*,int) ; 

int do_set_username (int user_id, const char *text, int len) {
  if ((unsigned)len >= 256 || conv_user_id (user_id) < 0) {
    return 0;
  }
  struct lev_username *E = alloc_log_event (LEV_TARG_USERNAME + len, 9 + len, user_id);
  filter_text (E->s, text, len);
  return set_username (E, len);
}