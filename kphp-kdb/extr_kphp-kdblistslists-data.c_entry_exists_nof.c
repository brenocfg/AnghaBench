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
typedef  void tree_ext_large_t ;
typedef  int /*<<< orphan*/  object_id_t ;
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  OTree ; 
 int /*<<< orphan*/ * __get_list_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_metafile_loaded (int,int) ; 
 int entry_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_list_metafile (int /*<<< orphan*/ ) ; 
 void* listree_lookup_large_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int metafile_mode ; 
 int /*<<< orphan*/  unpack_metafile_pointers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unpack_metafile_pointers_short (int /*<<< orphan*/ *) ; 

int entry_exists_nof (list_id_t list_id, object_id_t object_id) {
  list_t *L = __get_list_f (list_id, -1);
  if (metafile_mode & 1) {
    if (!L) {
      return 1;
    }
    unpack_metafile_pointers_short (L);
    int temp_id;
    tree_ext_large_t *T = listree_lookup_large_tree (&OTree, object_id, &temp_id);
    if ((T && (T != (void *)-1)) || ((T == (void *)-1) && get_list_metafile (list_id) >= 0)) {
      return 1;
    } else {
      return 0;
    }
  }
  if (metafile_mode) {
    if (!L) {
      return 1;
    }
    //int metafile_number = find_metafile (list_id);
    //int metafile_number = get_list_m (list_id)->metafile_number;
    int metafile_number = get_list_metafile (list_id);
    if (metafile_number < 0) {
      return 1;
    }    
    if (!check_metafile_loaded (metafile_number, -1)) {  // ??? NOT SURE about this -1, was 0 before
      return 1;
    }
    unpack_metafile_pointers (L);
  }
  return entry_exists (list_id, object_id);
}