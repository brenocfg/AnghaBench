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
struct tl_hashmap {int size; scalar_t__ filled; scalar_t__ n; void** h; int /*<<< orphan*/  (* compare ) (void*,void*) ;int /*<<< orphan*/  (* compute_hash ) (struct tl_hashmap*,void*,int*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (struct tl_hashmap*,void*,int*,int*) ; 
 int /*<<< orphan*/  stub2 (void*,void*) ; 
 int /*<<< orphan*/  tl_hashmap_extend (struct tl_hashmap**) ; 

void *tl_hashmap_get_f (struct tl_hashmap **V, void *p, int force) {
  assert (force >= 0);
  int h1, h2;
  struct tl_hashmap *H = *V;
  H->compute_hash (H, p, &h1, &h2);
  void *D;
  while ((D = H->h[h1]) != NULL) {
    if (!H->compare (D, p)) {
      return D;
    }
    h1 += h2;
    if (h1 >= H->size) { h1 -= H->size; }
  }
  if (!force) {
    return NULL;
  }
  if (H->filled == H->n) {
    tl_hashmap_extend (V);
    return tl_hashmap_get_f (V, p, force);
  }
  H->filled++;
  H->h[h1] = p;
  return p;
}