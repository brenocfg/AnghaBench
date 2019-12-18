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
struct heap_entry {int temp_id; } ;
typedef  int /*<<< orphan*/  listree_t ;
typedef  int /*<<< orphan*/  global_id_t ;

/* Variables and functions */
 int /*<<< orphan*/ * M_global_id_list ; 
 int __vsort_and_mask ; 
 int /*<<< orphan*/  __vsort_scanned ; 
 int __vsort_xor_mask ; 
 struct heap_entry* heap_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int metafile_get_flags (int) ; 
 int /*<<< orphan*/  metafile_get_value (int) ; 

__attribute__((used)) static int barray_scan_node (listree_t *LT, int temp_id) {
  int flags = metafile_get_flags (temp_id);
  if (((flags ^ __vsort_xor_mask) & __vsort_and_mask) != 0) {
    return 0;
  }
  global_id_t global_id = M_global_id_list[temp_id];
  value_t value = metafile_get_value (temp_id);
  struct heap_entry *h = heap_insert (value, global_id);
  if (h) {
    h->temp_id = temp_id * 2 + 1;
  }
  __vsort_scanned++;
  return 1;
}