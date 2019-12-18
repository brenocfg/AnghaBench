#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listree_t ;
struct TYPE_6__ {int* list_id; TYPE_1__* o_tree; } ;
typedef  TYPE_2__ list_t ;
struct TYPE_5__ {int delta; } ;

/* Variables and functions */
 int MAXINT ; 
 int M_tot_entries ; 
 int /*<<< orphan*/  OTree ; 
 int /*<<< orphan*/  array_write_object_id ; 
 int /*<<< orphan*/  array_write_object_id_indirect ; 
 int /*<<< orphan*/  assert (int) ; 
 int global_dump_fl ; 
 int global_dump_mod ; 
 int global_dump_rem ; 
 int /*<<< orphan*/  in_array ; 
 int /*<<< orphan*/  in_tree ; 
 int /*<<< orphan*/  listree_get_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  load_o_tree_sub (int /*<<< orphan*/ *,int) ; 
 int metafile_get_sublist_size (int) ; 
 int new_total_entries ; 
 int /*<<< orphan*/  tree_write_object_id ; 
 int /*<<< orphan*/  tree_write_object_id_indirect ; 
 int /*<<< orphan*/  unpack_metafile_pointers (TYPE_2__*) ; 
 int /*<<< orphan*/  writeout_int (int) ; 
 int /*<<< orphan*/  writeout_list_id (int*) ; 

int dump_single_list (list_t *L) {
  listree_t OTreeSub;

  #ifdef LISTS_Z
  int t = L->list_id[0];
  #else
  int t = L->list_id;
  #endif
  if (t == MAXINT) { 
    return 0; 
  }
  t %= global_dump_mod;
  if (t != global_dump_rem && t != -global_dump_rem) { 
    return 0; 
  }

  unpack_metafile_pointers (L);

  new_total_entries = 0;

  int sz;

  if (!global_dump_fl) {
    sz = M_tot_entries + L->o_tree->delta;

    writeout_list_id (L->list_id);
    writeout_int (sz);

    in_tree = tree_write_object_id;
    in_array = array_write_object_id;


    listree_get_range ((listree_t *) &OTree, 0, MAXINT);
  } else {
    int sublist = global_dump_fl & 7;

    sz = metafile_get_sublist_size (sublist);

    if (!sz) {
      return 0;
    }

    writeout_list_id (L->list_id);
    writeout_int (sz);

    in_tree = tree_write_object_id_indirect; 
    in_array = array_write_object_id_indirect;

    load_o_tree_sub (&OTreeSub, sublist);
    listree_get_range (&OTreeSub, 0, MAXINT);
  }

  assert (sz == new_total_entries);

  return 1;
}