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
struct index_entry {int* data; int key_len; } ;

/* Variables and functions */
 struct index_entry empty_index_entry ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * index_binary_data ; 
 size_t* index_offset ; 
 int index_size ; 
 scalar_t__ mystrcmp (int*,int,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

struct index_entry* index_get (const char *key, int key_len) {
  int l = -1;
  int r = index_size;
  while (r-l > 1) {
    int x = (r+l)>>1;
    struct index_entry *entry = (struct index_entry *)&index_binary_data[index_offset[x]];
    if (mystrcmp (entry->data, entry->key_len, key, key_len) < 0) {
      l = x;
    } else {
      r = x;
    }
  }
  if (verbosity>=4) {
    fprintf (stderr, "(l,r) = (%d,%d)\n", l, r);
    fprintf (stderr, "index_size = %d\n", index_size);
  }
  l++;
  struct index_entry *entry;
  if (l < index_size) {
    entry = (struct index_entry *)&index_binary_data[index_offset[l]];
    vkprintf (4, "entry->key_len = %d, key_len = %d\n", entry->key_len, key_len);
    if (verbosity >= 6) {
      int i;
      for (i = 0; i < entry->key_len; i++)
        fprintf (stderr, "%c", entry->data[i]);
      fprintf (stderr, "\n");
    }
  }
  if (l < index_size && !mystrcmp (entry->data, entry->key_len, key, key_len)) { 
    vkprintf (4, "Item found in index.\n");
    return entry;
  }
  return &empty_index_entry;
}