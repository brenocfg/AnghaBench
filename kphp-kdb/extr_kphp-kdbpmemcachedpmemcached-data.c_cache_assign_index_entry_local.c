#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct index_entry {int data_len; int /*<<< orphan*/  delay; int /*<<< orphan*/  flags; scalar_t__ data; } ;
struct TYPE_2__ {int data_len; int /*<<< orphan*/  delay; int /*<<< orphan*/  flags; scalar_t__ data; } ;
struct entry {int index_entry; int allocated_here; int timestamp; TYPE_1__ data; scalar_t__ key_len; } ;

/* Variables and functions */
 scalar_t__ PMEMCACHED_TYPE_INDEX_DISK ; 
 int cache_size ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ index_type ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 scalar_t__ zzmalloc (int) ; 

inline int cache_assign_index_entry_local (struct entry *entry, struct index_entry *index_entry) {
  if (!index_entry || index_entry->data_len == -1) {
    entry->index_entry = 0;
    entry->data.data_len = -1;
    entry->data.data = 0;
  } else {
    entry->index_entry = 1;
    entry->data.data_len = index_entry->data_len;
    if (index_type != PMEMCACHED_TYPE_INDEX_DISK) {
      entry->data.data = index_entry->data + entry->key_len;
      entry->allocated_here = 0;
    } else {
      entry->data.data = zzmalloc (entry->data.data_len + 1);
      memcpy (entry->data.data, index_entry->data+ entry->key_len, entry->data.data_len + 1);
      entry->allocated_here = 1;
      cache_size += entry->data.data_len + 1;
    }
    entry->data.flags = index_entry->flags;
    entry->data.delay = index_entry->delay;
  }
  entry->timestamp = -2;
  if (verbosity >= 4) {
    fprintf (stderr, "done... \n");
    fprintf (stderr, "data_len = %d\n", entry->data.data_len);
  }
  return 0;
}