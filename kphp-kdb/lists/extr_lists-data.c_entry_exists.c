#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_ext_large_t ;
typedef  int /*<<< orphan*/  object_id_t ;
struct TYPE_7__ {scalar_t__ data; scalar_t__ tot_entries; } ;
typedef  TYPE_1__ metafile_t ;
struct TYPE_8__ {int /*<<< orphan*/ * A; scalar_t__ N; int /*<<< orphan*/ ** root; } ;
typedef  TYPE_2__ listree_direct_t ;
struct TYPE_9__ {int metafile_index; int /*<<< orphan*/ * o_tree; } ;
typedef  TYPE_3__ list_t ;
typedef  int /*<<< orphan*/  list_id_t ;
typedef  int /*<<< orphan*/  array_object_id_t ;

/* Variables and functions */
 int /*<<< orphan*/ * NILL ; 
 TYPE_3__* __get_list_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int find_metafile (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_metafile_ptr (int) ; 
 int /*<<< orphan*/ * listree_lookup_large (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ metafile_mode ; 
 scalar_t__ prepare_list_metafile (int /*<<< orphan*/ ,int) ; 

int entry_exists (list_id_t list_id, object_id_t object_id) {
  if (metafile_mode && prepare_list_metafile (list_id, -1) < 0) {
    assert (0);
    return 0;
  }
  list_t *L = __get_list_f (list_id, -1);
  int metafile_index = -1;

  listree_direct_t OTree;
  tree_ext_large_t *Root;

  if (!L) {
    metafile_index = find_metafile (list_id);
    if (metafile_index < 0) {
      return 0;
    }
    Root = NILL;
    OTree.root = &Root;
  } else {
    metafile_index = L->metafile_index;
    OTree.root = &L->o_tree;
  }

  if (metafile_index >= 0) {
    metafile_t *M = get_metafile_ptr (metafile_index);
    OTree.N = M->tot_entries;
    OTree.A = (array_object_id_t *) M->data;
  } else {
    OTree.N = 0;
    OTree.A = 0;
  }

  int temp_id;
  tree_ext_large_t *T = listree_lookup_large (&OTree, object_id, &temp_id);

  return T ? 1 : 0;
}