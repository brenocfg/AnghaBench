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
struct tl_hashmap {int size; int n; int /*<<< orphan*/  h; scalar_t__ filled; } ;

/* Variables and functions */
 int TL_MIN_HASHMAP_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int get_hashtable_size (int) ; 
 int /*<<< orphan*/  tl_zzmalloc0 (int) ; 
 struct tl_hashmap* zmalloc (int) ; 

struct tl_hashmap *tl_hashmap_alloc (int n) {
  assert (n >= TL_MIN_HASHMAP_SIZE);
  struct tl_hashmap *H = zmalloc (sizeof (struct tl_hashmap));
  H->size = get_hashtable_size (n);
  H->filled = 0;
  H->n = n;
  H->h = tl_zzmalloc0 (H->size * sizeof (void *));
  return H;
}