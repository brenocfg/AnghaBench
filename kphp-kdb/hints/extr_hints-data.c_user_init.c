#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ object_old_n; int /*<<< orphan*/ * object_type_ids; int /*<<< orphan*/  object_chg; int /*<<< orphan*/ * object_indexes; int /*<<< orphan*/ * object_data; scalar_t__ aio; scalar_t__ metafile_len; int /*<<< orphan*/ * metafile; int /*<<< orphan*/ * prev_used; int /*<<< orphan*/ * next_used; int /*<<< orphan*/  flags; int /*<<< orphan*/  chg_list_global; int /*<<< orphan*/  chg_list_st; int /*<<< orphan*/  chg_list_cur; int /*<<< orphan*/ * object_ratings; int /*<<< orphan*/ * object_names; scalar_t__ object_size; int /*<<< orphan*/  chg_list_en; int /*<<< orphan*/  object_table; int /*<<< orphan*/  pref_table; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  CHG_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_USER_INFO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_USER_RATING_STATE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chg_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_changes_st ; 
 int /*<<< orphan*/  htbl_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ltbl_init (int /*<<< orphan*/ *) ; 

void user_init (user *u) {
#ifdef HINTS
  htbl_init (&u->pref_table);
#endif
  ltbl_init (&u->object_table);
  chg_list_init (&u->chg_list_st, &u->chg_list_en);
  u->object_size = 0;
#ifdef HINTS
  u->object_names = NULL;
#endif
  u->object_ratings = NULL;
  u->chg_list_cur = u->chg_list_st;
  u->chg_list_global = global_changes_st;
  u->flags = SET_USER_INFO(0, -1);
  u->flags = SET_USER_RATING_STATE(u->flags, 1);

  u->next_used = NULL;
  u->prev_used = NULL;

  u->metafile = NULL;
  u->metafile_len = 0;
  u->aio = 0;

#ifdef HINTS
  u->object_data = NULL;
  u->object_indexes = NULL;
#else
  CHG_INIT (u->object_chg);
#endif
  u->object_type_ids = NULL;
  u->object_old_n = 0;
}