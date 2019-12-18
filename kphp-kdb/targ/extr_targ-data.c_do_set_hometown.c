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
struct lev_hometown {int /*<<< orphan*/  text; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_HOMETOWN ; 
 struct lev_hometown* alloc_log_event (scalar_t__,int,int) ; 
 scalar_t__ conv_user_id (int) ; 
 int /*<<< orphan*/  filter_simple_text (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/ * get_user (int /*<<< orphan*/ ) ; 
 int store_hometown (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int do_set_hometown (int user_id, const char *text, int len) {
  if (len < 0 || len >= 256 || conv_user_id (user_id) < 0) {
    return 0;
  }
  struct lev_hometown *E = alloc_log_event (LEV_TARG_HOMETOWN + len, 9+len, user_id);

  filter_simple_text (E->text, text, len);

  user_t *U = get_user (E->user_id);

  if (U) {
    return store_hometown (U, E->text, len);
  } else {
    return 0;
  }
}