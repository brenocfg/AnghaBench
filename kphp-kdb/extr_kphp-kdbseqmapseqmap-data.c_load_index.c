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
typedef  int /*<<< orphan*/  kfs_file_handle_t ;

/* Variables and functions */
 int NODE_TYPE_PLUS ; 
 int NODE_TYPE_SURE ; 
 void* alloc_item (int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ index_entries ; 
 void* max_item ; 
 void* min_item ; 

int load_index (kfs_file_handle_t Index) {
  if (!Index) {
    index_entries = 0;
    min_item = alloc_item (0, 0, NODE_TYPE_PLUS | NODE_TYPE_SURE, 0);
    static int key[1000];
    int i;
    for (i = 0; i < 1000; i++) { key[i] = 0x7fffffff; }
    max_item = alloc_item (1000, key, NODE_TYPE_PLUS | NODE_TYPE_SURE, 0);
    return 0;
  }
  assert (0);
  return 0;
}