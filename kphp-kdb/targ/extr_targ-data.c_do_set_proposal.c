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
struct lev_proposal {int len; int /*<<< orphan*/  text; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TARG_PROPOSAL ; 
 struct lev_proposal* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ conv_user_id (int) ; 
 int /*<<< orphan*/  filter_simple_text (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/ * get_user (int /*<<< orphan*/ ) ; 
 int store_proposal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int do_set_proposal (int user_id, const char *text, int len) {
  if (len < 0 || len >= 1024 || conv_user_id (user_id) < 0) {
    return 0;
  }
  struct lev_proposal *E = alloc_log_event (LEV_TARG_PROPOSAL, 11+len, user_id);

  E->len = len;
  filter_simple_text (E->text, text, len);

  user_t *U = get_user (E->user_id);

  if (U) {
    return store_proposal (U, E->text, len);
  } else {
    return 0;
  }
}