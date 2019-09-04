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
struct entry {int key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 struct entry __tmp ; 
 int /*<<< orphan*/  create_new_cache_item (struct entry*,char const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_cache_item (struct entry*) ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

struct entry *get_cache_item_simple (const char *key, int key_len) {
  if (verbosity >= 4) { fprintf (stderr, "get_cache_item_simple\n"); }
  if (key_len >= 0 && key_len ==  __tmp.key_len && !memcmp (key, __tmp.key, key_len)) {
    return &__tmp;
  } else {
    free_cache_item (&__tmp);
    create_new_cache_item (&__tmp, key, key_len);
    return &__tmp;
  }
}