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
struct lev_start {scalar_t__ schema_id; int split_mod; int split_min; int split_max; int extra_bytes; int* str; } ;
struct lev_lists_start_ext {int kludge_magic; scalar_t__ schema_id; int list_id_ints; int object_id_ints; int value_ints; int /*<<< orphan*/  extra_mask; } ;

/* Variables and functions */
 scalar_t__ LISTS_SCHEMA_CUR ; 
 scalar_t__ LISTS_SCHEMA_V1 ; 
 scalar_t__ LISTS_SCHEMA_V3 ; 
 int MAX_LIST_ID_INTS ; 
 int MAX_OBJECT_ID_INTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int list_id_bytes ; 
 int list_id_ints ; 
 int list_object_bytes ; 
 int new_entry_value_offset ; 
 int object_id_bytes ; 
 int object_id_ints ; 
 int split_max ; 
 int split_min ; 
 int split_mod ; 
 int /*<<< orphan*/  stderr ; 
 int value_ints ; 

__attribute__((used)) static int lists_le_start (struct lev_start *E) {
  int t_list_id_ints, t_object_id_ints, t_value_ints;
  if (E->schema_id != LISTS_SCHEMA_CUR && E->schema_id != LISTS_SCHEMA_V1) {
    fprintf (stderr, "incorrect binlog schema %08x for lists-engine\n", E->schema_id);
    exit (1);
  }
  if (split_mod) {
    assert (E->split_mod >= split_mod && !(E->split_mod % split_mod) && split_min == E->split_min % split_mod && E->split_max == E->split_min + 1);
  }
  split_min = E->split_min;
  split_max = E->split_max;
  split_mod = E->split_mod;
  assert (split_mod > 0 && split_min >= 0 && split_min + 1 == split_max && split_max <= split_mod);

  if (E->extra_bytes >= 6 && E->str[0] == 1) {
    struct lev_lists_start_ext *EX = (struct lev_lists_start_ext *) E;
    assert (EX->kludge_magic == 1 && EX->schema_id == LISTS_SCHEMA_V3);
    t_list_id_ints = EX->list_id_ints;
    t_object_id_ints = EX->object_id_ints;
    t_value_ints = EX->value_ints;
    assert (!EX->extra_mask);
  } else {
    if (E->schema_id != LISTS_SCHEMA_V1) {
      fprintf (stderr, "incorrect binlog for lists-engine\n");
      exit (1);
    } else {
      t_list_id_ints = t_object_id_ints = t_value_ints = 1;
    }
  }

  if (list_id_ints) {
    assert (t_list_id_ints == list_id_ints && t_object_id_ints == object_id_ints && t_value_ints == value_ints);
  }

  list_id_ints = t_list_id_ints;
  object_id_ints = t_object_id_ints;
  value_ints = t_value_ints;
  new_entry_value_offset = list_id_ints + object_id_ints + 1;

  assert (list_id_ints > 0 && list_id_ints <= MAX_LIST_ID_INTS);
  assert (object_id_ints > 0 && object_id_ints <= MAX_OBJECT_ID_INTS);
  assert (value_ints == 1 || value_ints == 2);
  assert (sizeof (value_t) == 4);

  object_id_bytes = object_id_ints * 4;
  list_id_bytes = list_id_ints * 4;
  list_object_bytes = list_id_bytes + object_id_bytes;

  return 0;
}