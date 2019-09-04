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
struct index_entry {scalar_t__ key_len; scalar_t__ data_len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int MAX_METAFILES ; 
 scalar_t__ MAX_METAFILE_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ buffer_meta ; 
 int /*<<< orphan*/  buffer_meta_init_key (int /*<<< orphan*/ ,scalar_t__) ; 
 int buffer_meta_number ; 
 scalar_t__ buffer_meta_pos ; 
 scalar_t__* buffer_shifts ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct index_entry*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

void buffer_meta_index (struct index_entry* index_entry) {
  if (verbosity >= 3) {
    fprintf (stderr, "Data from index_entry\n");
  }
  if (buffer_meta_pos == 0) {
    buffer_meta_init_key (index_entry->data, index_entry->key_len);
  }
  assert (buffer_meta_pos + sizeof (struct index_entry) + index_entry->key_len + index_entry->data_len + 1 < MAX_METAFILE_SIZE);
  memcpy (buffer_meta + buffer_meta_pos, index_entry, sizeof(struct index_entry) + index_entry->key_len + index_entry->data_len + 1);
  buffer_meta_pos += sizeof(struct index_entry) + index_entry->key_len + index_entry->data_len + 1;
  assert (buffer_meta_number < MAX_METAFILES - 1);
  buffer_shifts[++buffer_meta_number] = buffer_meta_pos;
}