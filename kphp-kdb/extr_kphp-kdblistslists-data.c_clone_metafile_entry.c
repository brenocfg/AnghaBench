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
typedef  int /*<<< orphan*/  tree_ext_large_t ;
struct tree_payload {int /*<<< orphan*/  date; int /*<<< orphan*/  value; int /*<<< orphan*/  flags; scalar_t__ text; int /*<<< orphan*/  global_id; } ;
typedef  int /*<<< orphan*/  object_id_t ;

/* Variables and functions */
 int /*<<< orphan*/ * M_global_id_list ; 
 int /*<<< orphan*/  M_obj_id_list ; 
 int M_tot_entries ; 
 scalar_t__ NODE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OARR_ENTRY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OTree ; 
 struct tree_payload* PAYLOAD (int /*<<< orphan*/ *) ; 
 scalar_t__ TF_ZERO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * listree_replace_large (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metafile_get_date (int) ; 
 int /*<<< orphan*/  metafile_get_flags (int) ; 
 int /*<<< orphan*/  metafile_get_value (int) ; 

__attribute__((used)) static tree_ext_large_t *clone_metafile_entry (int temp_id) {
  assert (temp_id >= 0 && temp_id < M_tot_entries);
  object_id_t object_id = OARR_ENTRY (M_obj_id_list, temp_id);
  tree_ext_large_t *T = listree_replace_large (&OTree, object_id);
  assert (NODE_TYPE (T) == TF_ZERO);
  struct tree_payload *P = PAYLOAD (T);
  P->global_id = M_global_id_list[temp_id];
  P->text = 0;
  P->flags = metafile_get_flags (temp_id);
  P->value = metafile_get_value (temp_id);
  P->date = metafile_get_date (temp_id);
  return T;
}