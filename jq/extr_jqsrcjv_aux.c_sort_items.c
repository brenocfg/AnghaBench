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
struct sort_entry {int index; void* key; void* object; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 scalar_t__ JV_KIND_ARRAY ; 
 int /*<<< orphan*/  assert (int) ; 
 void* jv_array_get (int /*<<< orphan*/ ,int) ; 
 int jv_array_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 struct sort_entry* jv_mem_calloc (int,int) ; 
 int /*<<< orphan*/  qsort (struct sort_entry*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_cmp ; 

__attribute__((used)) static struct sort_entry* sort_items(jv objects, jv keys) {
  assert(jv_get_kind(objects) == JV_KIND_ARRAY);
  assert(jv_get_kind(keys) == JV_KIND_ARRAY);
  assert(jv_array_length(jv_copy(objects)) == jv_array_length(jv_copy(keys)));
  int n = jv_array_length(jv_copy(objects));
  struct sort_entry* entries = jv_mem_calloc(sizeof(struct sort_entry), n);
  for (int i=0; i<n; i++) {
    entries[i].object = jv_array_get(jv_copy(objects), i);
    entries[i].key = jv_array_get(jv_copy(keys), i);
    entries[i].index = i;
  }
  jv_free(objects);
  jv_free(keys);
  qsort(entries, n, sizeof(struct sort_entry), sort_cmp);
  return entries;
}