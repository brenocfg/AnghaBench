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
struct lev_langs {int* langs; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_LANG_ADD ; 
 int MAX_LANGS ; 
 int add_langs (int /*<<< orphan*/ *,int*,int) ; 
 struct lev_langs* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/ * get_user (int) ; 

int do_set_user_lang (int user_id, int lang_id) {
  user_t *U = get_user (user_id);
  if (!U || lang_id < 0 || lang_id >= MAX_LANGS) {
    return 0;
  }

  struct lev_langs *E = alloc_log_event (LEV_TARG_LANG_ADD + 1, 12, user_id);
  E->langs[0] = lang_id;

  return add_langs (U, E->langs, 1);
}