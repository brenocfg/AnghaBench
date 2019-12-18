#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int key_len; int data_len; int timestamp; scalar_t__ key; scalar_t__ data; } ;
typedef  TYPE_1__ hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  debug_dump_hash_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  del_entry_time (TYPE_1__*) ; 
 int /*<<< orphan*/  entry_memory ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  free_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  tree_delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int verbosity ; 
 int /*<<< orphan*/  zzfree (scalar_t__,int) ; 

void del_entry (hash_entry_t *entry) {
  assert (entry);
  if (verbosity >= 4) {
    fprintf(stderr, "deleted %p\n", entry);
    debug_dump_hash_entry (entry);
  }

  del_entry_time (entry);

  tree = tree_delete (tree, entry);
  
  zzfree (entry->key, entry->key_len + 1); 
  zzfree (entry->data, entry->data_len + 1);
  entry_memory -= entry->key_len + entry->data_len + 2;

  entry->key = 0;
  entry->key_len = -1;
  entry->timestamp = -1;

  free_entry (entry);
}