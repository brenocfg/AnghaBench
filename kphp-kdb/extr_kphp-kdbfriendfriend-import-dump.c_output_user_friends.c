#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lev_setlist_long {int user_id; int num; int* L; int /*<<< orphan*/  type; } ;
struct lev_setlist_cat_long {int user_id; int num; TYPE_1__* L; int /*<<< orphan*/  type; } ;
struct lev_setlist_cat {int user_id; TYPE_1__* L; scalar_t__ type; } ;
struct lev_setlist {int user_id; int* L; scalar_t__ type; } ;
struct friend {int cat; int id; struct friend* next; } ;
struct TYPE_2__ {int id; int cat; } ;
typedef  TYPE_1__ id_cat_pair_t ;

/* Variables and functions */
 scalar_t__ LEV_FR_SETLIST ; 
 scalar_t__ LEV_FR_SETLIST_CAT ; 
 int /*<<< orphan*/  LEV_FR_SETLIST_CAT_LONG ; 
 int /*<<< orphan*/  LEV_FR_SETLIST_LONG ; 
 int MAX_IMPORT_FRIENDS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ext_lists_output ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/ * list_len_cnt ; 
 int /*<<< orphan*/  lists_output ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 
 void* write_alloc (int) ; 

void output_user_friends (int user_id, struct friend *list) {
  int cnt = 0, cnt2 = 0;
  struct friend *p = list;
  if (!list) { 
    return; 
  }
  while (p) {
    if (p->cat != 1) {
      cnt2++;
    }
    p = p->next;
    cnt++;
    assert (cnt <= 1000000);
  }
  p = list;
  if (cnt > MAX_IMPORT_FRIENDS) {
    if (verbosity > 0) {
      fprintf (stderr, "warning: user %d has %d friends, only %d imported\n", 
	user_id, cnt, MAX_IMPORT_FRIENDS);
    }
    while (cnt > MAX_IMPORT_FRIENDS) {
      if (p->cat != 1) {
        cnt2--;
      }
      p = p->next;
      cnt--;
    }
  }
  list_len_cnt[cnt]++;
  if (!cnt2) {
    int *q;

    if (cnt >= 256) {
      struct lev_setlist_long *E = write_alloc (12 + 4*cnt);
      E->type = LEV_FR_SETLIST_LONG;
      E->user_id = user_id;
      E->num = cnt;
      q = E->L + cnt;
    } else {
      struct lev_setlist *E = write_alloc (8 + 4*cnt);
      E->type = LEV_FR_SETLIST + cnt;
      E->user_id = user_id;
      q = E->L + cnt;
    }
    while (p) {
      *--q = p->id;
      assert (p->cat == 1);
      p = p->next;
    }

    lists_output++;

  } else {
    id_cat_pair_t *r;

    if (cnt >= 256) {
      struct lev_setlist_cat_long *E = write_alloc (12 + 8*cnt);
      E->type = LEV_FR_SETLIST_CAT_LONG;
      E->user_id = user_id;
      E->num = cnt;
      r = E->L + cnt;
    } else {
      struct lev_setlist_cat *E = write_alloc (8 + 8*cnt);
      E->type = LEV_FR_SETLIST_CAT + cnt;
      E->user_id = user_id;
      r = E->L + cnt;
    }
    while (p) {
      r--;
      r->id = p->id;
      r->cat = p->cat;
      p = p->next;
    }

    ext_lists_output++;
  }
}