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

/* Variables and functions */
 scalar_t__ MAX_LIST_ID_INTS ; 
 scalar_t__ MAX_OBJECT_ID_INTS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ list_id_ints ; 
 scalar_t__ object_id_ints ; 

__attribute__((used)) static void compute_struct_sizes (void) {
  assert (list_id_ints > 0 && list_id_ints <= MAX_LIST_ID_INTS);
  assert (object_id_ints > 0 && object_id_ints <= MAX_OBJECT_ID_INTS);
  // compute binlog record sizes
  
  // compute memory structure sizes

  #ifdef LISTS_Z
  int i;
  object_list_ints = object_id_ints + list_id_ints;
  ltree_node_size = sizeof (ltree_t) + object_list_ints * 4;
  object_id_bytes = object_id_ints * 4;
  list_id_bytes = list_id_ints * 4;
  object_list_bytes = object_id_bytes + list_id_bytes;
  list_struct_size = sizeof (list_t) + list_id_bytes;
  payload_offset = tree_ext_small_node_size = __builtin_offsetof (tree_ext_small_t, x) + object_id_bytes;

  for (i = 0; i < object_id_ints; i++) {
    max_object_id[i] = MAXINT;
  }
  for (i = 0; i < list_id_ints; i++) {
    max_list_id[i] = MAXINT;
  }
  for (i = 0; i < object_id_ints + list_id_ints; i++) {
    max_list_object_pair[i] = MAXINT;
  }
  #ifdef _LP64 
  if (payload_offset & 4) {
    payload_offset += 4;
  }
  #endif
  tree_ext_global_node_size = __builtin_offsetof (tree_ext_global_t, z) + object_id_bytes;
  tree_ext_large_node_size = payload_offset + sizeof (struct tree_payload);


  file_list_index_entry_size = sizeof (struct file_list_index_entry) + list_id_bytes;
  #endif

  // compute offsets for data access
  /*
  cyclic_buffer_entry_size = sizeof (struct cyclic_buffer_entry) + list_id_bytes;
  cyclic_buffer_entry_ints = (cyclic_buffer_entry_size >> 2);
  
  assert (!CB);
  CB = malloc (CYCLIC_BUFFER_SIZE * cyclic_buffer_entry_size);
  assert (CB);
  */

}