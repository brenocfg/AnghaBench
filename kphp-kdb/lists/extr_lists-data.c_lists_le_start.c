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
typedef  int /*<<< orphan*/  value_t ;
struct lev_start {scalar_t__ schema_id; scalar_t__ split_min; scalar_t__ split_max; scalar_t__ split_mod; int extra_bytes; int* str; } ;
struct lev_lists_start_ext {int kludge_magic; scalar_t__ schema_id; int list_id_ints; int object_id_ints; int value_ints; int /*<<< orphan*/  extra_mask; } ;

/* Variables and functions */
 int CB ; 
 scalar_t__ LISTS_SCHEMA_CUR ; 
 scalar_t__ LISTS_SCHEMA_V1 ; 
 scalar_t__ LISTS_SCHEMA_V3 ; 
 int LIST_ID_INTS ; 
 int OBJECT_ID_INTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compute_struct_sizes () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int list_id_ints ; 
 int /*<<< orphan*/  log_cur_pos () ; 
 scalar_t__ log_split_max ; 
 scalar_t__ log_split_min ; 
 scalar_t__ log_split_mod ; 
 int object_id_ints ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int lists_le_start (struct lev_start *E) {
  if (E->schema_id != LISTS_SCHEMA_CUR
#ifdef LISTS_Z
   && E->schema_id != LISTS_SCHEMA_V1
#endif
     ) {
    return -1;
  }

  int old_list_id_ints = -1, old_object_id_ints = -1;

  if (!log_split_mod) {
    assert (!log_split_min && !log_split_max);
    assert (!list_id_ints && !object_id_ints);
    log_split_min = E->split_min;
    log_split_max = E->split_max;
    log_split_mod = E->split_mod;
  } else {
    vkprintf (1, "warning: duplicate LEV_START at log position %lld, split %d..%d mod %d\n", log_cur_pos(), E->split_min, E->split_max, E->split_mod);
    assert (log_split_mod == E->split_mod);
    assert (log_split_min == E->split_min);
    assert (log_split_max == E->split_max);
    old_list_id_ints = list_id_ints;
    old_object_id_ints = object_id_ints;
  }
  assert (log_split_mod > 0 && log_split_min >= 0 && log_split_min + 1 ==  log_split_max && log_split_max <= log_split_mod);


  if (E->extra_bytes >= 6 && E->str[0] == 1) {
    struct lev_lists_start_ext *EX = (struct lev_lists_start_ext *) E;
    assert (EX->kludge_magic == 1 && EX->schema_id == LISTS_SCHEMA_V3);
    list_id_ints = EX->list_id_ints;
    object_id_ints = EX->object_id_ints;
    assert (EX->value_ints == sizeof (value_t) / 4);
    assert (!EX->extra_mask);
  } else {
#ifdef LISTS_Z
    if (E->schema_id != LISTS_SCHEMA_V1) {
      fprintf (stderr, "incorrect binlog for lists-x-engine");
      exit (1);
    } else {
      list_id_ints = object_id_ints = 1;
    }
#else
    list_id_ints = LIST_ID_INTS;
    object_id_ints = OBJECT_ID_INTS;
#endif
  }

#ifndef LISTS_Z
  assert (list_id_ints == 1 && object_id_ints == 1);
#endif

  if (old_object_id_ints > 0) {
    assert (object_id_ints == old_object_id_ints && list_id_ints == old_list_id_ints);
    assert (CB);
  } else {
    compute_struct_sizes ();
  }

  return 0;
}