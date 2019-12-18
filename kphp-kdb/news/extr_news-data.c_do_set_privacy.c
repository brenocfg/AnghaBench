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
struct lev_privacy {int privacy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_NEWS_PRIVACY ; 
 struct lev_privacy* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ conv_uid (int) ; 
 int set_privacy (int,int) ; 

int do_set_privacy (int user_id, int mask) {
  if (conv_uid (user_id) < 0) {
    return -1;
  }
  struct lev_privacy *E = alloc_log_event (LEV_NEWS_PRIVACY, 12, user_id);
  E->privacy = mask | 1;
  return set_privacy (user_id, mask);
}