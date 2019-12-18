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
struct tree_payload {int dummy; } ;
struct file_list_index_entry {int dummy; } ;
struct cyclic_buffer_entry {int dummy; } ;
typedef  int /*<<< orphan*/  ltree_t ;

/* Variables and functions */
 int CB ; 
 int CYCLIC_BUFFER_SIZE ; 
 void* MAXINT ; 
 int MAX_LIST_ID_INTS ; 
 int MAX_OBJECT_ID_INTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int cyclic_buffer_entry_ints ; 
 int cyclic_buffer_entry_size ; 
 int file_list_index_entry_size ; 
 int /*<<< orphan*/  list_id ; 
 int list_id_bytes ; 
 int list_id_ints ; 
 void* list_struct_size ; 
 int /*<<< orphan*/  list_t ; 
 int ltree_node_size ; 
 void** max_list_id ; 
 void** max_list_object_pair ; 
 void** max_object_id ; 
 int object_id_bytes ; 
 int object_id_ints ; 
 int object_list_bytes ; 
 int object_list_ints ; 
 void* offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int payload_offset ; 
 void* tree_ext_global_node_size ; 
 int /*<<< orphan*/  tree_ext_global_t ; 
 int tree_ext_large_node_size ; 
 int tree_ext_small_node_size ; 
 int /*<<< orphan*/  tree_ext_small_t ; 
 int /*<<< orphan*/  x ; 
 int /*<<< orphan*/  z ; 
 int zzmalloc (int) ; 

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
  list_struct_size = offsetof (list_t, list_id) + list_id_bytes;
  payload_offset = tree_ext_small_node_size = offsetof (tree_ext_small_t, x) + object_id_bytes;
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
  tree_ext_global_node_size = offsetof (tree_ext_global_t, z) + object_id_bytes;
  tree_ext_large_node_size = payload_offset + sizeof (struct tree_payload);

  cyclic_buffer_entry_size = sizeof (struct cyclic_buffer_entry) + list_id_bytes;
  cyclic_buffer_entry_ints = (cyclic_buffer_entry_size >> 2);

  file_list_index_entry_size = sizeof (struct file_list_index_entry) + list_id_bytes;
  #endif

  // compute offsets for data access

  assert (!CB);
  CB = zzmalloc (CYCLIC_BUFFER_SIZE * cyclic_buffer_entry_size);
  assert (CB);

}