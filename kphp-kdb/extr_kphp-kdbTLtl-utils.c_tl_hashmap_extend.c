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
struct tl_hashmap {int size; int n; int /*<<< orphan*/ ** h; int /*<<< orphan*/  compute_hash; int /*<<< orphan*/  compare; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 struct tl_hashmap* tl_hashmap_alloc (int) ; 
 int /*<<< orphan*/  tl_hashmap_free (struct tl_hashmap**) ; 
 int /*<<< orphan*/  tl_hashmap_get_f (struct tl_hashmap**,int /*<<< orphan*/ *,int) ; 
 int verbosity ; 

__attribute__((used)) static void tl_hashmap_extend (struct tl_hashmap **V) {
  if (verbosity >= 4) {
    fprintf (stderr, "tl_hashmap_extend: old hash size is %d.\n", (*V)->size);
  }
  int i;
  struct tl_hashmap *H = tl_hashmap_alloc ((*V)->n * 2);
  H->compare = (*V)->compare;
  H->compute_hash = (*V)->compute_hash;
  for (i = 0; i < (*V)->size; i++) {
    if ((*V)->h[i] != NULL) {
      tl_hashmap_get_f (&H, (*V)->h[i], 1);
    }
  }
  tl_hashmap_free (V);
  *V = H;
}