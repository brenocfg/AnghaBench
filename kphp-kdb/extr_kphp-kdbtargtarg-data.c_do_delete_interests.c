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
struct lev_generic {int dummy; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_INTERESTS_CLEAR ; 
 unsigned int MAX_INTERESTS ; 
 struct lev_generic* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  clear_interests (struct lev_generic*) ; 
 int /*<<< orphan*/ * get_user (int) ; 

int do_delete_interests (int user_id, int type) {
  user_t *U = get_user (user_id);
  if (!U || (unsigned) type > MAX_INTERESTS) {
    return 0;
  }
  struct lev_generic *E = alloc_log_event (LEV_TARG_INTERESTS_CLEAR + type, 8, user_id);
  clear_interests (E);
  return 1;
}